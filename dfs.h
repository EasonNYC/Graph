#pragma once

#include "Visitor.h"
#include <list>
#include <stack>
#include <iostream>
#include <map>
#include <set>
#include <string>


#include "Edge.h"
#include "Graph.h"

template <class obj>
class DFS : public Visitor<obj>
{
	std::set<Vertex<obj>*> visited;
	std::list<Vertex<obj>*> solution;
	std::stack<Vertex<obj>*> stack; //make obsolete
	std::deque<Vertex<obj>*> to_explore;
	std::map<Vertex<obj>*, Vertex<obj>*> parent_list; //used for solution path backtracking


	obj start; //root 
	obj goal;
	int nodesVisted;
	int depth;

	Graph<obj> G;

public:

	//Constructor
	DFS( Graph<obj>& g, obj& start, obj& goal )
		: G( g ), start( start ), goal( goal )
	{
		this->search();
	}


	//forwards to Vertex version of visit
	virtual void visitEdge( Edge<obj>& edge ) override
	{
		return visit( edge.destination );
	}


	//used for visitor pattern
	virtual void visit( Vertex<obj>* node ) override
	{
		//mark the node as visited
		visited.insert( node );
		nodesVisted++;

		//do some work on the node
		this->processNode( *node );
	};


	//returns a bool of whether a node has been visited in the search
	virtual bool isVisited( Vertex<obj>& node )
	{
		//return true if already in set of visited nodes
		if (visited.find( &node ) != visited.end())
		{
			return true;
		}

		return false;
	}


	//work that should happen upon visiting a node
	virtual void processNode( Vertex<obj>& node )
	{
		//check for goal
		if (node.payload == goal)
		{
			//std::cout << "goal found: " << node.name << std::endl;
		}

		else
		{
			//do work here. perhaps add new nodes to the graph or add new children based on some function?
			//std::cout << "doing work on  " << node.payload << std::endl;
		}
	}


	//performs depth first search on the associated graph
	void search()
	{
		//reset stats
		depth = 0;
		nodesVisted = 0;

		//push the root node to the top of the stack
		Vertex<obj>* s = G.getVertex( start );
		stack.push( s );

		while (!stack.empty())
		{
			//pop the stack
			Vertex<obj>* ver = stack.top();
			std::cout << "removing " << ver->payload << " from the stack" << std::endl;
			stack.pop();

			//if we've never seen this vertex before
			if (this->isVisited( *ver ) == false)
			{
				//this->visitNode( *ver ); //add to visited list
				ver->accept( *this );

				//check if it's the goal
				if (ver->payload == goal)
				{
					std::cout << "goal found: " << ver->payload << std::endl;

					Vertex<obj>* startnode = G.getVertex( start );

					//add current path to the the solution list (todo: make private function)
					solution.push_front( ver );
					while (solution.front() != startnode)
					{
						solution.push_front( parent_list[solution.front()] );
						depth++;
					}

					//todo: mark bool solution found

					//remove this later
					printSolution();

					return;
				}


				//for each neighbor add all vertecies we've never seen before to the stack
				for (Edge<obj>& r : ver->neighbors)
				{

					Vertex<obj>* temp = r.destination; //get vertex
					if (this->isVisited( *temp ) == false) // or is in stack already
					{
						std::cout << "adding " << r.destination->payload << " to the stack" << std::endl;
						stack.push( temp );
						parent_list[r.destination] = ver;
					}
				}
			}
		}
		//return
	}

	//returns a pointer to the first element of the solution if it exists.
	std::list<Vertex<obj>*> getSolution() const
	{
		return solution;
	}


	//prints the solution if one is available.
	void printSolution() const
	{
		std::cout << std::endl << "------------------------" << std::endl << std::endl;

		//check for solution
		if (solution.front() == nullptr)
		{
			std::cout << "no solution found." << std::endl;
			return;
		}

		//print solution info (TODO: add if solution found or not)
		std::cout << "nodes visited: " << nodesVisted << std::endl;
		std::cout << "depth reached: " << depth << std::endl << std::endl;
		std::cout << "solution: " << std::endl;

		//print path to solution
		for (auto& v : solution)
		{
			std::cout << v->payload;
			if (v->payload == start)
			{
				std::cout << " (start)";
			}
			else if (v->payload == goal)
			{
				std::cout << " (goal) " << std::endl;
				break;
			}
			std::cout << std::endl;
			std::cout << "    |" << std::endl << "    V" << std::endl;
		}
	}
};
