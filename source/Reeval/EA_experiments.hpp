//
//  EA_experiments.hpp
//  OneMax
//
//  Created by Francesco Quinzan on 02.12.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef EA_experiments_hpp
#define EA_experiments_hpp

#include "libraries.h"
#include "header.hpp"
#include "random.hpp"

#include "GA.hpp"
#include "population.hpp"

class EA_experiments: public header {
    
    void make_legend(ofstream*);
    
public:
    
    /* parameter calibration */
    
    void parameter_calibration(string, int);
    
    /* r analysis */
    
    void r_analysis(string, int);
    
    /* sigma analysis */
    
    void variance_analysis(string, int);
};

#endif /* EA_experiments_hpp */
