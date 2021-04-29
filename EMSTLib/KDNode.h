#pragma once
#define INFINITY 9999999999999
#include "BoundingBox.h"
template <int D>
class KDNode
{
public:
	float upperBound;
	bool allConnected;
	BoundingBox<D> bb;
	virtual bool isTerminal() = 0;
	virtual KDNode<D>* getLeft() = 0;
	virtual KDNode<D>* getRight() = 0;
	virtual BoundingBox<D>& getbb() = 0;
	virtual Point<D>* getFirstPoint() = 0;
};



