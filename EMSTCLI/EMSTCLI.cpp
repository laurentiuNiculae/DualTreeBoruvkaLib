// EMSTCLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>
#include "DualTreeBoruvka.h"
#include "TestDataGenerator.h"

void testSpeed()
{
    TestDataGenerator generator;
    vector<Point<2>*> myPoints = generator.generateUniformData<2>(100000, -100000, 100000);
    set<Edge<2>> E;
    
    KDTree<2> KDT(5, myPoints);
    //KDT.bfsBB(0, KDT.getRoot());
    DualTreeBoruvka<2> DTB(KDT, myPoints);
    E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    std::cout << E.size();
}

void testPoints()
{
    vector<Point<2>*> myPoints;

    myPoints.emplace_back(new Point<2>({ -185.708252, 100.261108 }));
    myPoints.emplace_back(new Point<2>({ 920.368042, 180.849243 }));
    myPoints.emplace_back(new Point<2>({ 877.297485, -378.849182 }));
    myPoints.emplace_back(new Point<2>({ 446.734741, 955.640991 }));
    myPoints.emplace_back(new Point<2>({ 708.169800, -699.095581 }));
    myPoints.emplace_back(new Point<2>({ -759.525635, 455.308960 }));
    myPoints.emplace_back(new Point<2>({ -771.558472, 386.505127 }));
    myPoints.emplace_back(new Point<2>({ 15.622009, 562.160156 }));
    myPoints.emplace_back(new Point<2>({ -169.612305, -833.791870 }));
    myPoints.emplace_back(new Point<2>({ -307.942200, -293.087769 }));
    myPoints.emplace_back(new Point<2>({ -721.318909, 260.983276 }));
    myPoints.emplace_back(new Point<2>({ 639.645630, -315.830017 }));
    myPoints.emplace_back(new Point<2>({ 472.025635, -127.475281 }));
    myPoints.emplace_back(new Point<2>({ -61.904175, -906.766602 }));
    myPoints.emplace_back(new Point<2>({ -914.589294, -605.567566 }));
    myPoints.emplace_back(new Point<2>({ 625.163452, 952.364258 }));
    myPoints.emplace_back(new Point<2>({ -272.863892, 683.356689 }));
    myPoints.emplace_back(new Point<2>({ -108.361572, 770.449829 }));
    myPoints.emplace_back(new Point<2>({ 652.850098, -799.945557 }));
    myPoints.emplace_back(new Point<2>({ -130.671936, -910.033752 }));



    KDTree<2> KDT(5, myPoints);
    DualTreeBoruvka<2> DTB(KDT, myPoints);
    set<Edge<2>> E;
    E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    std::cout << E.size();
}

void generateMistakeSet()
{
    TestDataGenerator generator;
    bool foundMistake = false;

    while (foundMistake == false)
    {
        vector<Point<2>*> myPoints = generator.generateUniformData<2>(10000, -1000, 1000);
        set<Edge<2>> E;
        KDTree<2> KDT(5, myPoints);
        DualTreeBoruvka<2> DTB(KDT, myPoints);
        E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    
        if (E.size() == 999 && DTB.pointSet.allComponents.size() >= 2)
        {
            for (auto i : myPoints)
            {
                cout << i->toString() << '\n';
            }
        
            for (auto i : E)
            {
                cout << i.toString() << '\n';
            }
        
            foundMistake = true;
        }
        else
        {
            for (int i = 0; i < myPoints.size(); i++)
            {
                delete myPoints[i];
            }
            myPoints.clear();
            E.clear();
        }
    }
}

int main()
{
    //testSpeed();
    //testPoints();
    generateMistakeSet();
}
