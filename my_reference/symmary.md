# Summary

- Introduction
- Mental Models First

- Ownership
  - Ownership is responsibility, not memory
  - Ownership via files and resources
  - When ownership fights your design

- Borrowing
  - Shared vs exclusive access
  - Borrowing in real APIs
  - The borrow checker as a design tool

- Lifetimes
  - Lifetimes as contracts
  - Who outlives whom
  - When lifetimes disappear

- Structs & Enums
  - Modeling reality with types
  - Making illegal states unrepresentable

- Traits
  - Capabilities over inheritance
  - Designing extensible APIs
  - Static vs dynamic dispatch

- Iterators
  - Pull-based data flow
  - Laziness and zero-cost abstraction
  - Thinking in pipelines

- Error Handling
  - `Result` as control flow
  - Library vs application errors
  - Panics, boundaries, and invariants

- Smart Pointers
  - Indirection with purpose
  - `Box`, `Rc`, `Arc` in practice
  - Interior mutability when it makes sense

- Concurrency
  - Sharing vs message passing
  - `Send` and `Sync` intuition
  - Designing thread-safe APIs

- Async Rust
  - Async is not parallel
  - Futures and executors
  - Cancellation and backpressure

- Macros
  - Code generation, not magic
  - When macros are the right tool

- Unsafe Rust
  - What “unsafe” actually means
  - Building safe abstractions

- Performance
  - Where Rust is actually fast
  - Data layout and cache behavior

- Closing Thoughts
  - Writing Rust that feels natural
