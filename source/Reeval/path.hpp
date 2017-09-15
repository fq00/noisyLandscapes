//
//  path.hpp
//  Reeval
//
//  Created by Francesco Quinzan on 30.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef path_hpp
#define path_hpp

#include "libraries.h"
#include "table.hpp"
#include "pheromone.hpp"
#include "random.hpp"

class path{
    
public:
    
    /* paths matrix */
    
    class table<int> data;
    
    /* parameters - number of ants */
    
    int lambda;
    
    //public:
    
    /* set path according to pheromone traits */
    
    void set (class pheromone*);
    
    /* get values as vector<int> */
    
    vector<int> get (int);
    
    /* get single value */
    
    int value (int);
    
    /* get the optimum */
    
    vector<int> best(class fitness *);
    
    /* check convergence */
    
    int check();
    
    /* get lambda parameter */
    
    int size();
    
    /* constructor - fix lambda */
    
    path(int);
    
};

#endif /* path_hpp */
