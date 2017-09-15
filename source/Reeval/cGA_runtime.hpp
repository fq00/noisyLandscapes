//
//  cGA_runtime.hpp
//  OneMax
//
//  Created by Francesco Quinzan on 05.01.16.
//  Copyright © 2016 Francesco Quinzan. All rights reserved.
//

#ifndef cGA_runtime_hpp
#define cGA_runtime_hpp

#include "libraries.h"
#include "header.hpp"
#include "random.hpp"

#include "CGA.hpp"
#include "pheromone.hpp"
#include "path.hpp"

class cGA_runtime{
    
    string dir;
    
    void makeLegend(ofstream*);
    int cGAruntime(int, double);
    int minIndex(vector<int>);
    void parametersCalibration(double, int*);
    
    void runtime(int);
    
public:
    
    cGA_runtime(string dir, int seed){
        
        cGA_runtime::dir = dir;
        randomEngine::set_seed(seed);
        runtime(seed);
        return;
        
    };
    
};

#endif /* cGA_runtime_hpp */
