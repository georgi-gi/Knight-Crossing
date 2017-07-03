# Knight-Crossing

Knight Crossing shows the shortest path for the knight from position (0,0) to
position (n,n) on a chess table. The algorithm used is the A*. The f function in
the algorithm, which tells which one of the nodes will be observed first,
is a sum of two functions - g and h. g shows the number of moves the knight has
made and h is the heuristics function. The heurisitcs function works in the
following way: if the size of the table is (n,n) and the next move will lead the
knight on position (i,j), the value of h in this node will be n-i if i >= j
and n-j else. This means that the h function shows the number of cells diagonally
to the direction of (n,n) and the remaining number of cells on row or column.
This ensures that the path will be the shortest one.