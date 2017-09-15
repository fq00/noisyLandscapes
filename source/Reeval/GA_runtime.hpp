//
//  GA_runtime.hpp
//  OneMax
//
//  Created by Francesco Quinzan on 04.01.16.
//  Copyright © 2016 Francesco Quinzan. All rights reserved.
//

#ifndef GA_runtime_hpp
#define GA_runtime_hpp

#include "libraries.h"
#include "header.hpp"
#include "random.hpp"

#include "GA.hpp"
#include "population.hpp"

class GA_runtime{

    string dir;
    
    void makeLegend(ofstream*);
    int GAruntime(int, double);
    int minIndex(vector<int>);
    void mu(double, int*);
    
    void runtime(int);
    
public:

    GA_runtime(string dir, int seed){
        
        GA_runtime::dir = dir;
        randomEngine::set_seed(seed);
        runtime(seed);
        return;
        
    };
    
};

#endif /* GA_runtime_hpp */
