# Json-based-CSP-solver

Constraint satisfaction problems (CSP's) are integral in deterministic ai. By assigning domains to particular nodes, and trying to satisfy constraints that exist between different nodes, a number of problems may be solved. CSP's may also be used in planning problems, where one needs to know the sequence of actions that need to be taken in order to reach a goal state (or world).

The CSP solver utilized depth-first-search in combination with branch pruning in order to take advantage of DFS's non-exponential memory use. After the problem space has been initialized with the json (see example format in problem.json), the terminal may be used for the user to select a variable ordering for each variables expansion and assignment. Furthermore, the solutions, and number of pruned branches with be displayed in the console.

The project uilizes the lightweight json parser for c++, jsonCpp.
