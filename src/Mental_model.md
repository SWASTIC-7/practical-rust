# Mental Models First

Before writing Rust code, it helps to adjust how you *think*.

Most difficulties in Rust do not come from syntax or missing features.  
They come from using mental models borrowed from other languages and expecting Rust to behave the same way.

This chapter is about unlearning some habits and building new ones.

---

## Rust Is Not Trying to Be Convenient

Many languages optimize for convenience first:
- you can copy values freely
- you can mutate shared data easily
- errors are often handled at runtime

Rust optimizes for **correctness by construction**.

If Rust feels strict or annoying, it is usually because:
> the design is unclear, not because the language is limited.

Rust pushes complexity **to the edges**, so the core stays safe.

---

## Ownership Is About Responsibility

In Rust, ownership is not about memory addresses.  
It is about **who is responsible for a value**.

The owner decides:
- when a value is dropped
- who can access it
- whether it can be shared or mutated

Once you think in terms of responsibility instead of memory, many rules start to feel natural.

---

## Borrowing Is About Access, Not References

A borrow is not “just a pointer”.

A borrow is a **temporary permission**:
- shared borrow → many readers
- mutable borrow → one writer

Rust does not track *where* references point.  
It tracks **who is allowed to do what, and when**.

This is why the borrow checker feels more like a rule engine than a type checker.

---

## Lifetimes Are Promises

Lifetimes are not timestamps or scopes.

A lifetime says:
> “This reference will be valid for *at least* this long.”

Most of the time, Rust can infer these promises for you.  
When it cannot, it asks you to be explicit.

Lifetimes exist to make *implicit assumptions visible*.

---

## Types Are Design Tools

In Rust, types are not just for correctness.  
They are tools to **shape how code can be used**.

Good Rust APIs:
- prevent invalid states
- guide users toward correct usage
- make misuse hard or impossible

If you fight the type system, it often means the model needs rethinking.

---

## Errors Are Part of the API

Errors in Rust are not exceptional.

They are expected, modeled, and handled explicitly.

`Result` is not just for failures —  
it is how Rust represents **branching logic with context**.

A function that can fail is not incomplete.  
It is honest.

---

## Rust Prefers Explicit Boundaries

Rust likes clear lines:
- who owns what
- who can mutate
- what can fail
- what can run concurrently

When boundaries are clear, the compiler becomes an ally.  
When they are fuzzy, the compiler pushes back.

This is not friction — it is feedback.

---

## How to Use This Book

This book is not meant to be read top to bottom in one go.

You are encouraged to:
- run the examples
- break them
- read compiler errors fully
- compare working and failing code

Do not try to memorize rules.  
Try to notice *patterns*.

Over time, Rust will stop feeling restrictive and start feeling predictable.

That is when you begin to think in Rust.
