/*
 the Floyd–Warshall algorithm is an algorithm for finding shortest paths 
 in a weighted graph with positive or negative edge weights 
 (but with no negative cycles).[1][2] A single execution of the algorithm 
 will find the lengths (summed weights) of shortest paths between all 
 pairs of vertices. Although it does not return details of the paths 
 themselves, it is possible to reconstruct the paths with simple modifications to the algorithm. 


 The Floyd–Warshall algorithm compares all possible paths through the graph between 
 each pair of vertices. It is able to do this with 
 {\displaystyle \Theta (|V|^{3})} \Theta (|V|^{3}) comparisons in a graph. 
 This is remarkable considering that there may be up to {\displaystyle \Omega (|V|^{2})}
 {\displaystyle \Omega (|V|^{2})} edges in the graph, 
 and every combination of edges is tested. It does so by incrementally improving an 
 estimate on the shortest path between two vertices, until the estimate is optimal.
*/