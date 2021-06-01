#pragma once
#include "KDNode.h"
#include "KDNodeNonTerminal.h"
#include "KDNodeTerminal.h"
#include <vector>
#include <iostream>
#include "Point.h"
#include <algorithm>
#include <queue>
#include <functional>

#define not !
#define or ||

using std::pair;
using std::vector;
using std::cout;
using std::queue;

// typedef pair<vector<Point<D>*>, vector<Point<D>*>> SplitedVector;
template <int D>
using SplitedVector = pair<vector<Point<D>*>, vector<Point<D>*>>;

template <int D>
using SplitedBoundingBox = pair<BoundingBox<D>, BoundingBox<D>>;

template <int D>
class KDTree
{
	int k;
	BoundingBox<D> fullBB;
	KDNode<D>* root;
	KDNode<D>* makeTerminal(typename vector<Point<D>*>& pointsPartition, BoundingBox<D> bb);
	KDNode<D>* makeNonTerminal(int d, Point<D>* p, BoundingBox<D> bb, KDNode<D>* left, KDNode<D>* right);
	KDNode<D>* buildTree(typename vector<Point<D>*>& points, Point<D>* lastSplitMade, BoundingBox<D> lastBB);
	int spreadest(int d, typename vector<Point<D>*> pointsPartition);
	Point<D>* medianPoint(int d, typename vector<Point<D>*> pointsPartition);
	SplitedVector<D>& splitVector(int d, Point<D>* p, typename vector<Point<D>*>& pointsPartition);
	SplitedBoundingBox<D> splitBoundingBox(int d, Point<D>* splitPoint, BoundingBox<D> lastBB);

	//typedef pair<vector<Point<D>*>, vector<Point<D>*>> SplitedVector;

public:
	KDTree<D>(int k, vector<Point<D>*> points);
	void dfsPrint();
	void bfs(int h, typename KDNode<D>* node);
	void bfsBB(int h, KDNode<D>* node);
	void bfsWithVisitor(int h, typename KDNode<D>* node, void (*visitor)(KDNode<D>* node));
	void bfsWithVisitor2(int h, typename KDNode<D>* node, std::function<void(KDNode<D>*)> visitor);
	void bfsPrint();
	KDNode<D>* getRoot();
};


template <int D>
KDTree<D>::KDTree(int k, typename vector<Point<D>*> points)
{
	this->k = k;
	fullBB = BoundingBox<D>(points.begin(), points.end());
	this->root = buildTree(points, nullptr, fullBB);
}

template <int D>
KDNode<D>* KDTree<D>::buildTree(typename vector<Point<D>*>& points, Point<D>* lastSplitPoint, BoundingBox<D> lastBB)
{
	int d = 0, j, maxspread;
	Point<D>* p;

	if (points.size() <= k)
	{
		return this->makeTerminal(points, lastBB);
	}
	maxspread = 0;
	for (j = 0; j < D; j++)
	{
		if (spreadest(j, points) > maxspread)
		{
			maxspread = spreadest(j, points);
			d = j;
		}
	}
	std::sort(points.begin(), points.end(), [d](Point<D>* a, Point<D>* b) { return (*a)[d] < (*b)[d]; });
	p = this->medianPoint(d, points);
	SplitedVector<D>& pointPartition = this->splitVector(d, p, points);
	SplitedBoundingBox<D> boundingBoxPair = this->splitBoundingBox(d, p, lastBB);
	return this->makeNonTerminal(d, p, lastBB, this->buildTree(pointPartition.first, p, boundingBoxPair.first), this->buildTree(pointPartition.second, p, boundingBoxPair.second));
}

template <int D>
KDNode<D>* KDTree<D>::makeTerminal(typename vector<Point<D>*>& pointsPartition, BoundingBox<D> bb)
{
	return new KDNodeTerminal<D>(pointsPartition, bb);
}

template <int D>
KDNode<D>* KDTree<D>::makeNonTerminal(int d, Point<D>* p, BoundingBox<D> bb, KDNode<D>* left, KDNode<D>* right)
{
	return new KDNodeNonTerminal<D>(d, p, bb, left, right);
}

template <int D>
void KDTree<D>::dfsPrint()
{
	queue<KDNode<D>*> nodeQueue;
	KDNode<D>* currentNode = nullptr;

	nodeQueue.push(root);
	while (not nodeQueue.empty())
	{
		currentNode = nodeQueue.front();
		nodeQueue.pop();
		if (not currentNode->isTerminal())
		{
			cout << ((KDNodeNonTerminal<D>*)currentNode)->getDimension();
			cout << " - ";
			cout << ((KDNodeNonTerminal<D>*)currentNode)->getMedian();
			cout << std::endl;
			nodeQueue.push(((KDNodeNonTerminal<D>*)currentNode)->getLeft());
			nodeQueue.push(((KDNodeNonTerminal<D>*)currentNode)->getRight());
		}
	}
}

template <int D>
void KDTree<D>::bfsPrint()
{
	bfs(0, root);
}

template <int D>
KDNode<D>* KDTree<D>::getRoot()
{
	return root;
}

template <int D>
void KDTree<D>::bfs(int h, KDNode<D>* node)
{
	if (node->isTerminal())
	{
		int contor = 0;
		for (auto i : ((KDNodeTerminal<D>*)node)->getPoints())
		{
			if (contor == 0)
			{
				for (int k = 0; k < h; k++) cout << "   -";
			}
			else
			{
				for (int k = 0; k < h; k++) cout << "    ";
			}
			cout << i->toString();
			cout << std::endl;
			contor++;
		}
	}
	else
	{
		for (int k = 0; k < h; k++) cout << "    ";
		cout << "[" << "d=" << ((KDNodeNonTerminal<D>*)node)->getDimension() << "p=" << ((KDNodeNonTerminal<D>*)node)->getMedian() << "]";
		cout << std::endl;
		bfs(h + 1, ((KDNodeNonTerminal<D>*)node)->getLeft());
		bfs(h + 1, ((KDNodeNonTerminal<D>*)node)->getRight());
	}
}

template <int D>
void KDTree<D>::bfsBB(int h, KDNode<D>* node)
{
	if (node->isTerminal())
	{
		for (int k = 0; k < h; k++) cout << "---";
		cout << "(" << node->bb.minimalPoint.toString() << ")" << "(" << node->bb.maximalPoint.toString() << ")\n";
		int contor = 0;
		for (auto i : ((KDNodeTerminal<D>*)node)->getPoints())
		{
			if (contor == 0)
			{
				for (int k = 0; k < h; k++) cout << "   -";
			}
			else
			{
				for (int k = 0; k < h; k++) cout << "    ";
			}
			cout << i->toString();
			cout << std::endl;
			contor++;
		}
	}
	else
	{
		for (int k = 0; k < h; k++) cout << "    ";
		cout << "(" << node->bb.minimalPoint.toString() <<")" << "(" << node->bb.maximalPoint.toString() << ")";
		cout << std::endl;
		bfsBB(h + 1, ((KDNodeNonTerminal<D>*)node)->getLeft());
		bfsBB(h + 1, ((KDNodeNonTerminal<D>*)node)->getRight());
	}
}

template<int D>
inline void KDTree<D>::bfsWithVisitor(int h, typename KDNode<D>* node, void (*visitor)(KDNode<D>* node))
{
	visitor(node);
	bfs(h + 1, ((KDNodeNonTerminal<D>*)node)->getLeft());
	bfs(h + 1, ((KDNodeNonTerminal<D>*)node)->getRight());
}

template<int D>
inline void KDTree<D>::bfsWithVisitor2(int h, typename KDNode<D>* node, std::function<void(KDNode<D>*)> visitor)
{
	visitor(node);
	bfs(h + 1, ((KDNodeNonTerminal<D>*)node)->getLeft());
	bfs(h + 1, ((KDNodeNonTerminal<D>*)node)->getRight());
}

template <int D>
int KDTree<D>::spreadest(int d, typename vector<Point<D>*> subFile)
{
	float minVal = 9999999;
	float maxVal = -9999999;

	for (int i = 0; i < subFile.size(); i++)
	{
		if ((*subFile.at(i))[d] > maxVal)
		{
			maxVal = (*subFile.at(i))[d];
		}
		if ((*subFile.at(i))[d] < minVal)
		{
			minVal = (*subFile.at(i))[d];
		}
	}
	return std::abs(minVal - maxVal);
}

template <int D>
Point<D>* KDTree<D>::medianPoint(int d, typename vector<Point<D>*> subFile)
{
	// need better algoritm
	Point<D>* median = subFile[subFile.size() / 2];
	return median;
}

template <int D>
SplitedVector<D>& KDTree<D>::splitVector(int d, Point<D>* p, typename vector<Point<D>*>& pointsPartition)
{
	vector<Point<D>*>* first = new vector<Point<D>*>();
	vector<Point<D>*>* second = new vector<Point<D>*>();
	int midPoint = pointsPartition.size() / 2;
	for (int i = 0; i < pointsPartition.size(); i++)
	{
		if (i < midPoint)
		{
			first->push_back(pointsPartition[i]);
		}
		else
		{
			second->push_back(pointsPartition[i]);
		}
	}

	return *new SplitedVector<D>(*first, *second);
}

template<int D>
inline SplitedBoundingBox<D> KDTree<D>::splitBoundingBox(int d, Point<D>* splitPoint, BoundingBox<D> lastBB)
{
	BoundingBox<D> firstBB;
	BoundingBox<D> secondBB;

	firstBB.minimalPoint = lastBB.minimalPoint;
	firstBB.maximalPoint = lastBB.maximalPoint;
	firstBB.maximalPoint[d] = (*splitPoint)[d];

	secondBB.minimalPoint = lastBB.minimalPoint;
	secondBB.maximalPoint = lastBB.maximalPoint;
	secondBB.minimalPoint[d] = (*splitPoint)[d];


	return SplitedBoundingBox<D>(firstBB, secondBB);
}
