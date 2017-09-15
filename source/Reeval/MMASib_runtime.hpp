//
//  MMASib_runtime.hpp
//  Reeval
//
//  Created by Francesco Quinzan on 04.01.16.
//  Copyright © 2016 Francesco Quinzan. All rights reserved.
//

#ifndef MMASib_runtime_hpp
#define MMASib_runtime_hpp

#include "libraries.h"
#include "header.hpp"
#include "random.hpp"

#include "ACO.hpp"
#include "path.hpp"
#include "pheromone.hpp"

class MMASib_runtime{
    
    string dir;
    
    void makeLegend(ofstream*);
    int MMASibRuntime(int, double, double, int, ofstream*);
    int minIndex(vector<int>);
    void parametersCalibration(double, double*, int*, int);
    
    void runtime(int);
    
public:
    
    MMASib_runtime(string dir, int seed){
        
        MMASib_runtime::dir = dir;
        randomEngine::set_seed(seed);
        runtime(seed);
        return;
        
    };
    
};

#endif /* MMASib_runtime_hpp */
