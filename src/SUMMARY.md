# Summary

- [Introduction](./introduction.md)
- [Mental Models First](./mental_models_first.md)


# Core Ownership Model

- [Ownership](./ownership/README.md)
  - [Ownership is Responsibility, Not Memory](./ownership/responsibility.md)
  - [Ownership via Files and Resources](./ownership/files_and_resources.md)
  - [When Ownership Fights Your Design](./ownership/design_conflicts.md)

- [Borrowing](./borrowing/README.md)
  - [Shared vs Exclusive Access](./borrowing/shared_vs_exclusive.md)
  - [Borrowing in Real APIs](./borrowing/real_apis.md)
  - [The Borrow Checker as a Design Tool](./borrowing/design_tool.md)

- [Lifetimes](./lifetimes/README.md)
  - [Lifetimes as Contracts](./lifetimes/contracts.md)
  - [Who Outlives Whom](./lifetimes/outlives.md)
  - [When Lifetimes Disappear](./lifetimes/elision.md)


# Type System

- [Structs & Enums](./structs_enums/README.md)
  - [Modeling Reality with Types](./structs_enums/modeling_reality.md)
  - [Making Illegal States Unrepresentable](./structs_enums/illegal_states.md)

- [Traits](./traits/README.md)
  - [Capabilities over Inheritance](./traits/capabilities.md)
  - [Designing Extensible APIs](./traits/extensible_apis.md)
  - [Static vs Dynamic Dispatch](./traits/dispatch.md)


# Patterns & Abstractions

- [Iterators](./iterators/README.md)
  - [Pull-Based Data Flow](./iterators/pull_based.md)
  - [Laziness and Zero-Cost Abstraction](./iterators/laziness.md)
  - [Thinking in Pipelines](./iterators/pipelines.md)

- [Error Handling](./error_handling/README.md)
  - [Result as Control Flow](./error_handling/result_control_flow.md)
  - [Library vs Application Errors](./error_handling/lib_vs_app.md)
  - [Panics, Boundaries, and Invariants](./error_handling/panics.md)

- [Smart Pointers](./smart_pointers/README.md)
  - [Indirection with Purpose](./smart_pointers/indirection.md)
  - [Box, Rc, Arc in Practice](./smart_pointers/box_rc_arc.md)
  - [Interior Mutability When It Makes Sense](./smart_pointers/interior_mutability.md)


# Concurrency & Async

- [Concurrency](./concurrency/README.md)
  - [Sharing vs Message Passing](./concurrency/sharing_vs_messages.md)
  - [Send and Sync Intuition](./concurrency/send_sync.md)
  - [Designing Thread-Safe APIs](./concurrency/thread_safe_apis.md)

- [Async Rust](./async_rust/README.md)
  - [Async is Not Parallel](./async_rust/not_parallel.md)
  - [Futures and Executors](./async_rust/futures_executors.md)
  - [Cancellation and Backpressure](./async_rust/cancellation.md)


# Advanced Topics

- [Macros](./macros/README.md)
  - [Code Generation, Not Magic](./macros/code_generation.md)
  - [When Macros Are the Right Tool](./macros/when_to_use.md)

- [Unsafe Rust](./unsafe_rust/README.md)
  - [What "Unsafe" Actually Means](./unsafe_rust/what_it_means.md)
  - [Building Safe Abstractions](./unsafe_rust/safe_abstractions.md)

- [Performance](./performance/README.md)
  - [Where Rust is Actually Fast](./performance/where_fast.md)
  - [Data Layout and Cache Behavior](./performance/data_layout.md)

- [Closing Thoughts](./closing_thoughts.md)
