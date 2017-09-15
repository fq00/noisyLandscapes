//
//  OneMax.hpp
//  Reeval
//
//  Created by Francesco Quinzan on 22.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#ifndef OneMax_hpp
#define OneMax_hpp

#include "libraries.h"

class OneMax{
    
public:
    
    /* parameters to generate noise */
    double sigma;
    int n;
    
    /* parameters to set up function */
    int order = 2;
    std::vector<int>* reference; //= &ref;
    
    /* dynamic OneMax */
    double dynamic (std::vector<int>*);
    
};


#endif /* OneMax_hpp */