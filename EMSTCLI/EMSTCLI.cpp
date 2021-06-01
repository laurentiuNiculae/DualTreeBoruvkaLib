// EMSTCLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>
#include "DualTreeBoruvka.h"
#include "TestDataGenerator.h"

int main()
{
    
    TestDataGenerator generator;
    bool foundMistake = false;

    vector<Point<2>*> myPoints = generator.generateUniformData<2>(15, -100000, 100000);
    set<Edge<2>> E;

    KDTree<2> KDT(5, myPoints);
    DualTreeBoruvka<2> DTB(KDT, myPoints);
    E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    std::cout << E.size();

    //while (foundMistake == false)
    //{
    //    vector<Point<2>*> myPoints = generator.generateUniformData<2>(20, -1000, 1000);
    //    set<Edge<2>> E;
    //    KDTree<2> KDT(10, myPoints);
    //    DualTreeBoruvka<2> DTB(KDT, myPoints);
    //    E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    //
    //    if (E.size() >= myPoints.size())
    //    {
    //        for (auto i : myPoints)
    //        {
    //            cout << i->toString() << '\n';
    //        }
    //
    //        for (auto i : E)
    //        {
    //            cout << i.toString() << '\n';
    //        }
    //
    //        foundMistake = true;
    //    }
    //    else
    //    {
    //        myPoints.clear();
    //        E.clear();
    //    }
    //}

}
