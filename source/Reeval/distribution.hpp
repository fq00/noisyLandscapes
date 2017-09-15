//
//  distribution.hpp
//  OneMax
//
//  Created by Francesco Quinzan on 06.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef distribution_hpp
#define distribution_hpp

#include "libraries.h"
#include "table.hpp"
#include "individuals.hpp"

class distribution{
    
    /* distribution array */
    
    class table<double> data;
    
    /* evaporation factor */
    
    double K;
    
public:
    
    /* constructor - set all coefficients to a specific value */
    
    distribution (int, double);
    
    /* adjust distribution to fitness */
    
    void adjust (class individuals*);
    
    /* get dimension */
    
    int dimension ();
    
    /* get a specific value */
    
    double get (int i);
    
};

#endif /* distribution_hpp */
