#pragma once
#include "KDTree.h"
#include "Edge.h"
#include "DisjointSet.h"
#include "BoundingBox.h"
#include <algorithm>
#include <set>

using std::set;

template <int D>
class DualTreeBoruvka
{
	KDTree<D>& tree;
	vector<Point<D>*>& points;
	
	map<conexComponent<D>*, float> dCq;
	map<conexComponent<D>*, Edge<D>*> eCq;
	map<KDNode<D>*, float> dQ;


	bool areSameComponent(KDNode<D>* Q, KDNode<D>* R);
	void updateFullyConnectedStates(KDNode<D>* node);
public:
	bool printEveryIterationFlag;
	bool printLastIterationFlag;
	bool printProgressFlag;
	DisjointSet<D> pointSet;
	DualTreeBoruvka(KDTree<D>& tree, vector<Point<D>*>& points);
	set<Edge<D>> findEMST(KDNode<D>* q, int treeSize);
	void FindComponentNeighbors(KDNode<D>* Q, KDNode<D>* R, vector<Edge<D>* >& e);
	void UpdateTree(KDNode<D>* q);
};

template <int D>
bool DualTreeBoruvka<D>::areSameComponent(KDNode<D>* Q, KDNode<D>* R)
{
	if (Q->allConnected && R->allConnected &&
		pointSet.Find(Q->getFirstPoint()) == pointSet.Find(R->getFirstPoint()))
	{
		return true;
	}
	return false;
}

template <int D>
DualTreeBoruvka<D>::DualTreeBoruvka(KDTree<D>& tree, typename vector<Point<D>*>& points)
	: tree(tree), points(points), printEveryIterationFlag(false), printLastIterationFlag(false), printProgressFlag(false)
{
	for (auto i : points)
	{
		pointSet.MakeSet(i);
	}

	for (auto i : pointSet.getConexComponents())
	{
		dCq.insert(pair<conexComponent<D>*, float>(i, INFINITY));
	}
}

template <int D>
set<Edge<D>> DualTreeBoruvka<D>::findEMST(KDNode<D>* q, int treeSize)
{
	set<Edge<D>> E;
	vector<Edge<D>* > e;
	int i = 1;
	while (E.size() < treeSize - 1)
	{
		e.clear();
		UpdateTree(q);
		FindComponentNeighbors(q, q, e);
		if (eCq.size() == 0)
		{
			for (auto& i : dQ)
			{
				i.second = std::numeric_limits<float>::max();
			}
		}
		for (auto i : eCq)
		{
			pointSet.Union(i.second->getNode1(), i.second->getNode2());
			E.emplace(*i.second);
		}
		if (printEveryIterationFlag == true)
		{
			for (auto i : E)
			{
				cout << i.toString() << "\n";
			}
		}
		
		updateFullyConnectedStates(q);
		if (printProgressFlag == true)
		{
			std::cout << "Progress: " <<  (float)(E.size()) << "/" <<  (float)(treeSize - 1) << " || " << "ConexNr: "<< pointSet.allComponents.size()  <<  std::endl;
		}
		i++;

	}
	if (!printEveryIterationFlag && printLastIterationFlag)
	{
		for (auto i : E)
		{
			cout << i.toString() << "\n";
		}
	}
	std::cout << "\n";

	return E;
}

template <int D>
void DualTreeBoruvka<D>::FindComponentNeighbors(KDNode<D>* Q, KDNode<D>* R, vector<Edge<D>* >& e)
{
	if (Q->allConnected && R->allConnected &&
		pointSet.Find(Q->getFirstPoint()) == pointSet.Find(R->getFirstPoint())
		)
	{
		return;
	}
	if (bbDistance(Q->getbb(), R->getbb()) > dQ[Q] + 45)
	{
		bbDistance(Q->getbb(), R->getbb());
		return;
	}
	if (Q->isTerminal() && R->isTerminal())
	{
		Point<D>* closestPoint = nullptr;
		dQ[Q] = 0;
		for (auto q : ((KDNodeTerminal<D>*)Q)->getPoints())
		{
			closestPoint = nullptr;
			for (auto r : ((KDNodeTerminal<D>*)R)->getPoints())
			{
				if (pointSet.Find(q) != pointSet.Find(r))
				{
					if (distance(*q, *r) < dCq[pointSet.Find(q)])
					{
						
						dCq[pointSet.Find(q)] = distance(*q, *r);
						if (q < r)
						{
							eCq[pointSet.Find(q)] = new Edge<D>(q, r);
						}
						else
						{
							eCq[pointSet.Find(q)] = new Edge<D>(r, q);
						}

						closestPoint = r;
					}
				}
			}
			if (dQ[Q] < dCq[pointSet.Find(q)])
			{
				dQ[Q] = dCq[pointSet.Find(q)];
			}
		}
		//dQ.insert(pair<KDNode<D>*, float>(Q, 0));
		//
		//for (auto q : ((KDNodeTerminal<D>*)Q)->getPoints())
		//{
		//	if (dQ[Q] < dCq[pointSet.Find(q)])
		//	{
		//		dQ[Q] = dCq[pointSet.Find(q)];
		//	}
		//}
	}
	else
	{
		FindComponentNeighbors(Q->getLeft(), R->getLeft(), e);
		FindComponentNeighbors(Q->getRight(), R->getLeft(), e);
		FindComponentNeighbors(Q->getLeft(), R->getRight(), e);
		FindComponentNeighbors(Q->getRight(), R->getRight(), e);
		dQ[Q] = std::max(dQ[Q->getLeft()], dQ[Q->getRight()]);
	}

}

template <int D>
void DualTreeBoruvka<D>::UpdateTree(KDNode<D>* q)
{
	for (auto& i : dCq)
	{
		i.second = std::numeric_limits<float>::max();
	}
	//for (auto& i : dQ)
	//{
	//	i.second = std::numeric_limits<float>::max();
	//}
	eCq.clear();
}

template<int D>
inline void DualTreeBoruvka<D>::updateFullyConnectedStates(KDNode<D>* node)
{
	if (node->allConnected == true)
	{
		return;
	}
	if (node->isTerminal())
	{
		bool fullyConnected = true;
		vector<Point<D>*>& currentPoints = ((KDNodeTerminal<D>*)node)->getPoints();

		conexComponent<D>* firstComponent = pointSet.Find(currentPoints[0]);
		for (auto i : currentPoints)
		{
			if (firstComponent != pointSet.Find(i))
			{
				fullyConnected = false;
				break;
			}
			//fullyConnected = fullyConnected & (firstComponent == pointSet.Find(i));
		}
		node->allConnected = fullyConnected;
	}
	else
	{
		updateFullyConnectedStates(node->getLeft());
		updateFullyConnectedStates(node->getRight());
		if (node->getLeft()->allConnected && node->getRight()->allConnected &&
			areSameComponent(node->getLeft(), node->getRight()))
		{
			node->allConnected = true;
		}
	}
}