# 📘 DAA Project – Problem Statements

This repository contains solutions and implementations for selected **Design and Analysis of Algorithms (DAA)** problems.

---

## 🔹 Question 1: Graph Algorithms – Johnson's Algorithm

You are given a weighted directed graph  
G = (V, E) that may contain **negative-weight edges** but **no negative-weight cycles**.

Design **Johnson's Algorithm** to compute **all-pairs shortest paths** more efficiently than running Bellman-Ford from every vertex.

### Tasks

1. Describe the **re-weighting technique** used in Johnson's Algorithm and prove that:
   - Re-weighted edge weights are non-negative  
   - Shortest-path relationships are preserved  

2. Explain why **Dijkstra’s Algorithm** cannot be applied directly to graphs with negative edges, and how Johnson’s re-weighting resolves this.

3. Implement the full algorithm:
   - Augmented graph construction  
   - Bellman-Ford for potentials  
   - Re-weighting of edges  
   - Running Dijkstra from every vertex  

4. Derive the **overall time complexity** in terms of |V| and |E|, and compare it with **Floyd-Warshall** for:
   - Sparse graphs  
   - Dense graphs  

5. Demonstrate the algorithm on a graph with:
   - At least **5 vertices**  
   - At least **2 negative edges**  
   - Show potential values and final distance matrix  

---

## 🔹 Question 2: Secure Vault Placement Problem

A facility is modeled as an **N × N grid**, where each cell represents a possible location for placing a security vault.

### Constraints

- No two vaults can be placed in:
  - The same **row**
  - The same **column**
  - The same **diagonal**
- Exactly **N vaults** must be placed
- Some cells may be **blocked** and cannot be used

### Objective

Determine all valid configurations for placing the vaults.

### Tasks

1. Design a **backtracking algorithm** to place N vaults while:
   - Avoiding row, column, and diagonal conflicts  
   - Skipping blocked cells  

2. Implement the algorithm to:
   - Output all valid configurations  
   - Or return the total count  

3. Define the **state representation**, including:
   - Board configuration  
   - Column tracking  
   - Diagonal tracking  

4. Analyze the **worst-case time complexity** in terms of N  

5. Discuss optimizations:
   - Pruning invalid states early  
   - Compare with naive exhaustive search  

---

## 🔹 Question 3: Number Theory & Digit Construction

A bank locker system assigns:

- A unique number **N**
- A passcode **P**

### Constraints on Passcode

- Product of digits of **P = N**
- **P must be the smallest possible number** (numerically)
- **P ≥ N**
- A valid passcode always exists

### Objective

Determine the correct passcode for a given **N**

### Tasks

1. Design an efficient algorithm to construct the smallest number **P** satisfying the conditions  

2. Implement the algorithm:
   - Read input **N** from STDIN  
   - Output the passcode **P**  

3. Explain how **factorization of N** helps construct digits efficiently  

4. Analyze the **time complexity** in terms of N  

5. Compare with a **brute-force approach** (checking all numbers ≥ N), and justify improvements  

---


