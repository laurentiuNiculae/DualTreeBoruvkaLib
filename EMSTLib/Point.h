#pragma once
#include <cmath>
#include <vector>
#include <initializer_list>
#include <string>

template <unsigned int D>
class Point
{
	static int globalIndex;
	float coord[D];
	int index;
public:
	Point();
	Point(std::vector<float> v);
	Point(std::initializer_list<float> l);
	void setCoord(std::vector<float> v);
	unsigned int getSize();
	std::string toString();
	float& operator[](int i);
	int getIndex();

	template <int D_>
	friend float distance(Point& p1, Point& p2);
};

template <unsigned int D>
int Point<D>::globalIndex = 0;

template<unsigned int D>
inline Point<D>::Point()
{
	index = globalIndex;
	globalIndex = globalIndex + 1;
	for (int i = 0; i < D; i++)
	{
		coord[i] = 0.0f;
	}
}

template<unsigned int D>
inline Point<D>::Point(std::vector<float> v)
{

	if (v.size() != D)
	{
		throw "Can't initialize, Vector size doesn't match!";
	}
	index = globalIndex;
	globalIndex++;
	for (int i = 0; i < D; i++)
	{
		coord[i] = v[i];
	}
}

template<unsigned int D>
inline Point<D>::Point(std::initializer_list<float> params)
{
	if (params.size() != D)
	{
		throw "Can't initialize, Vector size doesn't match!";
	}
	index = globalIndex;
	globalIndex++;
	int i = 0;
	for (auto& x : params)
	{
		coord[i] = x;
		i++;
	}
}

template<unsigned int D>
inline unsigned int Point<D>::getSize()
{
	return D;
}

template<unsigned int D>
inline std::string Point<D>::toString()
{
	std::string str("");
	//str += "(";
	for (int i = 0; i < this->getSize(); i++)
	{
		str += std::to_string(this->coord[i]) + ",";
	}
	//str += ")";
	str += "[";
	str += std::to_string(this->index);
	str += "]";
	return str;
}

template<unsigned int D>
inline float& Point<D>::operator[](int i)
{
	return coord[i];
}

template<unsigned int D>
inline int Point<D>::getIndex()
{
	return index;
}

template<unsigned int D>
inline void Point<D>::setCoord(std::vector<float> v)
{
	if (v.size() != D)
	{
		throw "Can't initialize, Vector size doesn't match!";
	}
	for (int i = 0; i < D; i++)
	{
		coord[i] = v[i];
	}
}

template<int D_>
inline float distance(Point<D_>& p1, Point<D_>& p2)
{
	float dist = 0;
	float diff = 0;
	for (int i = 0; i < D_; i++)
	{
		diff = p1[i] - p2[i];
		dist += diff * diff;
	}
	return sqrt(dist);
}
