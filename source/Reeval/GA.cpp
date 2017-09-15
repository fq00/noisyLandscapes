//
//  GA.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 26.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "GA.hpp"
#include "OneMax.hpp"
#include "population.hpp"
#include "random.hpp"
#include "fitness.hpp"

using namespace std;

int GA::run(){
    
    // Step 1: set-up fitness and population classes
    
    class population population;
    class fitness fitness;
    population.set(GA::dimension, GA::size, GA::order);
    
    for (GA::N_STEPS = 0; GA::N_STEPS < GA::MAX_STEPS; GA::N_STEPS++){
        
        // Step 2: generate offspring
        
        population.offspring(GA::N_PARENTS);
        
        // Step 3: introduce mutation on last element
        
        population.mutation(population.size()-1);
        
        // Step 4: evaluate fitness
        
        fitness.fitnessGA(&population, GA::sigma, GA::n);
        
        // Step 5: verify convergence criterion
        
        if (population.check() == 0) break;
        
        // Step 6: kill weakest individual
        
        population.kill(fitness.results::max());
        
    }
    
    return (N_STEPS);
    
};

GA::GA(int dimension, int size, int order){
    
    GA::dimension = dimension;
    GA::size = size;
    GA::order = order;
    
    return;
    
};

void GA::posteriorNoise(double sigma, int n){
    
    GA::n = n;
    GA::sigma=  sigma;
    
    return;
    
};
