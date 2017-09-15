//
//  pheromone.hpp
//  Reeval
//
//  Created by Francesco Quinzan on 30.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef pheromone_hpp
#define pheromone_hpp

#include "libraries.h"
#include "fitness.hpp"
#include "table.hpp"
#include "path.hpp"

class pheromone{
  
public:
    
    class table<double> data;
    
    /* evaporation factor */
    
    double rho;
    
//public:
    
    /* set all elements to a specific value */
    
    pheromone (int, double);
    
    /* adjust pheromone to fitness of a given element */
    
    void adjust (class path*, class fitness*);
    
    /* get dimension */
    
    int dimension ();
    
    /* get a specific value */
    
    double get (int i, int j);
    
};

#endif /* pheromone_hpp */
