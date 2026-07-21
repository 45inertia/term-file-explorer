# Struct vs Class for Dir_Entry

Date: 20/07/2026

## Context

What would be the right way of implementing a this data holding structure.

## Decision

The decision to be made was beetween using a Struct vs a Class.

`Dir_Entry` is a pure data holder which has three fields and no invariants to protect, no behaviour.
In this case `struct` would be the prefered convention.

## Consequence

`Struct` is to be used as this is just a data holding structure. This brings about the question of
getters and setters. 

Getters and Setters exist to protect invariants (rules about what combinations of field values are
valid, enforced at the point of mutation). `Dir_Entry` has no such rules. Adding getters and setters
would be pure ceremony as there is more code, the same behaviour and no actual protection gained. 

**Note**: All fields in structs are public by default so no accessors/constructors are needed,
aggregate initialization works out of the box: `DirEntry{"file.txt", false, 1024}`