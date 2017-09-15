//
//  rAnalysis.hpp
//  Reeval
//
//  Created by Francesco Quinzan on 26.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef rAnalysis_hpp
#define rAnalysis_hpp

#include "libraries.h"
#include "header.hpp"
#include "random.hpp"

#include "ACO.hpp"
#include "pheromone.hpp"
#include "path.hpp"

class MMASib_experiments: public header {
    
    void make_legend(ofstream*);

public:
    
    /* parameter calibration */
    
    void parameter_calibration(string, int);
    
    /* r analysis */
    
    void r_analysis(string, int);
    
    /* sigma analysis */
    
    void variance_analysis(string, int);
};

#endif /* rAnalysis_hpp */
