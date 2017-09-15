//
//  GA_experiments.hpp
//  OneMax
//
//  Created by Francesco Quinzan on 27.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef GA_experiments_hpp
#define GA_experiments_hpp

#include "libraries.h"
#include "header.hpp"
#include "random.hpp"

#include "GA.hpp"
#include "population.hpp"

class GA_experiments: public header {
    
    void make_legend(ofstream*);
    
public:
    
    /* parameter calibration */
    
    void parameter_calibration(string, int);
    
    /* r analysis */
    
    void r_analysis(string, int);
    
    /* sigma analysis */
    
    void variance_analysis(string, int);
};

#endif /* GA_experiments_hpp */
