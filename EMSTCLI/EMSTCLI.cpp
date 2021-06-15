// EMSTCLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>
#include "DualTreeBoruvka.h"
#include "TestDataGenerator.h"
#include <fstream>

void testSpeed()
{
    TestDataGenerator generator;
    vector<Point<2>*> myPoints = generator.generateUniformData<2>(100000, -100000, 100000);
    set<Edge<2>> E;
    
    KDTree<2> KDT(5, myPoints);
    //KDT.bfsBB(0, KDT.getRoot());
    DualTreeBoruvka<2> DTB(KDT, myPoints);
    DTB.printProgressFlag = true;
    E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    std::cout << E.size();
}

vector<Point<2>*> readPointsFromFile()
{
    std::ifstream f("C:\\Users\\theme\\source\\repos\\EMSTLicenta\\EMSTCLI\\Points.txt");
    vector<Point<2>*> myPoints;
    float a, b;
    while (f >> a >> b)
    {
        myPoints.emplace_back(new Point<2>({ a, b }));
    }
    f.close();
    return myPoints;
}

void testPoints()
{
    vector<Point<2>*> myPoints = readPointsFromFile();

    KDTree<2> KDT(5, myPoints);
    KDT.bfsPrint();

    DualTreeBoruvka<2> DTB(KDT, myPoints);
    DTB.printEveryIterationFlag = true;
    DTB.printProgressFlag = true;

    set<Edge<2>> E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    std::cout << E.size();

    std::ofstream edges("C:\\Users\\theme\\OneDrive\\Desktop\\LICENTA\\Actual Licenta\\PlottingTests\\edges.txt");
    for (auto i : E)
    {
        edges << i.toString() << '\n';
    }
    edges.close();
}

void generateMistakeSet()
{
    TestDataGenerator generator;
    bool foundMistake = false;

    while (foundMistake == false)
    {
        vector<Point<2>*> myPoints = generator.generateUniformData<2>(1000, -1000, 1000);
        set<Edge<2>> E;
        KDTree<2> KDT(5, myPoints);
        DualTreeBoruvka<2> DTB(KDT, myPoints);
        DTB.printProgressFlag = true;
        E = DTB.findEMST(KDT.getRoot(), myPoints.size());
        
        double mean = 0;
        int i = 1;
        for ( auto it = E.begin(); it != E.end(); it++)
        {
            auto wow = *it;
            mean = mean * (i - 1) / i + wow.lenght() / i;
            i++;
        }

        cout << "MEAN IS: " << mean;
        

        if (E.size() >= 999 && DTB.pointSet.allComponents.size() != 1)
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
