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

    vector<Point<2>*> myPoints = generator.generateUniformData<2>(20000, -10000, 10000);
    set<Edge<2>> E;
    
    KDTree<2> KDT(64, myPoints);
    //KDT.bfsBB(0, KDT.getRoot());
    DualTreeBoruvka<2> DTB(KDT, myPoints);
    E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    std::cout << E.size();

    //vector<Point<2>*> myPoints;
    
    //myPoints.emplace_back(new Point<2>({-996.534973, -865.843506   }));
    //myPoints.emplace_back(new Point<2>({- 225.898865, 162.316040   }));
    //myPoints.emplace_back(new Point<2>({- 766.175476, 461.352417   }));
    //myPoints.emplace_back(new Point<2>({- 852.856079, -427.529846  }));
    //myPoints.emplace_back(new Point<2>({821.949097, -92.638000     }));
    //myPoints.emplace_back(new Point<2>({846.413574, -791.986084    }));
    //myPoints.emplace_back(new Point<2>({- 22.900452, 166.709595    }));
    //myPoints.emplace_back(new Point<2>({592.125366, -123.592163    }));
    //myPoints.emplace_back(new Point<2>({35.801392, 405.183350      }));
    //myPoints.emplace_back(new Point<2>({- 971.708679, -761.587219  }));
    //myPoints.emplace_back(new Point<2>({232.392578, 720.849121     }));
    //myPoints.emplace_back(new Point<2>({622.648438, 671.357666     }));
    //myPoints.emplace_back(new Point<2>({- 359.391296, -215.362732  }));
    //myPoints.emplace_back(new Point<2>({728.203857, -341.341675    }));
    //myPoints.emplace_back(new Point<2>({- 792.102722, 967.157593   }));
    //myPoints.emplace_back(new Point<2>({- 862.872620, 100.148315   }));
    //myPoints.emplace_back(new Point<2>({- 107.468018, 89.926758    }));
    //myPoints.emplace_back(new Point<2>({976.682007, 694.810181     }));
    //myPoints.emplace_back(new Point<2>({- 735.640442, 791.786133   }));
    //myPoints.emplace_back(new Point<2>({820.941772, -673.815796    }));

    //KDTree<2> KDT(5, myPoints);
    //KDT.bfsBB(0, KDT.getRoot());
    //DualTreeBoruvka<2> DTB(KDT, myPoints);
    //set<Edge<2>> E;
    //E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    //std::cout << E.size();

    //while (foundMistake == false)
    //{
    //    vector<Point<2>*> myPoints = generator.generateUniformData<2>(20, -1000, 1000);
    //    set<Edge<2>> E;
    //    KDTree<2> KDT(5, myPoints);
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
    //        for (int i = 0; i < myPoints.size(); i++)
    //        {
    //            delete myPoints[i];
    //        }
    //        myPoints.clear();
    //        E.clear();
    //    }
    //}

}
