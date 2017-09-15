//
//  distribution.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 06.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "distribution.hpp"

using namespace std;

/* constructor - set all coefficients to a specific value */
distribution::distribution (int dimension, double K){
    
    distribution::K = K;
    distribution::data.CLEAR();
    distribution::data.RESIZE(1, dimension);
    
    for (int i = 0; i < distribution::data.GET_N_ROW(); i++){
        for (int j = 0; j < distribution::data.GET_N_COL(); j++)
            distribution::data.SET_VALUE(1.0/2, i, j);
    }
    return;
    
};

/* adjust distribution to fitness */
void distribution::adjust (individuals* individuals){
    
    int n = individuals -> dimension();
    
    for (int i = 0; i < distribution::data.GET_N_COL(); i++){
        
        if (individuals->get(0, i) > individuals->get(1, i))
        /*distribution::data.SET_VALUE(::max(::min(distribution::data.GET_VALUE(0, i) + 1.0/distribution::K, ::max(1.0/distribution::K, 1-1.0/distribution::K)), ::min(1.0/distribution::K, 1-1.0/distribution::K)), 0, i);*/
            distribution::data.SET_VALUE(::max(::min(distribution::data.GET_VALUE(0, i) + 1.0/distribution::K, ::max(1.0/n, 1-1.0/n)), ::min(1.0/n, 1-1.0/n)), 0, i);
        if (individuals->get(0, i) < individuals->get(1, i))
        /*distribution::data.SET_VALUE(::max(::min(distribution::data.GET_VALUE(0, i) - 1.0/distribution::K, ::max(1.0/distribution::K, 1-1.0/distribution::K)), ::min(1.0/distribution::K, 1-1.0/distribution::K)), 0, i);*/
            distribution::data.SET_VALUE(::max(::min(distribution::data.GET_VALUE(0, i) - 1.0/distribution::K, ::max(1.0/n, 1-1.0/n)), ::min(1.0/n, 1-1.0/n)), 0, i);
        else
            distribution::data.SET_VALUE(distribution::data.GET_VALUE(0, i), 0, i);
        
    }
    
    return;
    
};

/* get dimension */
int distribution::dimension(){
    
    return (distribution::data.GET_N_COL());
    
};

/* get a specific value */
double distribution::get (int i){
    
    return(distribution::data.GET_VALUE(0, i));
    
};