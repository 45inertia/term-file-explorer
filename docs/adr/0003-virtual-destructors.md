# Virtual Destructors

Date: 25/07/2026

## Context

This is not an architectural decision but a documentation of a learning lesson. This revolves
around deleting an object through a base class pointer.

## Decision

If `~OS_Service()` is not virtual then delete on an `OS_Service*` only calls delete on `OS_Service`
destructor. It has no way of knowing that the real object is actually a `WindowsOSService`.

This means that anything that `WindowOSService` owns that `OS_Service` doesn't own does not get
released and there is a memory leak. 

## Consequence

Marking the destructor `virtual` fixes this as destruction goes through the same dynamic dispatch
method.

The general rule worth internalizing is:

**Any class intended to be used polymorphically (i.e. any class someone might hold or delete
through a base class pointer) must have a virtual destructor.**