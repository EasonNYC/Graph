#pragma once

//The edge class holds the weights associated with travelling from one vertex to another 

template <class obj>
class Vertex;

template <class obj>
class Edge
{
	int weight;

public:

	Vertex<obj>* destination;

	Edge( Vertex<obj>* destination, int weight ) //regular
		:destination( destination ), weight( weight )
	{}
};
