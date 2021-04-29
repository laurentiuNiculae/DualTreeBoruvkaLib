#pragma once
#include <random>
#include <functional>
#include <chrono>
#include "DualTreeBoruvka.h"


class TestDataGenerator
{
public:
	template <int D>
	static vector<Point<D>*> generateUniformData(int size, float minVal, float maxVal);

	template <int D>
	static vector<Point<D>*> generateNormalData(int size, float mean, float std);

	template <int D>
	static vector<Point<D>*> generateLineDistributuionData(int size, float mean, float std);
};

template<int D>
inline vector<Point<D>*> TestDataGenerator::generateUniformData(int size, float minVal, float maxVal)
{
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed1);
	std::uniform_real_distribution<float> distribution(minVal, maxVal);
	auto randNumber = std::bind(distribution, generator);

	vector<Point<D>*> points;
	points.reserve(size);

	for (int i = 0; i < size; i++)
	{
		Point<D>* point = new Point<D>();
		for (int dimension = 0; dimension < D; dimension++)
		{
			(*point)[dimension] = randNumber();
		}
		points.push_back(point);
	}
	return points;
}

template<int D>
inline vector<Point<D>*> TestDataGenerator::generateNormalData(int size, float mean, float std)
{
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(mean, std);
	auto randNumber = std::bind(distribution, generator);

	vector<Point<D>*> points;
	points.reserve(size);

	for (int i = 0; i < size; i++)
	{
		Point<D>* point = new Point<D>();
		for (int dimension = 0; dimension < D; dimension++)
		{
			point[dimension] = randNumber();
		}
	}
	return points;
}

template<int D>
inline vector<Point<D>*> TestDataGenerator::generateLineDistributuionData(int size, float mean, float std)
{
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(mean, std);
	auto randNumber = std::bind(distribution, generator);

	vector<Point<D>*> points;
	points.reserve(size);

	for (int i = 0; i < size; i++)
	{
		Point<D>* point = new Point<D>();
		for (int dimension = 0; dimension < D; dimension++)
		{
			point[dimension] = randNumber();
		}
	}
	return points;
}
