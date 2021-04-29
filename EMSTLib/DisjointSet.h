#pragma once
#include "Point.h"
#include <map>
#include <vector>
#include <set>
using std::map;
using std::set;

template <int D>
struct conexComponent {
	conexComponent<D>* parent;
	Point<D>* point;
	int size;
	conexComponent(Point<D>* point)
		: parent(this), point(point), size(1) { };
};


template <int D>
using PointToNode = std::pair<Point<D>*, conexComponent<D>*>;

template<int D>
class DisjointSet
{
	map<Point<D>*, conexComponent<D>*> elementsToNodes;
	set<conexComponent<D>*> allComponents;
	Point<D>* parent(Point<D>* point);
public:
	void MakeSet(Point<D>* newPoint);
	conexComponent<D>* Find(Point<D>* searchPoint);
	conexComponent<D>* Find(conexComponent<D>* searchNode);
	void Union(Point<D>* point1, Point<D>* point2);
	void Union(conexComponent<D>* node1, conexComponent<D>* node2);
	std::vector<conexComponent<D>*> getConexComponents();
};

template <int D>
void DisjointSet<D>::MakeSet(Point<D>* newPoint)
{
	elementsToNodes.insert(PointToNode<D>(newPoint, new conexComponent<D>(newPoint)));
	allComponents.insert(elementsToNodes[newPoint]);
}

template <int D>
conexComponent<D>* DisjointSet<D>::Find(conexComponent<D>* searchNode)
{
	while (searchNode != searchNode->parent)
	{
		searchNode = searchNode->parent;
	}
	return searchNode;
}

template <int D>
conexComponent<D>* DisjointSet<D>::Find(Point<D>* searchPoint)
{
	conexComponent<D>* searchNode = elementsToNodes[searchPoint];
	return Find(searchNode);
}

template <int D>
void DisjointSet<D>::Union(Point<D>* point1, Point<D>* point2)
{
	conexComponent<D>* node1 = Find(point1);
	conexComponent<D>* node2 = Find(point2);
	Union(node1, node2);
}

template <int D>
void DisjointSet<D>::Union(conexComponent<D>* node1, conexComponent<D>* node2)
{
	node1 = Find(node1);
	node2 = Find(node2);
	if (node1 == node2)
	{
		return;
	}
	if (node1->size < node2->size)
	{
		conexComponent<D>* aux = node1;
		node1 = node2;
		node2 = aux;
	}
	// make node1(the bigger one) the new root
	allComponents.erase(node2);
	node2->parent = node1;
	node1->size += node2->size;
}

template <int D>
std::vector<conexComponent<D>*> DisjointSet<D>::getConexComponents()
{
	return std::vector<conexComponent<D>*>(allComponents.begin(), allComponents.end());
}

template <int D>
Point<D>* DisjointSet<D>::parent(Point<D>* point)
{
	return nullptr;
}