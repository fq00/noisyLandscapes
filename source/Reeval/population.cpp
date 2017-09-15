//
//  population.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 28.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "population.hpp"
#include "random.hpp"
#include "table.hpp"

using namespace std;

/* generate random population */
void population::set(int dimension, int size, int order){
    
    population::ord = order;
    population::data.CLEAR();
    population::data.RESIZE(size, dimension);
    
    for (int i = 0; i < population::data.GET_N_ROW(); i++){
        for (int j = 0; j < population::data.GET_N_COL(); j++)
            population::data.SET_VALUE(randomEngine::int_uar(order), i, j);
    }
    
    return;
    
};

/* get population size (mu parameter) */
int population::size(){
    
    return(population::data.GET_N_ROW());
    
};

/* erase given individual */
void population::kill(int individual){
    
    population::data.ERASE_ROW(individual);
    return;
    
};

/* get individual as vector<int> */
vector<int> population::individual(int individual){
    
    return(population::data.GET_ROW(individual));
    
};

/* get poulation order */
int population::order(){
    
    return(population::ord);
    
};

/* get population dimension */
int population::dimension(){
    
    return(population::data.GET_N_COL());
    
};

/* introduce mutation factor */
void population::mutation(int row){
    
    /* mutation parameter */
    
    double p = 1.0 / population::dimension();
    
    /* intrduce mutation on individual*/
    
    for (int i = 0; i < population::dimension(); i++){
        if (randomEngine::uar() < p)
            population::data.SET_VALUE(randomEngine::int_uar(population::order()), row , i);
    }
    
    return;
    
}

/* create offspring */
void population::offspring(int n){
    
    population::data.RESIZE(population::size() + 1, population::dimension());
    vector<int> parents;
    int rnd;
    
    /* select n-parents */
    
    for (int i = 0; i < n; i++){
        parents.push_back(randomEngine::int_uar(population::size()-1));
    }
    
    /* perform recombination */
    
    for (int i = 0; i < population::dimension(); i++){
        rnd = randomEngine::int_uar(n);
        for (int j = 0; j < n; j++){
            if (rnd == j)
                population::data.SET_VALUE(data.GET_VALUE(parents.at(j), i), population::size()-1, i);
        }
    }
    return;
    
};

/* check if true optimum has been reached */
int population::check(){

    int err = 0;
    
    for (int i = 0; i < data.GET_N_ROW(); i++){
        err = 0;
        for (int j = 0; j < data.GET_N_COL(); j++){
            err = err + data.GET_VALUE(i, j);
        }
        if (err == 0) break;
    }
    return err;
};