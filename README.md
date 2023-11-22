# TriadRows
This program was written a long-while ago, in C. It was an exercise
in applying concepts I had learned through college courses, namely
various data-structures, file I/O, and the use of pointers in C.

## Concept
Triad Rows are a concept from Mick Goodrick's book *"The Advancing Guitarist"*.
In it, he proposes a method of practicing voice leadning, as well as playing over
chord changes. 

It presuposes that we have a set number of three-note chords (named triads), and 
if we randomly select one after the other, that we could in essence, find the
smoothest possible way to connect all of them, such that it doesn't sound too
disconnected. Doing so is termed "voice-leading", the harmonic approach of searching
for the least possible movement between harmonic structures.

If C-Major (in first inversion) is followed by G-Major, we can voice lead it as follows:

C-Major: C E G (1 3 5) -> G-Major: B D G (3 5 1)
C -> B is in a single step
E -> D is two half-steps (a whole step)
G -> G requires no movement

## Implementation
There are two files that acheive this purpose. The first `row.c`, utilizes simple 
array storage, allows for randomization of order, resetting of order, and display.

`binaryRow.c` includes the same functionality, but by using a *Binary Tree* data structure
instead.
