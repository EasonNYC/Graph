#pragma once

#include <iostream>
#include <list>

//Fwd Declarations
template <class obj> class Edge;
template <class obj> class Visitor;

//The Vertex Class holds the payload/object to be searched. Is connected to other verteces by a weighted edge.
template <class obj>
class Vertex
{
public:

	//public members
	obj payload;
	bool visited;
	std::list<Edge<obj>> neighbors; //make private?

	//Constructor
	Vertex( const obj& payload )
		: payload( payload ), visited( false )
	{ }

	//destructor
	virtual ~Vertex()
	{ }

	//adds an edge object to this vertecies neighbors
	void addEdge( Vertex* destination, int weight )
	{
		//check if edge is already a neighbor. Return if true.
		for (auto& v : neighbors)
		{
			if (v.destination->payload == payload)
			{
				return;
			}
		}
		//else add new neighbor
		neighbors.push_back( Edge<obj>( destination, weight ) );
	}

	// what the vertex should do (if anything) if it is being visited
	virtual void accept( Visitor<obj>& v )
	{
		//v.visitNode(static_cast<derived&>(this));
		v.visit( this );

		//take this stuff out later 
		visited = true;
		std::cout << payload << " is being visited" << std::endl;
	}
};
