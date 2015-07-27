/*
#include "dfs.h"

bool DFS::visitNode( Edge& node ) {

	//forward on to Vertex version of visitNode
	return visitNode( *node.destination );

}

bool DFS::visitNode( Vertex& node ) {
	
	//mark the node as visited
	visited.push_back( &node );
	nodesVisted++;

	//do some work on the node if nessisary
	this->processNode( node );
	return true;

}

bool DFS::isVisited( Vertex& node ) {

	//return true if already in list of visited nodes
	for ( auto &v : visited ) {
		if ( node.name == v->name ) {
			return true;
		}
	}

	return false;
}

void DFS::processNode( Vertex& node ) {
	
		//check for goal?
		if ( node.name == goal ) {
			//std::cout << "goal found: " << node.name << std::endl;
		}

		else {
			
			//do work here. perhaps add new nodes to the graph or add new children based on some function?
			std::cout << "doing work on  " << node.name << std::endl;
			
		}

	}
	
	

void DFS::search( ) {
	//reset stats
	depth = 0;
	nodesVisted = 0;

	//push the start node
	Vertex* s = G.getVertex( start );
	stack.push( s ); //do this in constructor
	
	while ( !stack.empty() ) {
	
		//pop the stack
		Vertex* ver = stack.top();
		std::cout << "removing " << ver->name << " from the stack" << std::endl;
		stack.pop();
		
		//if we've never seen it before
		if ( this->isVisited( *ver ) == false ) { 
			
			
			//visit the node (calls process node, then the vertex acknowledges
			ver->acceptVisitor( *this ); //calls process node then vertex acknowledges it is visited 

			//check if it's the goal
			if ( ver->name == goal ){
				std::cout << "goal found: " << ver->name << std::endl;

				Vertex* startnode = G.getVertex( start );

				//add current path to the the solution list
				solution.push_front( ver );
				while (solution.front() != startnode) {
					solution.push_front(parent_list[solution.front()]);
					depth++;
				}

				//print solution (make its own function)
				printSolution();
				
				return; //return path(solution) + this node
			}
				

			//add all vertecies we've never seen before to the stack
			for ( Edge& r : ver->neighbors ) {

				Vertex* temp = r.destination;
				if ( this->isVisited( *temp ) == false ) {
					std::cout << "adding " << r.destination->name << " to the stack" << std::endl;
					stack.push( temp );
					parent_list[r.destination] = ver;
				}

			}
		}
	}
	//return
}

std::list<Vertex*> DFS::getSolution() const {
	return solution;
} 
void DFS::printSolution() {
	//check for solution
	if ( solution.front() == nullptr ) {
		std::cout << "no solution found." << std::endl;
		return;
	}

	//print
	std::cout << "nodes visited: " << nodesVisted << std::endl;
	std::cout << "solution depth: " << depth << std::endl;
	std::cout << "solution: " << std::endl;
	for (auto& v : solution) {
		std::cout << v->name;
		if (v->name == start) {
			std::cout << "(start)-->";
		}
		else if (v->name == goal) {
			std::cout << "(goal) ";
		}
		
		else {
			std::cout << "-->";
		}
	}

}//prints the solution if one is available.
*/