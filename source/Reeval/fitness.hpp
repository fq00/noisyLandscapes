//
//  fitness.hpp
//  OneMax
//
//  Created by Francesco Quinzan on 29.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef fitness_hpp
#define fitness_hpp

#include "libraries.h"
#include "OneMax.hpp"
#include "results.hpp"
#include "population.hpp"
#include "path.hpp"
#include "individuals.hpp"

class fitness: public OneMax, public results{
    
public:
    
    /* compute the fitness of an entire populaton (used by GA) */
    
    void fitnessGA (class population*, double, int);
    
    /* compute the fitness of two individuals (used by CGA) */
    
    void fitnessCGA (class individuals*, double, int);
    
    /* compute the fitness of a single individual (used by ACO) */
    
    void fitnessACO (class path*, double, int);
   
    
};


#endif /* fitness_hpp */