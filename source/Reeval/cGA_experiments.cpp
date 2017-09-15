//
//  cGA_experiments.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 07.12.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "cGA_experiments.hpp"

void cGA_experiments::parameter_calibration(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 10000;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    double sigma = ::sqrt(10);
    int r = 1;
    
    /* output file */
    
    ofstream cGA_results;
    cGA_results.precision(dbl::max_digits10);
    cGA_results.open(dir + "/cGA_parameter_calibration.txt");
    header::make_header(&cGA_results, "cGA", seed);
    cGA_experiments::make_legend(&cGA_results);
    
    for (double K = 2; K < 100; K++){
        CGA cGA(dimension, K);
        cGA.posteriorNoise(sigma, r);
            
        /* run for given number of steps */
            
        for (int k = 0; k < sample_size; k++){
                
            cGA_results << dimension << " ";
            cGA_results << K << " ";
            cGA_results << sigma << " ";
            cGA_results << r << " ";
            cGA_results << cGA.run()*2*r << endl;
            
        }
    }
    
    cGA_results.close();
    return;
    
};

void cGA_experiments::r_analysis(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 10000;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    double K = 2;
    double sigma = ::sqrt(100);
    
    /* output file */
    
    ofstream cGA_results;
    cGA_results.precision(dbl::max_digits10);
    cGA_results.open(dir + "/cGA_r_analysis.txt");
    header::make_header(&cGA_results, "cGA", seed);
    cGA_experiments::make_legend(&cGA_results);
    
    for (int r = 1; r < 1000; r++){
        CGA cGA(dimension, K);
        cGA.posteriorNoise(sigma, r);
        
        /* run for given number of steps */
        
        for (int k = 0; k < sample_size; k++){
            
            cGA_results << dimension << " ";
            cGA_results << K << " ";
            cGA_results << sigma << " ";
            cGA_results << r << " ";
            cGA_results << cGA.run()*2*r << endl;
            
        }
        
    }
    
    cGA_results.close();
    return;
    
};

void cGA_experiments::variance_analysis(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 100;
    
    /* variables */
    
    int dimension = 100;
    double K = 25;
    int r = 10;
    
    /* output file */
    
    ofstream cGA_results;
    cGA_results.open(dir + "/cGA_variance_analysis.txt");
    header::make_header(&cGA_results, "cGA", seed);
    cGA_experiments::make_legend(&cGA_results);
    
    for (double sigma = ::sqrt(0); sigma < ::sqrt(1000000); sigma = sigma + ::sqrt(100)){
        CGA cGA(dimension, K);
        cGA.posteriorNoise(sigma, r);
        
        /* run for given number of steps */
        
        for (int k = 10; k < sample_size; k++){
            
            cGA_results << dimension << " ";
            cGA_results << K << " ";
            cGA_results << sigma << " ";
            cGA_results << r << " ";
            cGA_results << cGA.run()*2*r << endl;
            
        }
        
    }
    
    cGA_results.close();
    return;
    
};

void cGA_experiments::make_legend(ofstream* file){
    
    *file << "DIMENSION" << " ";
    *file << "K" << " ";
    *file << "SIGMA" << " ";
    *file << "N_RE_EVALUATIONS" << " ";
    *file << "N_FITNESS_EVALUATIONS" << endl;
    
};
