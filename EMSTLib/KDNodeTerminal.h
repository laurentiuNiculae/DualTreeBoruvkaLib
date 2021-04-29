#pragma once
#include "KDNode.h"
#include "BoundingBox.h"
#include <vector>
#include "Point.h"
using std::vector;

template <int D>
class KDNodeTerminal : public KDNode<D>
{
	vector<Point<D>*>& storedPoints;
public:
	KDNodeTerminal<D>(typename vector<Point<D>*>& pointPartition);
	bool isTerminal();
	KDNode<D>* getLeft();
	KDNode<D>* getRight();
	vector<Point<D>*>& getPoints();
	BoundingBox<D>& getbb();
	Point<D>* getFirstPoint();
};


template <int D>
KDNodeTerminal<D>::KDNodeTerminal(typename vector<Point<D>*>& pointPartition)
	: storedPoints(pointPartition)
{
	this->allConnected = false;
	this->upperBound = INFINITY;
	this->bb = BoundingBox<D>(pointPartition.begin(), pointPartition.end());
}

template <int D>
bool KDNodeTerminal<D>::isTerminal()
{
	return true;
}

template <int D>
KDNode<D>* KDNodeTerminal<D>::getLeft()
{
	return this;
}

template <int D>
KDNode<D>* KDNodeTerminal<D>::getRight()
{
	return this;
}

template <int D>
vector<Point<D>*>& KDNodeTerminal<D>::getPoints()
{
	return storedPoints;
}

template <int D>
BoundingBox<D>& KDNodeTerminal<D>::getbb()
{
	return this->bb;
}

template <int D>
Point<D>* KDNodeTerminal<D>::getFirstPoint()
{
	return storedPoints[0];
}
