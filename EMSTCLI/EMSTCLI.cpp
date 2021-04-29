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
    vector<Point<2>*> myPoints;
    myPoints.push_back(new Point<2>({-84826.070313, -43560.105469   }));
    myPoints.push_back(new Point<2>({- 7451.757813, -53869.898438   }));
    myPoints.push_back(new Point<2>({41677.765625, 91390.703125     }));
    myPoints.push_back(new Point<2>({96132.515625, 60202.781250     }));
    myPoints.push_back(new Point<2>({- 86333.437500, 70087.953125   }));
    myPoints.push_back(new Point<2>({70492.234375, 18376.242188     }));
    myPoints.push_back(new Point<2>({- 15140.593750, -93712.773438  }));
    myPoints.push_back(new Point<2>({33657.796875, 26163.710938     }));
    myPoints.push_back(new Point<2>({48876.140625, -37997.234375    }));
    myPoints.push_back(new Point<2>({- 12989.960938, 51508.000000   }));
    myPoints.push_back(new Point<2>({- 53830.707031, -42415.332031  }));
    myPoints.push_back(new Point<2>({- 32106.992188, 97852.468750   }));
    myPoints.push_back(new Point<2>({23544.875000, 73619.015625     }));
    myPoints.push_back(new Point<2>({- 74218.601563, -46880.871094  }));
    myPoints.push_back(new Point<2>({- 90896.218750, 23038.492188   }));
    myPoints.push_back(new Point<2>({96215.734375, 29910.828125     }));
    myPoints.push_back(new Point<2>({- 53718.054688, -86493.226563  }));
    myPoints.push_back(new Point<2>({- 72932.906250, 98541.078125   }));
    myPoints.push_back(new Point<2>({15388.453125, -42794.781250    }));
    myPoints.push_back(new Point<2>({53694.375000, -25794.414063    }));
    myPoints.push_back(new Point<2>({- 64048.046875, 52204.078125   }));
    myPoints.push_back(new Point<2>({95335.640625, -94670.750000    }));
    myPoints.push_back(new Point<2>({- 7622.023438, 65370.531250    }));
    myPoints.push_back(new Point<2>({- 29744.359375, -10029.437500  }));
    myPoints.push_back(new Point<2>({- 42789.679688, 52676.453125   }));
    myPoints.push_back(new Point<2>({- 53711.375000, 32519.546875   }));
    myPoints.push_back(new Point<2>({16358.765625, 19863.429688     }));
    myPoints.push_back(new Point<2>({- 19897.625000, 24242.601563   }));
    myPoints.push_back(new Point<2>({- 60091.535156, 39370.218750   }));
    myPoints.push_back(new Point<2>({- 51110.570313, -71859.070313  }));
    myPoints.push_back(new Point<2>({24221.804688, -85031.554688    }));
    myPoints.push_back(new Point<2>({74950.937500, -29331.812500    }));
    myPoints.push_back(new Point<2>({- 15860.015625, 90683.609375   }));
    myPoints.push_back(new Point<2>({38403.437500, 83199.000000     }));
    myPoints.push_back(new Point<2>({- 15878.226563, 7249.390625    }));
    myPoints.push_back(new Point<2>({- 68165.937500, 14147.296875   }));
    myPoints.push_back(new Point<2>({- 78819.476563, -54753.023438  }));
    myPoints.push_back(new Point<2>({- 36561.359375, -47844.000000  }));
    myPoints.push_back(new Point<2>({39376.984375, 62845.000000     }));
    myPoints.push_back(new Point<2>({40880.171875, 82528.109375     }));
    myPoints.push_back(new Point<2>({- 9306.875000, -50577.484375   }));
    myPoints.push_back(new Point<2>({67114.437500, -41414.917969    }));
    myPoints.push_back(new Point<2>({74478.546875, 18206.359375     }));
    myPoints.push_back(new Point<2>({- 81758.117188, 4596.875000    }));
    myPoints.push_back(new Point<2>({52895.468750, 67048.531250     }));
    myPoints.push_back(new Point<2>({47730.906250, 90053.218750     }));
    myPoints.push_back(new Point<2>({- 60016.382813, -92716.492188  }));
    myPoints.push_back(new Point<2>({- 27574.695313, 36038.796875   }));
    myPoints.push_back(new Point<2>({- 81433.234375, -17268.859375  }));
    myPoints.push_back(new Point<2>({- 70379.984375, -88682.390625  }));
    myPoints.push_back(new Point<2>({- 73046.140625, -62915.500000  }));
    myPoints.push_back(new Point<2>({51714.156250, -62183.691406    }));
    myPoints.push_back(new Point<2>({45761.828125, -43106.894531    }));
    myPoints.push_back(new Point<2>({- 29401.406250, 12810.992188   }));
    myPoints.push_back(new Point<2>({97171.515625, -74350.343750    }));
    myPoints.push_back(new Point<2>({36611.968750, -65900.796875    }));
    myPoints.push_back(new Point<2>({44749.109375, 28920.117188     }));
    myPoints.push_back(new Point<2>({- 23453.023438, -87123.937500  }));
    myPoints.push_back(new Point<2>({- 48387.546875, -32850.117188  }));
    myPoints.push_back(new Point<2>({- 58269.195313, -8905.867188   }));
    myPoints.push_back(new Point<2>({- 27693.398438, -40876.257813  }));
    myPoints.push_back(new Point<2>({95869.046875, -20151.078125    }));
    myPoints.push_back(new Point<2>({92869.281250, 12896.593750     }));
    myPoints.push_back(new Point<2>({- 93736.734375, -89161.914063  }));
    myPoints.push_back(new Point<2>({36492.390625, 83969.562500     }));
    myPoints.push_back(new Point<2>({- 71704.796875, -98482.359375  }));
    myPoints.push_back(new Point<2>({- 64171.476563, -5926.343750   }));
    myPoints.push_back(new Point<2>({- 18795.320313, 89369.531250   }));
    myPoints.push_back(new Point<2>({84548.359375, -2628.054688     }));
    myPoints.push_back(new Point<2>({- 29808.750000, -69139.031250  }));
    myPoints.push_back(new Point<2>({- 51799.273438, -8887.304688   }));
    myPoints.push_back(new Point<2>({24939.062500, 97516.953125     }));
    myPoints.push_back(new Point<2>({- 93351.390625, -71001.523438  }));
    myPoints.push_back(new Point<2>({- 78248.156250, 4204.937500    }));
    myPoints.push_back(new Point<2>({- 63745.738281, -54881.222656  }));
    myPoints.push_back(new Point<2>({86607.000000, 78389.531250     }));
    myPoints.push_back(new Point<2>({14757.695313, 51535.968750     }));
    myPoints.push_back(new Point<2>({21478.929688, -56763.027344    }));
    myPoints.push_back(new Point<2>({58320.875000, 56596.343750     }));
    myPoints.push_back(new Point<2>({21721.257813, -50157.429688    }));
    myPoints.push_back(new Point<2>({- 18064.765625, -15287.468750  }));
    myPoints.push_back(new Point<2>({- 47542.000000, 32221.468750   }));
    myPoints.push_back(new Point<2>({- 45748.867188, -49842.636719  }));
    myPoints.push_back(new Point<2>({61528.140625, -95159.109375    }));
    myPoints.push_back(new Point<2>({67334.968750, -44295.562500    }));
    myPoints.push_back(new Point<2>({- 59401.320313, -55018.644531  }));
    myPoints.push_back(new Point<2>({16001.570313, 49884.015625     }));
    myPoints.push_back(new Point<2>({15536.484375, -74632.804688    }));
    myPoints.push_back(new Point<2>({41651.671875, 32408.031250     }));
    myPoints.push_back(new Point<2>({- 93066.718750, -32959.453125  }));
    myPoints.push_back(new Point<2>({78818.531250, -7127.296875     }));
    myPoints.push_back(new Point<2>({- 97055.742188, -60251.351563  }));
    myPoints.push_back(new Point<2>({44945.984375, -4733.664063     }));
    myPoints.push_back(new Point<2>({80410.531250, 72417.171875     }));
    myPoints.push_back(new Point<2>({49181.781250, 40231.109375     }));
    myPoints.push_back(new Point<2>({- 38112.175781, -84166.765625  }));
    myPoints.push_back(new Point<2>({- 72812.773438, -97975.507813  }));
    myPoints.push_back(new Point<2>({90670.781250, 35195.453125     }));
    myPoints.push_back(new Point<2>({- 77380.648438, -41640.257813  }));
    myPoints.push_back(new Point<2>({65889.781250, 59363.609375     }));
    set<Edge<2>> E;


    //myPoints = generator.generateUniformData<2>(20, -10, 10);
    KDTree<2> KDT(5, myPoints);
    DualTreeBoruvka<2> DTB(KDT, myPoints);
    E = DTB.findEMST(KDT.getRoot(), myPoints.size());
    
    std::cout << "wow";
}
