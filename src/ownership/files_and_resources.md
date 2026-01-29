# Shared Files 

think of the scenario where you have to read and upadate a public file which are accessible to many. 
Now for a synchronous task the flow is something like this
- open the file
- read the file 
- close the file

now what if you forgot to close the file.
Or if there are multiple user accessing the same file then who will open and who will close?

So these problems are mitigated using ownership model. In Rust there is only one owner at a time for a value.

Lets see different scenarios

## Scenario 1 (one forgets to close the file)
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
    // I'll assume someone else will. 
}

void run_application(const char* log_path) {
    FILE* logger = create_logger(log_path);
    process_events(logger);
    // Oops, forgot to close. Who was supposed to?
}
```

In this above c code user forgot to close the file 
but in Rust the same will file will get automatically closed once the file goes out of scope

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

## Scenario 2 (one tries to close the same file twice)

```c
void process_events(FILE* logger) {
    log_message(logger, "Processing started");
    log_message(logger, "Processing done");
    fclose(logger);  // I'll be responsible!
}

void run_application(const char* log_path) {
    FILE* logger = create_logger(log_path);
    process_events(logger);
    fclose(logger);  // I'll be responsible too!
}
```
look at the above c code , it tries to close the same file twice , which on running could crash, could corrupt memory, could seem fine until production. But this is a threat you know, now lets see the beauty fo Rust how it automatically handles this.


```rust
fn run_application(log_path: &str) -> io::Result<()> {
    let logger = Logger::new(log_path)?;
    
    drop(logger);  // Explicitly drop (close)
    drop(logger);  // Try to drop again
    
    Ok(())
}
```
on running this youy will see something like this

```bash
error[E0382]: use of moved value: `logger`
 --> src/main.rs:5:10
  |
3 |     drop(logger);
  |          ------ value moved here
4 |     
5 |     drop(logger);
  |          ^^^^^^ value used here after move
```
## Scenario 3 (what if you try to access the closed file)

```rust
fn run_application(log_path: &str) -> io::Result<()> {
    let mut logger = Logger::new(log_path)?;
    
    drop(logger);  // Close it
    logger.log("This should fail")?;  // Try to use it
    
    Ok(())
}
```
on doing so you will get an compilation error
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

Hence you saw how ownership model is saving us from multiple threats which are mistakenly left.
