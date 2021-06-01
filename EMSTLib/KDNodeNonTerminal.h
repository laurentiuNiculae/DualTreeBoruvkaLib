#pragma once
#include "KDNode.h"
#include "BoundingBox.h"

template <int D>
class KDNodeNonTerminal : public KDNode<D>
{
	int d;
	Point<D>* p;
	KDNode<D>* left;
	KDNode<D>* right;
public:
	KDNodeNonTerminal(int d, Point<D>* p, BoundingBox<D> bb, KDNode<D>* left, KDNode<D>* right);
	bool isTerminal();
	int getDimension();
	float getMedian();
	KDNode<D>* getLeft();
	KDNode<D>* getRight();
	BoundingBox<D>& getbb();
	Point<D>* getFirstPoint();
};


template <int D>
KDNodeNonTerminal<D>::KDNodeNonTerminal(int d, Point<D>* p, BoundingBox<D> bb, KDNode<D>* left, KDNode<D>* right)
	: d(d), p(p), left(left), right(right)
{
	this->allConnected = false;
	this->upperBound = INFINITY;
	this->bb = bb;
}

template <int D>
bool KDNodeNonTerminal<D>::isTerminal()
{
	return false;
}

template <int D>
int KDNodeNonTerminal<D>::getDimension()
{
	return this->d;
}

template <int D>
float KDNodeNonTerminal<D>::getMedian()
{
	return (*this->p)[d];
}

template <int D>
KDNode<D>* KDNodeNonTerminal<D>::getLeft()
{
	return left;
}

template <int D>
KDNode<D>* KDNodeNonTerminal<D>::getRight()
{
	return right;
}

template <int D>
BoundingBox<D>& KDNodeNonTerminal<D>::getbb()
{
	return this->bb;
}

template <int D>
Point<D>* KDNodeNonTerminal<D>::getFirstPoint()
{
	return left->getFirstPoint();
}
