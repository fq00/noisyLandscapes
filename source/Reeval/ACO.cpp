//
//  ACO.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 29.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "ACO.hpp"
#include "pheromone.hpp"
#include "path.hpp"

int ACO::run(){
    
    ofstream ACO_pheromone_analysis;
    ACO_pheromone_analysis.open ("/Users/fq00/Desktop/ACO_pheromone_analysis.txt");
    
    /* Step 1: set up values */
    class fitness fitness;
    class path path(ACO::size);
    class pheromone pheromone(ACO::dimension, ACO::rho);
    
    for (ACO::N_STEPS = 0; ACO::N_STEPS < ACO::MAX_STEPS; ACO::N_STEPS++){
        
        /* Step 2: choose random path accordingly to pheromone */
        path.set(&pheromone);
        
        /* Step 3: compute fitness */
        fitness.fitnessACO(&path, ACO::sigma, ACO::n);
        
        /* Step 4: check convergence condition */
        if (path.check() == ACO::dimension) break;
        
        /* Step 5: adjust pheromone to fitness (food gain) */
        pheromone.adjust(&path, &fitness);
        
        //for (int i = 0; i < path.lambda; i++){
        //    for (int j = 0; j < pheromone.dimension(); j++){
        //        cout << path.data.GET_VALUE(i, j) << " ";
        //    }
        //    cout << " with fitness: " << fitness.data.GET_VALUE(i,0) << endl;
        //}
        //cout << endl;
        
        //for (int j = 0; j < pheromone.data.GET_N_ROW(); j++){
        //    for (int i = 0; i < pheromone.data.GET_N_COL(); i++)
        //        ACO_pheromone_analysis << pheromone.data.GET_VALUE(0, i) << " ";
        //    ACO_pheromone_analysis << endl;
        //}
        //cout << endl;
        
    }
    
    ACO_pheromone_analysis.close();
    return (ACO::N_STEPS);
    
}

ACO::ACO(int dimension, int size, double rho){
    
    ACO::dimension = dimension;
    ACO::size = size;
    ACO::rho = rho;
    
    return;
    
}

void ACO::posteriorNoise(double sigma, int n){
    
    ACO::sigma=sigma;
    ACO::n = n;
    
    return;
    
};

//int ACO::control(path* path){
//    int err = 0;
//    vector<int> best = path->get();
//    for (int i = 0; i < best.size(); i++){
//        if (best.at(i) == 1){
//            err++;
//        };
//    };
//    return err;
//};