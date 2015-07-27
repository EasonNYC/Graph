#pragma once

#include "Edge.h"
#include "Vertex.h"

//Visitor interface inherited by each search type.
template<class obj>
class NodeVistorInterface{

public:
	//destructor
	virtual ~NodeVistorInterface() {}

	//pure virtual
	virtual void visitEdge(Edge<obj>& node) = 0;
	virtual void visitNode(Vertex<obj>& node) = 0;

};
