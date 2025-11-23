<style>
h1 {
  border-bottom: none;
}
</style>
<div align="center">
<h1>AVL Tree</h1>
</div>

* Name: Joshua Roberge
* Semester: Fall 2025
* Topic: AVL Tree
<hr>


A binary tree is a data structure which, on average, provides O(Log(n)) for insertions, deletion and searching, but this is not the worst-case scenario. Binary trees have a significant flaw in that they are entirely dependent on the insertion order of the data. When a binary tree is unbalanced, its performance is affected and can result in a worst-case scenario of O(n) for various operations. This research paper investigates the data structure of an AVL tree an AVL is a self-balancing tree that corrects for a binary tree’s worst-case scenario. To understand the effectiveness of this algorithm, our research will be discussed in four sections:

1.	AVL Algorithm: A general discussion of the core concepts behind the algorithm and its practical implementations.
2.	Implementation: A discussion of the reports code base and the design decisions behind the data structures implementation.
3.	Theoretical Analysis: Analyzing Big(O) for insertion, deletion, and searching, and proving correctness.
4.	Empirical Analysis: analyzing the runtime through the use of an experiment.


# Algorithm Background
