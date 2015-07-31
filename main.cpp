#include<list>

#include "Graph.h"
#include "dfs.h"


int main(){

	//create a new empty graph
	Graph<std::string> mygraph;
	
	//load the graph with some data
	mygraph.twowayConnect("Arad","Zerind", 75);
	mygraph.twowayConnect("Zerind", "Oraclea", 71);
	mygraph.twowayConnect("Oraclea", "Siblu", 151);
	mygraph.twowayConnect("Arad", "Siblu", 140);
	mygraph.twowayConnect("Arad", "Timisoara", 118);
	mygraph.twowayConnect("Timisoara", "Lugoj", 111);
	mygraph.twowayConnect("Lugoj", "Mehadia", 70);
	mygraph.twowayConnect("Mehadia", "Dobreta", 75);
	mygraph.twowayConnect("Dobreta", "Cralova", 120);
	mygraph.twowayConnect("Cralova", "Rim", 146);
	mygraph.twowayConnect("Cralova", "Pitesl", 138);
	mygraph.twowayConnect("Rim", "Pitesl", 97);
	mygraph.twowayConnect("Siblu", "Rim", 80);
	mygraph.twowayConnect("Siblu", "Fagaras", 99);
	mygraph.twowayConnect("Fagaras", "Bucharest", 211);
	mygraph.twowayConnect("Pitesl", "Bucharest", 101);
	mygraph.twowayConnect("Bucharest", "Glurglu", 90);
	mygraph.twowayConnect("Bucharest", "Urz", 85);
	mygraph.twowayConnect("Urz", "Hirsova", 98);
	mygraph.twowayConnect("Hirsova", "Eforle", 86);
	mygraph.twowayConnect("Urz", "Vaslul", 98);
	mygraph.twowayConnect("Vaslul", "Lasl", 92);
	mygraph.twowayConnect("Lasl", "Neamt", 87);

	//mygraph.AddEdge(mygraph.getVertex("second"), mygraph.AddVertex("third"), 12);
	//mygraph.AddEdge(mygraph.getVertex("second"), mygraph.AddVertex("fourth"), 20);
	//mygraph.AddEdge(mygraph.getVertex("third"), mygraph.AddVertex("destination"), 5); //dest created for first time
	//mygraph.AddEdge(mygraph.getVertex("destination"), mygraph.AddVertex("fourth"), 5);
	//mygraph.AddEdge(mygraph.getVertex("destination"), mygraph.AddVertex("destination"), 5);//delete this add check for itself in addedge
	//mygraph.AddEdge(mygraph.getVertex("fourth"), mygraph.AddVertex("destination"), 6);
	//mygraph.AddEdge(mygraph.getVertex("destination"), mygraph.AddVertex("second"), 5);
	//mygraph.AddEdge(mygraph.getVertex("second"), mygraph.AddVertex("deadend"), 12);

	//conduct DFS
	DFS<std::string> DFS(mygraph,std::string("Arad"),std::string("Bucharest"));
	
	//DFS.search();

	//int board[4][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
	
}