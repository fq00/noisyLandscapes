//
//  population.hpp
//  Reeval
//
//  Created by Francesco Quinzan on 28.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef population_hpp
#define population_hpp

#include "libraries.h"
#include "table.hpp"
#include "../other/table.cpp"
#include "random.hpp"

class population {

public:
    
    class table<int> data;
    int ord;
    
//public:
    
    /* generate random population */
    
    void set(int, int, int);
    
    /* get population size (mu parameter) */
    
    int size();
    
    /* get poulation order */
    
    int order();
    
    /* get population dimension */
    
    int dimension();
    
    /* erase given individual */
    
    void kill(int);
    
    /* get individual as vector<int> */
    
    vector<int> individual(int);
    
    /* get pointer to a specific value*/
    
    vector<int>* row(int);
    
    /* introduce mutation factor */
    
    void mutation(int);
    
    /* create offspring */
    
    void offspring(int);
    
    /* check if true optimum has been reached */
    
    int check();
    
};

#endif /* population_hpp */