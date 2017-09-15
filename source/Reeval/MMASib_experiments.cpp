//
//  rAnalysis.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 26.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "MMASib_experiments.hpp"

void MMASib_experiments::parameter_calibration(string dir, int seed){

    randomEngine::set_seed(seed);
    int sample_size = 100;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    double sigma = ::sqrt(10);
    int r = 1;
    
    /* output file */
    
    ofstream MMASib_results;
    MMASib_results.precision(dbl::max_digits10);
    MMASib_results.open(dir + "/MMASib_parameter_calibration.txt");
    header::make_header(&MMASib_results, "MMASib", seed);
    MMASib_experiments::make_legend(&MMASib_results);
    
    for (int n_ants = 2; n_ants < 15; n_ants++){
        for (double evaporation = 0.03; evaporation < 0.06; evaporation = evaporation + 0.002){
            ACO ACO(dimension, n_ants, evaporation);
            ACO.posteriorNoise(sigma, r);
            
            /* run for given number of steps */
            
            for (int k = 0; k < sample_size; k++){
                
                MMASib_results << dimension << " ";
                MMASib_results << n_ants << " ";
                MMASib_results << evaporation << " ";
                MMASib_results << sigma << " ";
                MMASib_results << r << " ";
                MMASib_results << ACO.run()*n_ants*r << endl;
                
            }
            
        }
    }

    MMASib_results.close();
    return;

};

void MMASib_experiments::r_analysis(string dir, int seed){

    randomEngine::set_seed(seed);
    int sample_size = 100;
    
    /* variables */
    
    int dimension = 100;
    double evaporation = 0.045;
    int n_ants = 5;
    double sigma = ::sqrt(100);
    
    int results = 0;
    
    /* output file */
    
    ofstream MMASib_results;
    MMASib_results.open(dir + "/MMASib_r_analysis.txt");
    header::make_header(&MMASib_results, "MMASib", seed);
    MMASib_experiments::make_legend(&MMASib_results);
    
    for (int r = 1; r < 100; r++){
        ACO ACO(dimension, n_ants, evaporation);
        ACO.posteriorNoise(sigma, r);
            
        /* run for given number of steps */
            
        for (int k = 0; k < sample_size; k++){
                
            results = ACO.run();
            results = results*n_ants*r;
            cout << results << endl;

            MMASib_results << dimension << " ";
            MMASib_results << n_ants << " ";
            MMASib_results << evaporation << " ";
            MMASib_results << sigma << " ";
            MMASib_results << r << " ";
            MMASib_results << results << endl;
                
        }
            
    }
    
    MMASib_results.close();
    return;

};

void MMASib_experiments::variance_analysis(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 100;
    
    /* variables */
    
    int dimension = 100;
    double evaporation = 0.045;
    int n_ants = 5;
    int r = 5;
    
    int results = 0;
    
    /* output file */
    
    ofstream MMASib_results;
    MMASib_results.open(dir + "/MMASib_variance_analysis.txt");
    header::make_header(&MMASib_results, "MMASib", seed);
    MMASib_experiments::make_legend(&MMASib_results);
    
    for (double sigma = ::sqrt(0); sigma < ::sqrt(10)*14; sigma = sigma + ::sqrt(10)/2){
        ACO ACO(dimension, n_ants, evaporation);
        ACO.posteriorNoise(sigma, r);
        
        /* run for given number of steps */
        
        for (int k = 10; k < sample_size; k++){
            
            results = ACO.run()*n_ants*r;
            cout << results << endl;
            
            MMASib_results << dimension << " ";
            MMASib_results << n_ants << " ";
            MMASib_results << evaporation << " ";
            MMASib_results << sigma << " ";
            MMASib_results << r << " ";
            MMASib_results << results << endl;
            
        }
        
    }
    
    MMASib_results.close();
    return;
    
};

void MMASib_experiments::make_legend(ofstream* file){

    *file << "DIMENSION" << " ";
    *file << "N_ANTS" << " ";
    *file << "EVAPORATION" << " ";
    *file << "SIGMA" << " ";
    *file << "N_RE_EVALUATIONS" << " ";
    *file << "N_FITNESS_EVALUATIONS" << endl;
    
};