/*
//https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
//Bellman–Ford–Moore algorithm.[1]

//https://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/
Dynamic Programming | Set 23 (Bellman–Ford Algorithm)
Given a graph and a source vertex src in graph, 
find shortest paths from src to all vertices in the given graph. 
The graph may contain negative weight edges.

We have discussed Dijkstra’s algorithm for this problem. 
Dijksra’s algorithm is a Greedy algorithm and time complexity is O(VLogV) 
(with the use of Fibonacci heap). Dijkstra doesn’t work for Graphs with 
negative weight edges, Bellman-Ford works for such graphs. 
Bellman-Ford is also simpler than Dijkstra and suites well for distributed systems. 
But time complexity of Bellman-Ford is O(VE), which is more than Dijkstra.

//https://en.cppreference.com/w/cpp/container
*/
//https://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/

/*
Johnson's algorithm
	http://joonki-jeong.blogspot.com/2013/01/johnsons-algorithm.html
	Johnson's algorithm finds shortest paths between all pairs by using both Dijkstra's algorithm and the Bellman-Ford algorithm.
	Dijkstra's algorithm and the Bellman-Ford algorithm finds shortest paths from the single source vertex to others. Dijkstra's algorithm runs in O(n*lg n) to compute shortest paths while the Bellman-Ford runs in O(n*m), where n is the number of vertices and m is the number of edges. Thus, Dijkstra's algorithm is strictly faster than the Bellman-Ford for both sparse and dense graphs. However, Dijkstra's algorithm has one shortcoming, which is the constraint that the input graph must not have negative cost edges. On the other hand, the Bellman-Ford allows the input graph to have negative cost edges, but no negative cost cycles.


*/




#include <iostream>
using namespace std;

struct Edge
{
	int src,dst,weight;
	Edge(int src = -1, int dst = -1, int weight = INT_MAX):src(src),dst(dst),weight(weight)
	{}

};

struct Graph
{
	int noV;
	int noE;
	int counter;
	struct Edge* pEdges;

	Graph(int noV , int noE): noV(noV) , noE(noE) , counter(-1), pEdges(new Edge[noE])
	{	}

	void AddEdgeToGraph(int src , int srv , int weight)
	{
		pEdges[++(counter)] =  Edge(src,srv,weight);
	}

	void PrintGraph(int *distance , bool islinear = false)
	{
		cout<<"\n ************************** \n";
		for(int u =0 ; u < noV ; ++u)
		{
			if(islinear)
				cout<<"\t"<<distance[u];
			else
				cout<<"\n node No = " << u <<", distance = "<<distance[u];
		}
	}
};


void BellmanFord(Graph * grp, int src )
{
	int* distance = new int[grp->noV];
	for( int u = 0 ; u < grp->noV ; ++u)
		distance[u] = INT_MAX;

	distance[src] = 0;
	//===========================================================================
	for(int counter = 0 ; counter < (grp->noV - 1) ; ++counter)
	{
		for(int e = 0 ; e < grp->noE ; ++e)
		{
			int u = grp->pEdges[e].src;
			int v = grp->pEdges[e].dst;
			int weight = grp->pEdges[e].weight;
			if(  ( distance[u] != INT_MAX) && (distance[v] > distance[u] + weight) )
			{
				distance[v] = distance[u] + weight;
			}	
			//cout<<"\n\n\n after counter ["<< counter<<"] and e ["<<e<<"] ";
			grp->PrintGraph(distance , true);
		}
	}
	//test negative weights
	//===========================================================================
	for(int e = 0 ; e < (grp->noE) ; ++e)
	{
		int u = grp->pEdges[e].src;
		int v = grp->pEdges[e].dst;
		int weight = grp->pEdges[e].weight;
		if(  ( distance[u] != INT_MAX) && (distance[v] > distance[u] + weight) )
		{
			cout<<"\n GRAPG contains negaive weight cycle !!!!! \n\n"<<endl;
			return;
		}			
	}
	//===========================================================================
	grp->PrintGraph(distance);
}

//================================================================
void main()
{
	cout<<"\n Program Started :"<<__FILE__<<endl;
	Graph * grp = new Graph(5, 8);
	
	grp->AddEdgeToGraph(0,1,-1);
	//grp->AddEdgeToGraph(0,2,4);
	grp->AddEdgeToGraph(2,0,-1);//negaitve cycle

	grp->AddEdgeToGraph(1,3,2);
	grp->AddEdgeToGraph(1,4,2);
	
	//grp->AddEdgeToGraph(1,2,3);
	grp->AddEdgeToGraph(1,2,-1);		//negaitve cycle


	grp->AddEdgeToGraph(3,1,1);
	grp->AddEdgeToGraph(3,2,5);

	grp->AddEdgeToGraph(4,3,-3);
	

	BellmanFord(grp, 0);

	cout<<"\n Program Ended "<<endl;
}
/*
 Program Started :Bellman-Ford-Moore-grsph-alog-withnegative-weight.cpp
 **************************
 node No = 0, distance = 0
 node No = 1, distance = -1
 node No = 2, distance = 2
 node No = 3, distance = -2
 node No = 4, distance = 1
 Program Ended
Press any key to continue . . .
*/

/* negative cycle case
        -6      -4      -5      -5      -2
 GRAPG contains negaive weight cycle !!!!!
*/