//
//  GA_experiments.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 27.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "GA_experiments.hpp"

void GA_experiments::parameter_calibration(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 100;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    //double sigma = ::sqrt(10);
    double sigma = ::sqrt(100);
    int r = 1;
    
    /* output file */
    
    ofstream GA_results;
    GA_results.precision(dbl::max_digits10);
    GA_results.open(dir + "/GA_parameter_calibration.txt");
    header::make_header(&GA_results, "(mu + 1)-GA", seed);
    GA_experiments::make_legend(&GA_results);
    //mu = 5
    for (int mu = 15; mu < 100; mu++){
        GA GA(dimension, mu, 2);
        GA.posteriorNoise(sigma, r);
            
        /* run for given number of steps */
            
        for (int k = 0; k < sample_size; k++){
                
            GA_results << dimension << " ";
            GA_results << mu << " ";
            GA_results << sigma << " ";
            GA_results << r << " ";
            GA_results << GA.run()*mu*r << endl;
                
        }
        
    }
    
    GA_results.close();
    return;
    
};

void GA_experiments::r_analysis(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 100;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    int mu = 10;
    double sigma = ::sqrt(100);
    
    /* output file */
    
    ofstream GA_results;
    GA_results.precision(dbl::max_digits10);
    GA_results.open(dir + "/GA_r_analysis.txt");
    header::make_header(&GA_results, "(mu + 1)-GA", seed);
    GA_experiments::make_legend(&GA_results);
    
    for (int r = 3; r < 100; r= r + 1){
        GA GA(dimension, mu, 2);
        GA.posteriorNoise(sigma, r);
        
        /* run for given number of steps */
        
        for (int k = 0; k < sample_size; k++){
            
            GA_results << dimension << " ";
            GA_results << mu << " ";
            GA_results << sigma << " ";
            GA_results << r << " ";
            GA_results << GA.run()*mu*r << endl;
            
        }
        
    }
    
    GA_results.close();
    return;
    
};

void GA_experiments::variance_analysis(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 100;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    int mu = 10;
    int r = 10;
    
    /* output file */
    
    ofstream GA_results;
    GA_results.precision(dbl::max_digits10);
    GA_results.open(dir + "/GA_variance_analysis.txt");
    header::make_header(&GA_results, "(mu + 1)-GA", seed);
    GA_experiments::make_legend(&GA_results);
    
    for (double sigma = ::sqrt(0); sigma < ::sqrt(10)*7.5; sigma = sigma + ::sqrt(10)/2){
        GA GA(dimension, mu, 2);
        GA.posteriorNoise(sigma, r);
        
        /* run for given number of steps */
        
        for (int k = 10; k < sample_size; k++){

            GA_results << dimension << " ";
            GA_results << mu << " ";
            GA_results << sigma << " ";
            GA_results << r << " ";
            GA_results << GA.run()*mu*r << endl;
            
        }
        
    }
    
    GA_results.close();
    return;
    
};

void GA_experiments::make_legend(ofstream* file){
    
    *file << "DIMENSION" << " ";
    *file << "MU" << " ";
    *file << "SIGMA" << " ";
    *file << "N_RE_EVALUATIONS" << " ";
    *file << "N_FITNESS_EVALUATIONS" << endl;
    
};