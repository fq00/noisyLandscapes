//
//  results.hpp
//  Reeval
//
//  Created by Francesco Quinzan on 26.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef results_hpp
#define results_hpp

#include "libraries.h"
#include "table.hpp"
#include "../other/table.cpp"

class results{
    
public:
    
    class table<double> data;
    
//public:
    
    /* adds element to the table */
    void add (double);
    
    /* clear the entire table */
    void clear ();
    
    /* delete a specific row */
    void del(int);
    
    /* find index with min/max value */
    int max ();
    int min ();
    
    /* find minimum value */
    double minimum ();
    
    /* find maximum value */
    double maximum ();
    
    /* get an element of the vector */
    double get (int);
    
    /* get an element of the vector */
    int size ();
};

#endif /* results_hpp */
