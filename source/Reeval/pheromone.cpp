//
//  pheromone.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 30.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "pheromone.hpp"
#include "fitness.hpp"
#include "table.hpp"
#include "path.hpp"

pheromone::pheromone (int dimension, double rho){
    
    pheromone::rho = rho;
    pheromone::data.CLEAR();
    pheromone::data.RESIZE(1, dimension);
    
    for (int i = 0; i < pheromone::data.GET_N_ROW(); i++){
        for (int j = 0; j < pheromone::data.GET_N_COL(); j++)
            pheromone::data.SET_VALUE(1.0/2, i, j);
    }
    return;
    
};

/* adjust pheromone to fitness of a given element*/
void pheromone::adjust (path* path, fitness* fitness){
    
    for (int i = 0; i < pheromone::data.GET_N_COL(); i++){
        
        // remove later
        //cout << endl;
        //cout << path->best(fitness).at(i) << " ";
        
        if (path->best(fitness).at(i) == 1)
            pheromone::data.SET_VALUE(::min(pheromone::data.GET_VALUE(0,i)*(1-pheromone::rho) + pheromone::rho, ::max(1.0/pheromone::data.GET_N_COL(), 1 - 1.0/pheromone::data.GET_N_COL())), 0, i);
        else
            pheromone::data.SET_VALUE(::max(pheromone::data.GET_VALUE(0,i)*(1-pheromone::rho), ::min(1.0/pheromone::data.GET_N_COL(), 1 - 1.0/pheromone::data.GET_N_COL())), 0, i);
        
    }
    
    //remove later
    //cout << endl;
    //cout << endl;
    
    return;
    
};

int pheromone::dimension(){
    
    return (pheromone::data.GET_N_COL());
    
};

double pheromone::get (int i, int j){
    
    return(pheromone::data.GET_VALUE(i, j));
    
};