#pragma once

#include <list>
#include <stack>
#include <iostream>
#include <map>
#include <set>
#include <string>


#include "Visitor.h"
#include "Edge.h"
#include "Graph.h"
#include "Timer.h"



template <class obj>
class DFS : public Visitor<obj>
{
	std::set<Vertex<obj>*> visited;
	std::deque<Vertex<obj>*> explore;

	std::list<Vertex<obj>*> solution;
	std::map<Vertex<obj>*, Vertex<obj>*> parent_list; 

	Graph<obj> G;

	obj start; //root 
	obj goal;

	int nodesVisted;
	int depth;
	bool goalFound;
	bool timedOut;

public:

	//Constructor
	DFS( Graph<obj>& g, obj& start, obj& goal )
		: G( g ), start( start ), goal( goal ), goalFound( false )
	{
		//auto-run search algo
		this->search();
	}


	//forwards to visit
	virtual void visitEdge( Edge<obj>& edge ) override
	{
		return visit( edge.destination );
	}


	//used in visitor pattern
	virtual void visit( Vertex<obj>* node ) override
	{
		//mark the node as visited
		visited.insert( node );
		nodesVisted++;

		//do work on the node (goal check, etc)
		processNode( *node );
	};


	//work that should happen upon visiting a node (generate neighbors, check for goal, update node etc.)
	virtual void processNode( Vertex<obj>& ver )
	{
		
		//check for goal (todo: change to functor)
		if (ver.payload == goal)
		{
			//let us know we have found a goal
			goalFound = true;
			std::cout << "goal found: " << ver.payload << std::endl;

			//add current path to the the solution list (todo: make this a function)
			Vertex<obj>* startnode = G.getVertex( start );
			solution.push_front( &ver );
			while (solution.front() != startnode)
			{
				solution.push_front( parent_list[solution.front()] );
				depth++;
			}
		}
		//else push any neighbors we've never seen before onto the explore deque
		else
		{
			
			for (Edge<obj>& edge : ver.neighbors)
			{
				Vertex<obj>* neighbor_vertex = edge.destination;
				if (((is_in_Visited( *neighbor_vertex )) || (is_in_Explore( *neighbor_vertex ))) == false)
				{
					//std::cout << "adding " << edge.destination->payload << " to explore " << std::endl;
					explore.push_front( neighbor_vertex );
					parent_list[edge.destination] = &ver; //track parents
				}
			}
		}
	}


	//returns true if a node has been visited in the search
	virtual bool is_in_Visited( Vertex<obj>& node )
	{
		//return true if already in set of visited nodes
		return visited.find( &node ) != visited.end();
	}


	//returns True if the vertex is in the explore deque.
	bool is_in_Explore( Vertex<obj>& node )
	{
		return std::find( explore.begin(), explore.end(), &node ) != explore.end();
	}


	//performs depth first search on the associated graph
	void search( double timeout = 20 /*secs*/ )
	{
		
		//reset stats
		depth = 0;
		nodesVisted = 0;
		goalFound = false;
		timedOut = false;

		std::cout << "Searching for " << goal << "... Starting at " << start <<  std::endl;
		//start the timer (used to detect timeout).
		Timer dfsTimer;
		
		//push the root node of the search to the the stack
		Vertex<obj>* root = G.getVertex( start );
		explore.push_front( root );

		while ((explore.empty() || goalFound || timedOut) == false)
		{
						
			//pop the stack
			Vertex<obj>* ver = explore.front();
			explore.pop_front();
			//std::cout << "removed " << ver->payload << " from the stack" << std::endl;

			//visit vertex, process it (check for goal, add neighbors to explore, etc.)
			if (!is_in_Visited( *ver ))
				ver->accept( *this );

			//check for timout
			if (dfsTimer.elapsed() > timeout)
				timedOut = true;
				
			
		}
	
		//Finally, print the solution and total search time.
		printSolution();
		std::cout << "total search time: " << dfsTimer.elapsed() << std::endl;

	}


	//returns a list of the solution path if it exists.
	std::list<Vertex<obj>*> getSolution() const
	{
		return solution;
	}


	//prints the solution if one is available.
	void printSolution() const
	{
		std::cout << std::endl << "------------------------" << std::endl << std::endl;

		//check for timeout
		if (timedOut)
		{
			std::cout << "search timed out. ";
		}

		//check for solution, return if there is none.
		if (solution.size() == 0)
		{
			std::cout << "no solution found." << std::endl;
			return;
		}
				
		std::cout << "solution: " << std::endl;

		//print path to solution
		for (auto& v : solution)
		{
			std::cout << v->payload;

			//format start and goal vertexes
			if (v->payload == start)
			{
				std::cout << " (start)";
			}
			else if (v->payload == goal)
			{
				std::cout << " (goal) " << std::endl;
				break;
			}

			//add text arrows
			std::cout << std::endl;
			std::cout << "    |" << std::endl << "    V" << std::endl;
		} 


		//print solution info (TODO: add time here)
		std::cout << "---------------" << std::endl;
		std::cout << "nodes visited: " << nodesVisted << std::endl;
		std::cout << "max depth: " << depth << std::endl;


	}
	
};
