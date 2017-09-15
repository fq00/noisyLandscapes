//
//  cGA_experiments.hpp
//  OneMax
//
//  Created by Francesco Quinzan on 07.12.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef cGA_experiments_hpp
#define cGA_experiments_hpp

#include "libraries.h"
#include "header.hpp"
#include "random.hpp"

#include "CGA.hpp"
#include "pheromone.hpp"
#include "path.hpp"

class cGA_experiments : public header {
    
    void make_legend(ofstream*);
    
public:
    
    /* parameter calibration */
    
    void parameter_calibration(string, int);
    
    /* r analysis */
    
    void r_analysis(string, int);
    
    /* sigma analysis */
    
    void variance_analysis(string, int);
};

#endif /* cGA_experiments_hpp */
