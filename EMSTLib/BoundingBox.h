#pragma once
#include <vector>
#include <algorithm>
#include "Point.h"

using std::vector;

template <int D>
class BoundingBox
{
public:
	Point<D> minimalPoint;
	Point<D> maximalPoint;
	BoundingBox();
	BoundingBox(typename vector<Point<D>*>::iterator iter, typename vector<Point<D>*>::iterator end);
    BoundingBox(typename vector<Point<D>*>::iterator iter, typename vector<Point<D>*>::iterator end, Point<D>* lastSplitMade);
	BoundingBox(typename BoundingBox<D>& bb1,typename BoundingBox<D>& bb2);
    void setMinimalPoint(Point<D>* p);
    void setMaximanPoint(Point<D>* p);

    template <int D_>
	friend float bbDistance(typename BoundingBox<D_>& bb1,typename BoundingBox<D_>& bb2);
};

template<int D>
inline BoundingBox<D>::BoundingBox()
{
    minimalPoint = Point<D>();
    maximalPoint = Point<D>();
}

template<int D>
inline BoundingBox<D>::BoundingBox(typename vector<Point<D>*>::iterator iter, typename vector<Point<D>*>::iterator end)
{
    minimalPoint = *(*iter);
    maximalPoint = *(*iter);
    while (iter != end) {
        for (int i = 0; i < D; i++) {
            minimalPoint[i] = std::min(minimalPoint[i], (*(*iter))[i]);
            maximalPoint[i] = std::max(maximalPoint[i], (*(*iter))[i]);
        }
        iter++;
    }
}

template<int D>
inline BoundingBox<D>::BoundingBox(typename vector<Point<D>*>::iterator iter, typename vector<Point<D>*>::iterator end, Point<D>* lastSplitMade)
{
    minimalPoint = *lastSplitMade;
    maximalPoint = *lastSplitMade;
    while (iter != end) {
        for (int i = 0; i < D; i++) {
            minimalPoint[i] = std::min(minimalPoint[i], (*(*iter))[i]);
            maximalPoint[i] = std::max(maximalPoint[i], (*(*iter))[i]);
        }
        iter++;
    }
}

template<int D>
inline BoundingBox<D>::BoundingBox(BoundingBox& bb1, BoundingBox& bb2)
{
    for (int i = 0; i < D; i++)
    {
        minimalPoint[i] = std::min(bb1.minimalPoint[i], bb2.minimalPoint[i]);
        maximalPoint[i] = std::max(bb1.maximalPoint[i], bb2.maximalPoint[i]);
    }
}

template<int D>
inline void BoundingBox<D>::setMinimalPoint(Point<D>* p)
{
    minimalPoint = *p;
}

template<int D>
inline void BoundingBox<D>::setMaximanPoint(Point<D>* p)
{
    maximalPoint = *p;
}

template <int D_>
float bbDistance(typename BoundingBox<D_>& bb1, typename BoundingBox<D_>& bb2)
{
    float sum = 0;
    for (int i = 0; i < D_; i++)
    {
        float diff = std::max(bb1.minimalPoint[i], bb2.minimalPoint[i]) - std::min(bb1.maximalPoint[i], bb2.maximalPoint[i]);
        if (diff > 0) {
            sum += diff * diff;
        }
    }
    return sqrt(sum);
}