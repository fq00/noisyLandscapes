//
//  fitness.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 29.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "fitness.hpp"
#include "OneMax.hpp"
#include "results.hpp"
#include "population.hpp"
#include "path.hpp"

using namespace std;

void fitness::fitnessGA(class population* population, double sigma, int n){
    
    vector<int> individual;
    
    /* set up dynamic OneMax */
    
    OneMax::sigma = sigma;
    OneMax::n = n;
    OneMax::order = population->order();
    
    /* compute fitness for every individual */
    
    results::clear();
    for (int i = 0; i < population->size(); i++){
        individual = population->individual(i);
        results::add(OneMax::dynamic(&individual));
        individual.clear();
    }
    
    return;
    
};

/* compute the fitness of two individuals (used by CGA) */
void fitness::fitnessCGA(class individuals* individuals,  double sigma, int n) {
    
    vector<int> individual;
    
    /* set up dynamic OneMax */
    
    OneMax::sigma = sigma;
    OneMax::n = n;
    
    /* compute fitness*/
    
    results::clear();
    for (int i = 0; i < individuals->size(); i++){
        individual = individuals->individual(i);
        results::add(OneMax::dynamic(&individual));
        individual.clear();
    }
    
    return;
    
};

void fitness::fitnessACO(class path* path,  double sigma, int n) {
    
    vector<int> solution;
    
    /* set up dynamic OneMax */
    
    OneMax::sigma = sigma;
    OneMax::n = n;
    
    /* compute fitness*/
    
    results::clear();
    for (int i = 0; i < path->size(); i++){
        solution = path->get(i);
        results::add(OneMax::dynamic(&solution));
    }
    
    return;

};