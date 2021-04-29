#pragma once
#include "Point.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

template <int D>
class Edge
{
	Point<D>* p1;
	Point<D>* p2;
public:
	Edge(Point<D>* p1, Point<D>* p2);
	string toString();
	Point<D>* getNode1();
	Point<D>* getNode2();
	bool operator ==(Edge<D>& edge);
	bool operator !=(Edge<D>& edge);
	bool operator <(const Edge<D>& edge) const;
};

template <int D>
Edge<D>::Edge(Point<D>* p1, Point<D>* p2)
{
	this->p1 = p1;
	this->p2 = p2;
}

template <int D>
string Edge<D>::toString()
{
	return p1->toString().append(p2->toString());
}

template <int D>
Point<D>* Edge<D>::getNode1()
{
	return p1;
}

template <int D>
Point<D>* Edge<D>::getNode2()
{
	return p2;
}

template <int D>
bool Edge<D>::operator==(Edge<D>& edge)
{
	if (p1 != edge.p1 || p2 != edge.p2)
	{
		return false;
	}
	return true;
}

template <int D>
bool Edge<D>::operator!=(Edge<D>& edge)
{
	if (p1 == edge.p1 && p2 == edge.p2)
	{
		return false;
	}
	return true;
}

template <int D>
bool Edge<D>::operator<(const Edge<D>& edge) const
{
	if (p1 < edge.p1)
	{
		return true;
	}
	else
	{
		if (p1 == edge.p1 && p2 < edge.p2)
		{
			return true;
		}
	}
	return false;
}
