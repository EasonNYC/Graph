#pragma once

#include <iostream>
#include <list>

#include "Vertex.h"

//Graph Class holds a collection of verteces. todo: vertex factory 
template <class obj>
class Graph
{
private:

	std::list<Vertex<obj>*> vertices; //todo: change to set

public:
	//constructor and destructor (todo: finish these)
	Graph() = default;
	~Graph() = default;

	//Takes an obj and adds a vertex to our list of verticies. returns pointer to the vertex.
	Vertex<obj>* AddVertex( obj payload )
	{ //pass by ref?

		//check if payload already exists among all vertices. 
		for (auto& v : vertices)
		{
			if (v->payload == payload)
			{
				//return vertex if it exists
				return v;
			}
		}


		//create new Vertex object and include it in our collection of verticies. 
		Vertex<obj>* vptr = new Vertex<obj>( payload );
		vertices.push_back( vptr );

		return vptr;
	}

	//method to add an edge from source vertex to destination vertex. checks vertex using its addr
	void AddEdge( Vertex<obj>* sourcenode, Vertex<obj>* destinationode, int weight )
	{
		//check for self assignment (based on addr)
		if (&sourcenode == &destinationode)
		{
			std::cout << "self assignment! via address" << sourcenode << std::endl;
		}

		/*find the source vertex in the graph's list of vertices. Then add an edge to destination vertex within
		its list of neighbors. uses vertex name to match.*/
		for (auto& v : vertices)
		{
			if (v->payload == sourcenode->payload)
			{
				// find source vertex
				v->neighbors.push_back( Edge<obj>( destinationode, weight ) );
			}
		}
	}

	//Adds an edge from sourcenode to destination node via a copy of the objects
	void AddEdge( obj source, obj destination, int weight )
	{
		//check self assignment
		if (source == destination)
		{
			std::cout << "self assignment detected!" << std::endl;
			return;
		}

		//check existing verticies for the name of this vertex and destination vertex...
		for (auto& v : vertices)
		{
			// first find source vertex
			if (v->payload == source)
			{
				//and if destination also exists
				for (auto& x : vertices)
				{
					if (x->payload == destination)
					{
						//connect them
						v->neighbors.push_back( Edge<obj>( x, weight ) );
						return;
					}
				}

				//otherwise create new vertex from destination and connect to found vertex
				v->neighbors.push_back( Edge<obj>( this->AddVertex( destination ), weight ) );

				return;
			}
		}

		//else we have two new vertecies. Create 2 new nodes and connect them
		AddEdge( AddVertex( source ), AddVertex( destination ), weight );
	}

	//function to return a vertex based on payload ==. 
	Vertex<obj>* getVertex( obj& thisobject )
	{
		for (auto& v : vertices)
		{
			if (v->payload == thisobject)
			{
				return v;// return the vertex
			}
		}

		//otherwise
		return nullptr;
	}

	//two way connection between vertecies
	void twowayConnect( obj source, obj destination, int weight )
	{
		AddEdge( source, destination, weight );
		AddEdge( destination, source, weight );
	}

	//one way connection from source vertex to destination vertex
	void onewayConnect( obj source, obj destination, int weight )
	{
		AddEdge( source, destination, weight );
	}
};
