# Practical Rust — Topic Roadmap

This repository contains the planning and reference material for a practical, intermediate Rust book focused on helping developers "think in Rust" through exercises and playgrounds. Below is a complexity-ordered checklist with **real-world use cases** showing where each concept is critical.

> **Hierarchy note:** Each section assumes only prior sections are known. For example, *Async* assumes closures and traits; *Unsafe* assumes ownership and layout are solid.

---

## 1 · Beginner / Quick Refresh

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Rust toolchain, Cargo, edition, and project layout | Every Rust project: `ripgrep`, `rustup`, `cargo` itself |
| [ ] | Basic syntax: variables, immutability, patterns, functions | CLI tools like `bat`, `fd` — simple utilities with clean flow |
| [ ] | Primitives, tuples, arrays, slices | Parsing binary protocols (`nom`), image pixel buffers (`image`) |
| [ ] | `String` vs `&str` basics | Text processing in `ripgrep`, config parsing |
| [ ] | Control flow: if, match, loops | State machines in parsers (`pest`), game loops |
| [ ] | Ownership: move semantics and copy types | File handles in `std::fs`, socket ownership in `mio` |
| [ ] | Borrowing: mutable and immutable references | Zero-copy parsing (`serde_json`), buffer slicing (`bytes`) |
| [ ] | Basic error handling: `Result`, `Option`, `unwrap`/`expect` | File I/O in `std::fs::read`, HTTP responses in `reqwest` |

---

## 2 · Core Concepts (Essential)

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Structs and enums (algebraic data types) | AST nodes in `rustc`/`swc`, config types in `serde` |
| [ ] | Pattern matching and exhaustive matches | JSON/TOML parsing (`serde`), packet classification |
| [ ] | Methods and associated functions (`impl`) | Builder pattern: `reqwest::ClientBuilder`, `tokio::runtime::Builder` |
| [ ] | Traits and trait bounds | `Read`/`Write` in `std::io`, `Serialize`/`Deserialize` |
| [ ] | Generics and monomorphization | `Vec<T>`, `HashMap<K,V>`, generic middleware in `tower` |
| [ ] | Lifetimes: annotations and elision | Zero-copy deserialization, borrowing in `regex` matches |
| [ ] | Modules, visibility, crate structure | Large projects: `rustc`, `bevy`, `actix-web` |
| [ ] | Cargo workspaces and dependencies | Monorepos like `rust-analyzer`, `tokio` workspace |

---

## 3 · Iterators & Closures
*(builds on traits, generics)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Iterators, adapters, lazy evaluation | Streaming file search in `ripgrep`, log processing |
| [ ] | Closures and capturing environments | Callbacks in `tokio::spawn`, event handlers in `iced` GUI |
| [ ] | Combinators: `map`, `filter`, `fold`, `collect` | Data pipelines in `polars` (dataframes), ETL tools |

---

## 4 · Collections
*(builds on generics, iterators)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | `Vec`, `VecDeque` | Dynamic arrays, ring buffers in audio (`cpal`) |
| [ ] | `HashMap`, `HashSet` | Caching (`lru`), symbol tables in compilers |
| [ ] | `BTreeMap`, `BTreeSet` | Ordered indices, range queries in databases |
| [ ] | `String` deeper: `Cow`, `OsString`, `PathBuf` | Cross-platform paths (`walkdir`), ropes (`ropey`) |

---

## 5 · Error Handling (in depth)
*(builds on enums, traits, `Result`)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Custom error types (`std::error::Error`) | Library errors in `sqlx`, `hyper` |
| [ ] | `thiserror` for libraries | `reqwest`, `tokio-postgres`, `aws-sdk-rust` |
| [ ] | `anyhow` for applications | CLI apps (`ripgrep`, `cargo-watch`) |
| [ ] | `?` chaining and `From` conversions | Multi-layer propagation in web backends |
| [ ] | Recoverable vs unrecoverable (`panic!`) | OOM in allocators, `debug_assert!` |

---

## 6 · Memory & Ownership (Advanced)
*(builds on ownership, lifetimes, traits)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | RAII and `Drop` | File/socket cleanup, GPU resource release (`wgpu`) |
| [ ] | `Box<T>` — heap allocation, recursive types | Recursive AST nodes, large structs by pointer |
| [ ] | `Rc<T>`, `Weak<T>` — single-thread ref counting | DOM trees (`scraper`), graphs (`petgraph`) |
| [ ] | `Arc<T>` — thread-safe ref counting | Shared config in `actix-web`, connection pools |
| [ ] | Interior mutability: `Cell`, `RefCell` | Caches inside immutable structs, memoization |
| [ ] | `Mutex<T>`, `RwLock<T>` | Shared state in web servers (`axum`, `rocket`) |

---

## 7 · Concurrency (threads & sync)
*(builds on `Arc`, `Mutex`)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | `Send` and `Sync` marker traits | Ensuring thread-safe types in `tokio` tasks |
| [ ] | `std::thread` spawning and joins | Parallel compression (`zstd`), CPU-bound work |
| [ ] | `Mutex`, `RwLock`, `Condvar` patterns | Job queues, producer-consumer |
| [ ] | Channels: `mpsc`, `crossbeam-channel` | Log aggregators, actors (`actix`) |
| [ ] | Scoped threads (`std::thread::scope`) | Parallel graph traversal, divide-and-conquer |
| [ ] | Parallel iterators (`rayon`) | Bulk image processing, parallel test runners |

---

## 8 · Async / Futures
*(builds on closures, traits, `Pin`)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | `Future` trait, polling, executors | Core of `tokio`, `async-std`, `smol` |
| [ ] | `async`/`await` basics | HTTP servers (`axum`), DB drivers (`sqlx`) |
| [ ] | Runtimes: `tokio` vs `async-std` vs `smol` | High-perf networking (`hyper`), embedded (`embassy`) |
| [ ] | Pinning (`Pin`, `Unpin`) | Self-referential futures, async iterators |
| [ ] | Streams and async iteration | WebSocket streams (`tungstenite`), event sourcing |
| [ ] | Task spawning, cancellation, timeouts | Request timeouts (`tower`), graceful shutdown |

---

## 9 · Macros & Metaprogramming
*(builds on syntax, traits)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | `macro_rules!` declarative macros | `vec![]`, `println!`, `lazy_static!`, DSLs |
| [ ] | Procedural derive macros | `#[derive(Serialize)]` in `serde` |
| [ ] | Attribute macros | `#[tokio::main]`, `#[test]`, `#[async_trait]` |
| [ ] | Function-like proc macros | `sqlx::query!` compile-time SQL checking |
| [ ] | `syn`, `quote`, `proc_macro2` | Custom derives (`clap`, `thiserror`) |
| [ ] | When macros vs generics vs functions | API trade-offs in `diesel`, `sea-orm` |

---

## 10 · Type System & Advanced Traits
*(builds on generics, lifetimes)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Associated types vs generic params | `Iterator::Item`, `Future::Output` |
| [ ] | Higher-ranked trait bounds (`for<'a>`) | Closures with refs in `rayon` |
| [ ] | Object safety and `dyn Trait` | Plugin systems, `Box<dyn Error>` |
| [ ] | Trait coherence (orphan rules) | Extension traits (`itertools`), newtype wrappers |
| [ ] | Type aliases, newtypes, phantom types | Type-state (`http::Request<Body>`), units of measure |
| [ ] | Const generics | Fixed arrays `[T; N]`, matrices (`nalgebra`) |

---

## 11 · Unsafe Rust & FFI
*(builds on ownership, layout)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Unsafe blocks: what you can do | Raw pointers in `bytes`, custom allocators |
| [ ] | Common pitfalls (aliasing, UB) | Bugs in hand-rolled linked lists |
| [ ] | `repr(C)` and data layout | Structs passed to C (`libc`), syscalls |
| [ ] | Calling C from Rust (`extern "C"`) | Bindings: `openssl`, `rusqlite` |
| [ ] | Calling Rust from C | Python bindings (`pyo3`), Ruby (`magnus`) |
| [ ] | Safe abstractions over unsafe | `Vec` internals, `parking_lot` locks |

---

## 12 · Performance & Low-Level
*(builds on unsafe, layout, iterators)*

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Zero-cost abstractions | Iterator chains → loops in `ripgrep` |
| [ ] | Data layout, alignment, `repr` | Network headers, GPU buffers (`wgpu`) |
| [ ] | Profiling (`perf`, `flamegraph`, `samply`) | Optimising `rustc`, game frame times |
| [ ] | Benchmarking (`criterion`, `divan`) | Regex throughput, serialization speed |
| [ ] | SIMD (`std::simd`, intrinsics) | JSON parsing (`simd-json`), image decode |
| [ ] | Memory ordering and atomics | Lock-free queues (`crossbeam`), `Arc` bumps |

---

## 13 · Compiler Internals & Diagnostics

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | How borrow checker reasons (NLL, MIR) | Understanding complex lifetime errors |
| [ ] | Reading `rustc` errors, `--explain` | Day-to-day debugging |
| [ ] | Clippy lints and custom lints | Project conventions, security audits |
| [ ] | `rustfmt` and formatting standards | CI enforcement, team consistency |
| [ ] | Unstable features and RFC process | Trying nightly in personal projects |

---

## 14 · Testing, Property Testing & Debugging

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Unit tests (`#[test]`) | Every crate; `std` test suite |
| [ ] | Integration tests (`tests/`) | CLI tests (`assert_cmd`), API tests |
| [ ] | Doc tests | Examples in `serde`, `tokio` docs |
| [ ] | Mocking (`mockall`, fakes) | Trait mocking, fake HTTP servers |
| [ ] | Property testing (`proptest`, `quickcheck`) | Round-trip serialization, parser fuzzing |
| [ ] | Fuzzing (`cargo-fuzz`, `afl`) | Security in `rustls`, `image` |
| [ ] | Debugging (`println!`, `dbg!`, `gdb`) | Async state, memory issues |

---

## 15 · Ecosystem, Tooling & Best Practices

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Publishing to `crates.io` | Every open-source Rust lib |
| [ ] | Semver and `cargo-semver-checks` | Avoiding breaks in `tokio`, `serde` |
| [ ] | `rustdoc` and doc best practices | High-quality docs: `axum`, `clap` |
| [ ] | CI pipelines (test, clippy, fmt) | GitHub Actions in `rust-analyzer`, `bevy` |
| [ ] | `cargo audit` and supply-chain security | Detecting CVEs in deps |
| [ ] | API design: builders, typestate, ext traits | `reqwest` builder, `http` crate design |

---

## 16 · Domain Topics (choose relevant)

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Embedded (`no_std`, `cortex-m`) | Drone firmware (`embassy`), IoT sensors |
| [ ] | WebAssembly (`wasm-bindgen`) | Browser apps (`yew`, `leptos`), Cloudflare Workers |
| [ ] | Systems programming (kernel, drivers) | Redox OS, Linux kernel Rust modules |
| [ ] | Networking (async servers, protocols) | `hyper`, `quinn` (QUIC), `rustls` (TLS) |
| [ ] | Game development | `bevy`, `macroquad`, `ggez` |
| [ ] | CLI tooling | `clap`, `dialoguer`, `indicatif` |

---

## 17 · Appendix / Deep Dives

| Done | Topic | Real-World Example |
|:----:|-------|-------------------|
| [ ] | Generic Associated Types (GATs) | Lending iterators, async traits |
| [ ] | Const generics advanced | Compile-time matrix dims (`nalgebra`) |
| [ ] | Proc macro internals | Writing a derive from scratch |
| [ ] | Unsafe audits and soundness proofs | Reviews in `crossbeam`, `parking_lot` |
| [ ] | Contributing to `rustc` | Compiler dev, diagnostics improvements |

---

Next steps: pick any section and I can expand it with **learning goals**, **playground exercises**, and **curated resources**.
