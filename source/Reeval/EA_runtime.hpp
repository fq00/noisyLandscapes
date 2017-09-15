//
//  EA_runtime.hpp
//  OneMax
//
//  Created by Francesco Quinzan on 04.01.16.
//  Copyright © 2016 Francesco Quinzan. All rights reserved.
//

#ifndef EA_runtime_hpp
#define EA_runtime_hpp

#include "libraries.h"
#include "header.hpp"
#include "random.hpp"

#include "GA.hpp"
#include "population.hpp"

class EA_runtime{
    
    string dir;
    
    void makeLegend(ofstream*);
    int EAruntime(int, double);
    int minIndex(vector<int>);
    void mu(double, int*);
    
    void runtime(int);
    
public:
    
    EA_runtime(string dir, int seed){
        
        EA_runtime::dir = dir;
        randomEngine::set_seed(seed);
        runtime(seed);
        return;
        
    };
    
};

#endif /* EA_runtime_hpp */
