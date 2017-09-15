//
//  individuals.hpp
//  Reeval
//
//  Created by Francesco Quinzan on 06.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef individuals_hpp
#define individuals_hpp

#include "libraries.h"
#include "random.hpp"
#include "table.hpp"
#include "../other/table.cpp"
#include "distribution.hpp"
#include "fitness.hpp"

class individuals {
    
    /* individuals matrix */
    
    class table<int> data;
    
public:
    
    /* get individuals dimension */
    
    int dimension();
    
    /* get value of specific individual */
    
    int get (int, int);
    
    /* get individual as vector<int> */
    
    vector<int> individual(int);
    
    /* generate random population */
    
    void set(class distribution*);
    
    /* get number of individuals - 2 by default */
    
    int size();
    
    /* swap vectors accoring to fitness */
    
    void swap(class fitness*);
    
    /* check if true optimum has been found */
    
    int check();
};

#endif /* individuals_hpp */
