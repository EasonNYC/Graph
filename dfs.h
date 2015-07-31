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
	std::deque<Vertex<obj>*> explore;
	
	std::list<Vertex<obj>*> solution;
	std::map<Vertex<obj>*, Vertex<obj>*> parent_list; //temporarily used for solution backtracking


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


	//forwards to visit
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


	//returns true if a node has been visited in the search
	virtual bool is_in_Visited( Vertex<obj>& node )
	{
		//return true if already in set of visited nodes
		return visited.find(&node) != visited.end();
		
	}

	//returns True if the vertex is in the explore deque.
	bool is_in_Explore( Vertex<obj>& node )
	{
		return std::find(explore.begin(), explore.end(), &node) != explore.end();
	}


	//work that should happen upon visiting a node (generate neighbors, update node etc.)
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
		explore.push_front( s );

		while (!explore.empty())
		{
			//pop the stack
			Vertex<obj>* ver = explore.front();
			std::cout << "removing " << ver->payload << " from the stack" << std::endl;
			explore.pop_front();

			//if we've never seen this vertex before, visit it
			if (is_in_Visited( *ver ) == false) 
			{
				//add to visited list
				ver->accept( *this );

				//if it's the goal (move to process node?)
				if (ver->payload == goal)
				{
					std::cout << "goal found: " << ver->payload << std::endl;

					//add current path to the the solution list (todo: make this a function)
					Vertex<obj>* startnode = G.getVertex( start );
					solution.push_front( ver );
					while (solution.front() != startnode)
					{
						solution.push_front( parent_list[solution.front()] );
						depth++;
					}

					//todo: mark bool solution found
					break; 
					
				}


				//for each neighbor push all vertecies we've never seen before to the front of the deque (todo: make this a function)
				for (Edge<obj>& r : ver->neighbors)
				{

					Vertex<obj>* temp = r.destination; //get neighbor
					if ( ((is_in_Visited( *temp )) || (is_in_Explore( *temp ))) == false) //check if is_in_explore should be here
					{
						std::cout << "adding " << r.destination->payload << " to explore " << is_in_Visited(*temp) << " " <<  is_in_Explore(*temp) << std::endl;
						explore.push_front( temp );
						parent_list[r.destination] = ver;
					}
				}
			}
		}
		//todo: add timeout check
		//print solution whether it's found or not
		printSolution();
		//return false?
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
		if (solution.size() == 0)
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
