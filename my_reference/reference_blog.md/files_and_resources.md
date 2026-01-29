# Ownership via Files and Resources

Files are one of the clearest examples of why ownership matters. A file handle is a **resource**—something that must be acquired, used, and then released. Get it wrong, and you leak handles, corrupt data, or crash.

Let's explore this with a logging scenario.

---

## The Scenario: A Simple Logger

You need a logger that:
1. Opens a log file
2. Writes messages to it
3. Closes it when done

Sounds simple. Let's see how it goes wrong.

---

## Failed Design #1: Forgetting Who Closes the File

```c
#include <stdio.h>

FILE* create_logger(const char* path) {
    return fopen(path, "a");
}

void log_message(FILE* file, const char* msg) {
    fprintf(file, "%s\n", msg);
}

void process_events(FILE* logger) {
    log_message(logger, "Processing started");
    // ... do work ...
    log_message(logger, "Processing done");
    // Should I close it? The function received it...
    // I'll assume someone else will. 🤷
}

void run_application(const char* log_path) {
    FILE* logger = create_logger(log_path);
    process_events(logger);
    // Oops, forgot to close. Who was supposed to?
}
```

**The problem:** No clear owner. `create_logger` opens it, `process_events` uses it, `run_application` orchestrates it—but nobody takes responsibility for closing it.

**Result:** File handle leak. Do this in a loop and you'll hit the OS limit on open files.

---

## Failed Design #2: Multiple Owners Try to Close

Let's "fix" it by being extra careful—everyone closes!

```c
void process_events(FILE* logger) {
    log_message(logger, "Processing started");
    log_message(logger, "Processing done");
    fclose(logger);  // I'll be responsible!
}

void run_application(const char* log_path) {
    FILE* logger = create_logger(log_path);
    process_events(logger);
    fclose(logger);  // I'll be responsible too! 💥
}
```

**The problem:** Double-free (double-close). The second `fclose` operates on an already-closed file handle—undefined behavior. Could crash, could corrupt memory, could seem fine until production.

Even worse—what if we add error handling?

```c
void run_application(const char* log_path) {
    FILE* logger = create_logger(log_path);
    
    if (some_condition) {
        fclose(logger);
        return;  // Early exit, closed here
    }
    
    process_events(logger);  // Also closes!
    fclose(logger);          // And again here on normal path
    
    // Three potential closes, only one should happen
}
```

**Result:** The more "careful" you are, the more chances for double-close bugs.

---

## The Real Problem: Unclear Responsibility

In C, when you pass a pointer, the language doesn't tell you:
- Are you **borrowing** it (use it, but don't free it)?
- Are you **taking ownership** (you must free it)?
- Is it **shared** (someone else might free it)?

You have to read documentation, comments, or conventions. And hope everyone follows them.

---

## Final Design: One Owner Controls the Lifetime

Here's how Rust solves this—ownership is explicit and enforced:

```rust
use std::fs::File;
use std::io::{self, Write};

struct Logger {
    file: File,  // Logger OWNS the file
}

impl Logger {
    fn new(path: &str) -> io::Result<Logger> {
        let file = File::create(path)?;
        Ok(Logger { file })
    }
    
    fn log(&mut self, msg: &str) -> io::Result<()> {
        writeln!(self.file, "{}", msg)
    }
}

// File is automatically closed when Logger is dropped
```

Now let's use it:

```rust
fn process_events(logger: &mut Logger) -> io::Result<()> {
    // We BORROW the logger (note the &mut)
    // We can use it, but we don't own it
    logger.log("Processing started")?;
    logger.log("Processing done")?;
    Ok(())
    // Logger is NOT closed here—we only borrowed it
}

fn run_application(log_path: &str) -> io::Result<()> {
    let mut logger = Logger::new(log_path)?;  // We OWN it
    
    process_events(&mut logger)?;  // Lend it out
    
    // logger is still valid here!
    logger.log("Application complete")?;
    
    Ok(())
    // logger goes out of scope → File is closed EXACTLY ONCE
}
```

**What changed:**
- `Logger::new` returns an **owned** `Logger`
- `process_events` takes `&mut Logger`—a **mutable borrow**
- The signature tells you: "I'll use this, but I won't consume it"
- When `logger` goes out of scope, `Drop` runs automatically

---

## What If You Try the C Mistakes in Rust?

**Mistake 1: Forgetting to close**

```rust
fn run_application(log_path: &str) -> io::Result<()> {
    let logger = Logger::new(log_path)?;
    // ... use logger ...
    
    // "Forgot" to close? Doesn't matter!
    // Rust calls Drop automatically when logger goes out of scope
    Ok(())
}
```

**Mistake 2: Double close**

```rust
fn run_application(log_path: &str) -> io::Result<()> {
    let logger = Logger::new(log_path)?;
    
    drop(logger);  // Explicitly drop (close)
    drop(logger);  // Try to drop again
    
    Ok(())
}
```

```
error[E0382]: use of moved value: `logger`
 --> src/main.rs:5:10
  |
3 |     drop(logger);
  |          ------ value moved here
4 |     
5 |     drop(logger);
  |          ^^^^^^ value used here after move
```

The compiler catches it. You literally cannot double-close.

**Mistake 3: Using after close**

```rust
fn run_application(log_path: &str) -> io::Result<()> {
    let mut logger = Logger::new(log_path)?;
    
    drop(logger);  // Close it
    logger.log("This should fail")?;  // Try to use it
    
    Ok(())
}
```

```
error[E0382]: borrow of moved value: `logger`
 --> src/main.rs:5:5
  |
3 |     drop(logger);
  |          ------ value moved here
4 |     
5 |     logger.log("This should fail")?;
  |     ^^^^^^ value borrowed here after move
```

Use-after-free? Compile error.

---

## Ownership Transfer: When You Want to Hand It Off

Sometimes you *do* want to transfer ownership:

```rust
fn create_and_transfer() -> Logger {
    let logger = Logger::new("app.log").unwrap();
    logger  // Ownership transfers to caller
    // No drop here—we moved it out
}

fn receive_and_own(logger: Logger) {
    // We now own it (no & in the type)
    // When this function ends, logger is dropped
}

fn main() {
    let logger = create_and_transfer();  // We own it
    receive_and_own(logger);             // Transfer ownership
    // logger is gone—can't use it here
}
```

The type signature tells the whole story:
- `Logger` → ownership transfer (you own it now)
- `&Logger` → shared borrow (read-only loan)
- `&mut Logger` → exclusive borrow (read-write loan)

---

## Takeaway: Ownership Ensures Cleanup Happens Exactly Once

| Problem | C | Rust |
|---------|---|------|
| Forget to close | Runtime leak | Auto-drop handles it |
| Double close | Undefined behavior | Compile error |
| Use after close | Undefined behavior | Compile error |
| Unclear responsibility | Hope & documentation | Type signature enforces it |

Ownership isn't about memory—it's about **responsibility**. When you own something, you're responsible for cleaning it up. When you borrow something, you're explicitly *not* responsible.

The compiler enforces this contract. No hoping, no conventions, no runtime checks. Just correctness by construction.

