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

&nbsp;&nbsp;&nbsp;&nbsp;
A traditional binary search tree (BST) is a data structure that, on average, provides $\log(n)$ for insertions, deletions, and searching, but our worst-case runtime is significantly worse than this. A BST has a significant flaw in that its performance is dependent on insertion order. When a binary tree is unbalanced, its performance is affected and can result in a worst-case scenario of O(n) for numerous operations.

&nbsp;&nbsp;&nbsp;&nbsp;
This research reviews and analyzes the AVL data structure. An AVL is a self-balancing tree that ensures a BST has a height of $O(\log(n))$. To understand the effectiveness of this algorithm, our research will be discussed in four sections:

1. __AVL Data Structure__: A general discussion of the core concepts behind the algorithm and its practical implementations.
2. __Theoretical Analysis__: Showing $h = O(\log(n))$ and then analyzing Big(O) for insertion, deletion, and searching.
3. __Implementation/Experimentation__: A discussion of the report's code base and experiment design.
4. __Empirical Analysis__: analyzing the runtimes using our experimental data.

##