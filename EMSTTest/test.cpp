#include "pch.h"
#include <iostream>
#include "TestDataGenerator.h"

typedef std::vector<float> fList;
typedef Point<2> Point2;
typedef Point<3> Point3;
TEST(PointClass, TestInitialization)
{
	Point<2> p1;
	EXPECT_FLOAT_EQ(0, p1[0]);
	EXPECT_FLOAT_EQ(0, p1[1]);

	Point<2> p2(fList({1,2}));
	EXPECT_FLOAT_EQ(1, p2[0]);
	EXPECT_FLOAT_EQ(2, p2[1]);

	Point<4> p3(fList({2,3,4,5}));
	EXPECT_FLOAT_EQ(2, p3[0]);
	EXPECT_FLOAT_EQ(3, p3[1]);
	EXPECT_FLOAT_EQ(4, p3[2]);
	EXPECT_FLOAT_EQ(5, p3[3]);
}

TEST(PointClass, TestDistance)
{
	Point<2> p1(fList({2,2}));
	Point<2> p2(fList({3,3}));

	EXPECT_FLOAT_EQ(distance(p1, p2), sqrtf(2));

	Point<3> p3(fList({ 1,1,1 }));
	Point<3> p4(fList({ 2,2,2 }));

	EXPECT_FLOAT_EQ(distance(p3, p4), sqrtf(3));
}

TEST(BoundingBox, TestInit2Dimension)
{
	std::vector<Point<2>*> myPoints({ new Point2({1,1}), new Point2({2,2}), new Point2({5,6}) });
	BoundingBox<2> B(myPoints.begin(), myPoints.end());

	EXPECT_FLOAT_EQ(1, B.minimalPoint[0]);
	EXPECT_FLOAT_EQ(1, B.minimalPoint[1]);

	EXPECT_FLOAT_EQ(5, B.maximalPoint[0]);
	EXPECT_FLOAT_EQ(6, B.maximalPoint[1]);
}

TEST(BoundingBox, TestInit3Dimension)
{
	std::vector<Point<3>*> myPoints({ new Point3({1,1,1}), new Point3({2,2,2}), new Point3({5,6,0}) });
	BoundingBox<3> B(myPoints.begin(), myPoints.end());

	EXPECT_FLOAT_EQ(1, B.minimalPoint[0]);
	EXPECT_FLOAT_EQ(1, B.minimalPoint[1]);
	EXPECT_FLOAT_EQ(0, B.minimalPoint[2]);

	EXPECT_FLOAT_EQ(5, B.maximalPoint[0]);
	EXPECT_FLOAT_EQ(6, B.maximalPoint[1]);
	EXPECT_FLOAT_EQ(2, B.maximalPoint[2]);
}

TEST(BoundingBox, TestDistance)
{
	std::vector<Point<2>*> myPoints1({ new Point2({1,1}), new Point2({2,2}) });
	std::vector<Point<2>*> myPoints2({ new Point2({3,3}), new Point2({4,4}) });
	BoundingBox<2> B1(myPoints1.begin(), myPoints1.end());
	BoundingBox<2> B2(myPoints2.begin(), myPoints2.end());
	EXPECT_FLOAT_EQ(sqrt(2), bbDistance(B1, B2));
}

TEST(KDTreeTest, TestInit)
{
	vector<Point<3>*> myPoints({ new Point3({1,1,0}), new Point3({2,2,0}), new Point3({1,2,0}), new Point3({9,9,0}), new Point3({8,8,0}), new Point3({9,8,0}),
		new Point3({1,1,20}), new Point3({2,2,20}), new Point3({8,8,20}) });
	KDTree<3> tree(3, myPoints);
	tree.bfsPrint();
	EXPECT_FLOAT_EQ(1, 1);
}

TEST(DisjointSet, MakeSetTest)
{
	DisjointSet<3> S;
	Point3* myPoints[6];
	for (int i = 0; i < 6; i++)
	{
		myPoints[i] = new Point3({ (float)i, (float)i, (float)i });
		S.MakeSet(myPoints[i]);
	}
	vector<conexComponent<3>*> x = S.getConexComponents();
	int index = 0;
	S.Union(myPoints[2], myPoints[3]);
	for (auto i : myPoints)
	{
		std::cout << S.Find(i) << myPoints[index++]->toString() << std::endl;
	}
}

//TEST(DualTreeBoruvka, TestMST2D)
//{
//	vector<Point2*> points;
//	points.emplace_back(new Point2({ 1, 1   }));
//	points.emplace_back(new Point2({ 1, 3   }));
//	points.emplace_back(new Point2({ 2.5, 5 }));
//	points.emplace_back(new Point2({ 4, 4   }));
//	points.emplace_back(new Point2({ 1, 8   }));
//	points.emplace_back(new Point2({ 5, 10  }));
//	points.emplace_back(new Point2({ 7, 9   }));
//	
//	KDTree<2> KDT(3, points);
//	//KDT.bfsPrint();
//	DualTreeBoruvka<2> DTB(KDT, points);
//	
//	DTB.findEMST(KDT.getRoot(), points.size());
//
//}

TEST(DualTreeBoruvka, TestMST3D)
{
	vector<Point<3>*> myPoints({ new Point3({1,1,0}), new Point3({2,2,0}), new Point3({1,2,0}), new Point3({9,9,0}), new Point3({8,8,0}), new Point3({9,8,0}),
		new Point3({1,1,20}), new Point3({2,2,20}), new Point3({8,8,20}) });

	for (auto i : myPoints)
	{
		std::cout << i->toString() << std::endl;
	}
	KDTree<3> KDT(5, myPoints);
	KDT.bfsPrint();
	DualTreeBoruvka<3> DTB(KDT, myPoints);

	DTB.findEMST(KDT.getRoot(), myPoints.size());
}

//TEST(DualTreeBoruvka, TestSpeedUniform)
//{
//	TestDataGenerator generator;
//
//	vector<Point<3>*> myPoints = generator.generateUniformData<3>(10000, -1000, 1000);
//
//	KDTree<3> KDT(10, myPoints);
//	DualTreeBoruvka<3> DTB(KDT, myPoints);
//
//	DTB.findEMST(KDT.getRoot(), myPoints.size());
//}

TEST(KDTree, getBoundingBoxOfRoot)
{
	std::vector<Point2*> myPoints({ new Point2({1,1}), new Point2({2,2}), new Point2({5,6}) });
	KDTree<2> K(2, myPoints);
	auto root = K.getRoot();
	auto rootbb = root->getbb();
	EXPECT_FLOAT_EQ(1, rootbb.minimalPoint[0]);
	EXPECT_FLOAT_EQ(1, rootbb.minimalPoint[1]);

	EXPECT_FLOAT_EQ(5, rootbb.maximalPoint[0]);
	EXPECT_FLOAT_EQ(6, rootbb.maximalPoint[1]);

}

TEST(KDTree, visitingNodesInATree)
{
	std::vector<Point2*> myPoints({ new Point2({1,1}), new Point2({2,2}), new Point2({5,6}) });
	KDTree<2> K(2, myPoints);
	vector<string> strings;
	K.bfsWithVisitor(0, K.getRoot(), [](KDNode<2>* node) { std::cout << node->bb.maximalPoint.toString(); });
	K.bfsWithVisitor2(0, K.getRoot(), [&strings](KDNode<2>* node)
		{ 
			strings.push_back(node->bb.maximalPoint.toString());
		});
	
}
TEST(DualTreeBoruvka, TestSpeedNormal)
{

}

TEST(DualTreeBoruvka, TestSpeedLineDistribution)
{

}