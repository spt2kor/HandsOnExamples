//========================================================================================================================
/*
https://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
Greedy Algorithms | Set 7 (Dijkstra’s shortest path algorithm)
Given a graph and a source vertex in the graph, find shortest paths from source to all vertices in the given graph.

Dijkstra’s algorithm is very similar to Prim’s algorithm for minimum spanning tree. 
Like Prim’s MST, we generate a SPT (shortest path tree) with given source as root. 
We maintain two sets, one set contains vertices included in shortest path tree, 
other set includes vertices not yet included in shortest path tree
. At every step of the algorithm, we find a vertex which is in the other set (set of not yet included) 
and has a minimum distance from the source.


Time Complexity of the implementation is O(V^2). 
If the input graph is represented using adjacency list, 
it can be reduced to O(E log V) with the help of binary heap.

 NOTE : Dijkstra’s algorithm doesn’t work for graphs with negative weight edges. 
		For graphs with negative weight edges, Bellman–Ford algorithm can be used,
*/

// TODO   -  https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/
// TODO	  -  https://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/


///Limitation of Dijkstra's algo    https://stackoverflow.com/questions/13159337/why-doesnt-dijkstras-algorithm-work-for-negative-weight-edges
//========================================================================================================================
//========================================================================================================================
#include <iostream>
using namespace std;
const int NoOfVertax = 9;
void PrintDistanceFromNode(int src ,int distance[NoOfVertax], int parentNode[NoOfVertax]);
void dijkstra(int graph[NoOfVertax][NoOfVertax], int startNode);
//===========================================
void main()
{
	cout<<"\n Program Started *** "<<__FILE__<<endl;

	/* Let us create the example graph discussed above */
   int graph[NoOfVertax][NoOfVertax] =	{ {0, 4, 0, 0, 0, 0, 0, 8, 0},
										  {4, 0, 8, 0, 0, 0, 0, 11, 0},
										  {0, 8, 0, 7, 0, 4, 0, 0, 2},
										  {0, 0, 7, 0, 9, 14, 0, 0, 0},
										  {0, 0, 0, 9, 0, 10, 0, 0, 0},
										  {0, 0, 4, 14, 10, 0, 2, 0, 0},
										  {0, 0, 0, 0, 0, 2, 0, 1, 6},
										  {8, 11, 0, 0, 0, 0, 1, 0, 7},
										  {0, 0, 2, 0, 0, 0, 6, 7, 0}
										 };
  
    dijkstra(graph, 0);
	
	cout<<"\n Program Ended"<<endl;
}
//=======================================================================================
int findMinimumPathNode_Dik(bool visited[NoOfVertax] , int distance[NoOfVertax])
{
	int minDist = INT_MAX ; 
	int minNodeIndex = -1;
	for(int u = 0 ; u < NoOfVertax ; ++u)
	{
		if( (visited[u] == false ) && (distance[u] < minDist) )
		{
			minDist = distance[u];
			minNodeIndex = u;
		}
	}
	return minNodeIndex;
}

void dijkstra(int graph[NoOfVertax][NoOfVertax], int startNode)
{
	bool visited[NoOfVertax] = {false};
	int parentNode[NoOfVertax] = {0};
	int distance[NoOfVertax] = {INT_MAX};	//7F'FF'FF'FF
	for(int c = 0 ; c < NoOfVertax ; ++c)
	{
		visited[c] = false;
		parentNode[c] = -1;
		distance[c] = INT_MAX;	//7F'FF'FF'FF
	}

	distance[startNode] = 0;

	for(int c = 0 ; c < NoOfVertax ; ++c)
	{
		int u = findMinimumPathNode_Dik(visited,distance);		//get min distance from "Min Heap" or MinPrioriyQueue()
		//cout<<"\n *********  \n "<<"count = "<<c<<", findMinimumPathNode () u = "<<u<<endl;
		if(u == -1)
			break;

		visited[u] = true;
		for(int v = 0 ; v < NoOfVertax ; ++v)
		{
			//cout<<"\n "<<"visited = "<<(visited[v]? "TRUE" : "FALSE")<<" - graph["<<u<<"]["<<v<<"]  = "<<graph[u][v] <<endl;
			//cout<<"\n "<<"distance["<<u<<"]  = "<<distance[u] <<" and distance["<<v<<"]  = "<<distance[v] <<endl;
			if( (false == visited[v])	//	node from u to v(v is not visited earlier)
				&& (graph[u][v] > 0)	//	their is valid path available between u->v
				&& ( (distance[u] + graph[u][v]) < distance[v] )   )
			{
				distance[v] = distance[u] + graph[u][v];
				parentNode[v] = u;
				//cout<<"\n "<<"Set List Path - distance["<<v<<"]  = "<<distance[v] <<endl;
			}
		}
	}
	
	PrintDistanceFromNode(0 , distance, parentNode);
	
}

void PrintDistanceFromNode(int src ,int distance[NoOfVertax], int parentNode[NoOfVertax])
{
	cout<<"\n **************************"<<endl;
	cout<<"Shortest Path from source node : "<< src << " to all other node is"<<endl;

	for(int u = 0 ; u< NoOfVertax ; ++u)
	{
		cout<<"\n\n\n from ["<<src<<"] to ["<<u<<"] is = "<<distance[u] <<", and parent is = "<<parentNode[u];

		int parent = parentNode[u];
		cout<<"\n node path from destinaion u="<<u<<", to src ="<<src<<", is = "<<u;
		while (parent != -1)
		{
			cout<<" <- "<< parent;
			parent = parentNode[parent];
		}
	}
}

/*
Output:
Vertex   Distance from Source
0                0
1                4
2                12
3                19
4                21
5                11
6                9
7                8
8                14


 Program Started *** Dijkstra-shortest-path-algorithm-Greedy-Algorithms.cpp

 **************************
Shortest Path from source node : 0 to all other node is
 from [0] to [0] is = 0, and parent is = -1
 node path from destinaion u=0, to src =0, is = 0

 from [0] to [1] is = 4, and parent is = 0
 node path from destinaion u=1, to src =0, is = 1 <- 0

 from [0] to [2] is = 12, and parent is = 1
 node path from destinaion u=2, to src =0, is = 2 <- 1 <- 0

 from [0] to [3] is = 19, and parent is = 2
 node path from destinaion u=3, to src =0, is = 3 <- 2 <- 1 <- 0

 from [0] to [4] is = 21, and parent is = 5
 node path from destinaion u=4, to src =0, is = 4 <- 5 <- 6 <- 7 <- 0

 from [0] to [5] is = 11, and parent is = 6
 node path from destinaion u=5, to src =0, is = 5 <- 6 <- 7 <- 0

 from [0] to [6] is = 9, and parent is = 7
 node path from destinaion u=6, to src =0, is = 6 <- 7 <- 0

 from [0] to [7] is = 8, and parent is = 0
 node path from destinaion u=7, to src =0, is = 7 <- 0

 from [0] to [8] is = 14, and parent is = 2
 node path from destinaion u=8, to src =0, is = 8 <- 2 <- 1 <- 0
 Program Ended
Press any key to continue . . .


*/