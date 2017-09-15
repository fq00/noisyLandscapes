//
//  OneMax.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 22.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "OneMax.hpp"
#include "random.hpp"

using namespace std;

double OneMax::dynamic (vector<int>* x){
    
    /* compute exact fitness */
    
    double fitness = 0.0;
    for (int i = 0; i < x->size(); i++){
            fitness = fitness + abs(x->at(i)) % OneMax::order;
    }
    
    /* add noise */
    
    fitness = fitness + randomEngine::nrm(0, ::sqrt(OneMax::n)*OneMax::sigma)/n;
    return (fitness);
    
};