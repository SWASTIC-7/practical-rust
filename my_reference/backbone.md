# Mental Models First

This book is not about learning *features*.  
It is about learning *how to think in Rust*.

Rust feels hard not because it is complex, but because it asks you to solve
real-world problems **explicitly**—problems other languages solve implicitly
(or ignore).

Every section in this book follows the same pattern:

- **1 real-world scenario**
- **2–3 failed designs** (things you *will* try)
- **1 final Rust-friendly design**
- **1 takeaway you should remember**

You are not expected to memorize syntax.
You are expected to recognize **patterns**.

---

## Ownership

### Ownership is Responsibility, Not Memory
**Scenario:**  
A task manager owns a list of tasks and is responsible for completing or deleting them.

- Failed design: Multiple parts freely modify the task list.
- Failed design: Copying tasks everywhere to “avoid ownership issues”.
- Final design: One clear owner, others must ask permission.
- Takeaway: Ownership models *responsibility*, not RAM.

---

### Ownership via Files and Resources
**Scenario:**  
A log file that must be opened, written to, and closed correctly.

- Failed design: Forgetting who closes the file.
- Failed design: Letting multiple owners close it.
- Final design: One owner controls the file’s lifetime.
- Takeaway: Ownership ensures cleanup happens exactly once.

---

### When Ownership Fights Your Design
**Scenario:**  
A cache shared across multiple modules.

- Failed design: Fighting the compiler with clones.
- Failed design: Forcing ownership into the wrong place.
- Final design: Rethink the API boundary.
- Takeaway: If ownership hurts, your design might be wrong.

---

## Borrowing

### Shared vs Exclusive Access
**Scenario:**  
Multiple readers reading configuration, one writer updating it.

- Failed design: Multiple writers at the same time.
- Failed design: Global mutable state.
- Final design: Many readers OR one writer.
- Takeaway: Borrowing encodes real-world rules.

---

### Borrowing in Real APIs
**Scenario:**  
A function that processes data without owning it.

- Failed design: Taking ownership when unnecessary.
- Failed design: Returning references incorrectly.
- Final design: Borrow inputs, return owned outputs if needed.
- Takeaway: APIs should express intent.

---

### Borrow Checker as a Design Tool
**Scenario:**  
Building a state machine.

- Failed design: Mutating state everywhere.
- Failed design: Temporary hacks to “please” the compiler.
- Final design: Explicit states and transitions.
- Takeaway: The borrow checker forces clarity.

---

## Lifetimes

### Lifetimes as Contracts
**Scenario:**  
Returning a reference tied to input data.

- Failed design: Returning references to temporaries.
- Failed design: Guessing lifetime annotations.
- Final design: Lifetimes express relationships, not durations.
- Takeaway: Lifetimes are about *who depends on whom*.

---

### Who Outlives Whom
**Scenario:**  
A view into a larger data structure.

- Failed design: Storing references without guarantees.
- Failed design: Over-annotating lifetimes.
- Final design: Data owns views, not the other way around.
- Takeaway: Parents must outlive children.

---

### When Lifetimes Disappear
**Scenario:**  
Iterator adapters and closures.

- Failed design: Expecting explicit lifetimes everywhere.
- Failed design: Overthinking elision.
- Final design: Let the compiler infer when possible.
- Takeaway: Good APIs hide lifetimes.

---

## Structs & Enums

### Modeling Reality with Types
**Scenario:**  
User accounts with different roles.

- Failed design: Boolean flags everywhere.
- Failed design: Optional fields for everything.
- Final design: Enums for real states.
- Takeaway: Types are documentation.

---

### Making Illegal States Unrepresentable
**Scenario:**  
Payment processing.

- Failed design: Checking validity everywhere.
- Failed design: Runtime errors for invalid states.
- Final design: Valid states only exist.
- Takeaway: If it compiles, it should be correct.

---

## Traits

### Capabilities over Inheritance
**Scenario:**  
Different storage backends.

- Failed design: Deep inheritance hierarchies.
- Failed design: God interfaces.
- Final design: Small capability-based traits.
- Takeaway: Traits describe *what*, not *what it is*.

---

### Designing Extensible APIs
**Scenario:**  
A plugin system.

- Failed design: Concrete types everywhere.
- Failed design: Breaking changes for new features.
- Final design: Trait-based extension points.
- Takeaway: Traits are contracts.

---

### Static vs Dynamic Dispatch
**Scenario:**  
Performance-critical vs flexible systems.

- Failed design: Using dynamic dispatch everywhere.
- Failed design: Overusing generics.
- Final design: Choose based on constraints.
- Takeaway: Abstraction has cost—but you choose it.

---

## Iterators

### Pull-Based Data Flow
**Scenario:**  
Processing a large log file.

- Failed design: Loading everything into memory.
- Failed design: Manual indexing.
- Final design: Iterator chains.
- Takeaway: Iterators scale naturally.

---

### Laziness and Zero-Cost Abstraction
**Scenario:**  
Filtering and transforming streams.

- Failed design: Intermediate allocations.
- Failed design: Premature optimization.
- Final design: Lazy evaluation.
- Takeaway: Rust abstractions can be free.

---

### Thinking in Pipelines
**Scenario:**  
Data transformation stages.

- Failed design: Nested loops.
- Failed design: Mutable temporary variables.
- Final design: Clear pipelines.
- Takeaway: Readability is performance.

---

## Error Handling

### `Result` as Control Flow
**Scenario:**  
Parsing user input.

- Failed design: Exceptions or panics.
- Failed design: Ignoring errors.
- Final design: Explicit success and failure paths.
- Takeaway: Errors are values.

---

### Library vs Application Errors
**Scenario:**  
Building a reusable crate.

- Failed design: Panicking inside libraries.
- Failed design: Overly detailed errors.
- Final design: Let callers decide.
- Takeaway: Libraries don’t crash apps.

---

### Panics, Boundaries, and Invariants
**Scenario:**  
Internal assumptions.

- Failed design: Panic everywhere.
- Failed design: Never panic.
- Final design: Panic at boundaries only.
- Takeaway: Panics mark bugs, not input errors.

---

## Smart Pointers

### Indirection with Purpose
**Scenario:**  
Recursive data structures.

- Failed design: Infinite size types.
- Failed design: Heap allocation everywhere.
- Final design: Explicit indirection.
- Takeaway: Indirection should be intentional.

---

### `Box`, `Rc`, `Arc` in Practice
**Scenario:**  
Shared read-only configuration.

- Failed design: Copying large data.
- Failed design: Premature shared ownership.
- Final design: Choose the simplest pointer first.
- Takeaway: Each pointer solves a specific problem.

---

### Interior Mutability When It Makes Sense
**Scenario:**  
Caching computed values.

- Failed design: Fighting the borrow checker.
- Failed design: Global mutable state.
- Final design: Controlled interior mutation.
- Takeaway: Mutability must be justified.

---

## Concurrency

### Sharing vs Message Passing
**Scenario:**  
Worker threads processing jobs.

- Failed design: Shared mutable state.
- Failed design: Locks everywhere.
- Final design: Ownership transfer via messages.
- Takeaway: Don’t share if you can move.

---

### `Send` and `Sync` Intuition
**Scenario:**  
Thread-safe APIs.

- Failed design: Guessing thread safety.
- Failed design: Overusing mutexes.
- Final design: Types express safety.
- Takeaway: Thread safety is a type property.

---

### Designing Thread-Safe APIs
**Scenario:**  
Concurrent data access.

- Failed design: Unsafe public APIs.
- Failed design: Locking inside callers.
- Final design: Safe-by-default APIs.
- Takeaway: Safety belongs in design.

---

## Async Rust

### Async Is Not Parallel
**Scenario:**  
Network requests.

- Failed design: Expecting speedups automatically.
- Failed design: Blocking inside async.
- Final design: Cooperative multitasking.
- Takeaway: Async is about waiting efficiently.

---

### Futures and Executors
**Scenario:**  
Scheduling tasks.

- Failed design: Manual polling.
- Failed design: Executor confusion.
- Final design: Let the runtime drive futures.
- Takeaway: You write logic, executors run it.

---

### Cancellation and Backpressure
**Scenario:**  
Streaming services.

- Failed design: Ignoring cancellation.
- Failed design: Unbounded queues.
- Final design: Respect limits.
- Takeaway: Async systems must slow down safely.

---

## Macros

### Code Generation, Not Magic
**Scenario:**  
Reducing boilerplate.

- Failed design: Copy-paste code.
- Failed design: Overusing macros.
- Final design: Macros for patterns only.
- Takeaway: Macros write Rust for you.

---

### When Macros Are the Right Tool
**Scenario:**  
Domain-specific syntax.

- Failed design: Complex runtime code.
- Failed design: Macro abuse.
- Final design: Declarative power.
- Takeaway: Use macros sparingly.

---

## Unsafe Rust

### What “Unsafe” Actually Means
**Scenario:**  
Interfacing with hardware or C.

- Failed design: Avoiding unsafe forever.
- Failed design: Unsafe everywhere.
- Final design: Small unsafe blocks.
- Takeaway: Unsafe is a promise.

---

### Building Safe Abstractions
**Scenario:**  
Low-level performance code.

- Failed design: Exposing unsafe APIs.
- Failed design: Trusting callers.
- Final design: Unsafe inside, safe outside.
- Takeaway: Safety is an abstraction.

---

## Performance

### Where Rust Is Actually Fast
**Scenario:**  
High-throughput systems.

- Failed design: Micro-optimizing early.
- Failed design: Ignoring profiling.
- Final design: Measure, then optimize.
- Takeaway: Rust gives control, not miracles.

---

### Data Layout and Cache Behavior
**Scenario:**  
Large data processing.

- Failed design: Pointer-heavy structures.
- Failed design: Ignoring memory layout.
- Final design: Cache-friendly design.
- Takeaway: Memory layout is performance.

---

## Closing Thoughts

Rust feels natural once your **mental model matches the compiler’s model**.

This book is about building that model—one real problem at a time.
