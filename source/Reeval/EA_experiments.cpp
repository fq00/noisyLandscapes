//
//  EA_experiments.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 02.12.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "EA_experiments.hpp"

void EA_experiments::parameter_calibration(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 100;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    double sigma = ::sqrt(10);
    int r = 1;
    
    int results = 0;
    
    /* output file */
    
    ofstream EA_results;
    EA_results.precision(dbl::max_digits10);
    EA_results.open(dir + "/EA_parameter_calibration.txt");
    header::make_header(&EA_results, "(mu + 1)-EA", seed);
    EA_experiments::make_legend(&EA_results);
    
    for (int mu = 6; mu < 100; mu++){
        GA EA(dimension, mu, 2);
        EA.posteriorNoise(sigma, r);
        EA.N_PARENTS = 1;
        
        /* run for given number of steps */
        
        for (int k = 0; k < sample_size; k++){
            
            results = EA.run()*mu*r;
            cout << results << endl;
            
            EA_results << dimension << " ";
            EA_results << mu << " ";
            EA_results << sigma << " ";
            EA_results << r << " ";
            EA_results << results << endl;
            
        }
        
    }
    
    EA_results.close();
    return;
    
};

void EA_experiments::r_analysis(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 100;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    int mu = 26;
    double sigma = 5;//::sqrt(100);
    
    /* output file */
    
    ofstream EA_results;
    EA_results.precision(dbl::max_digits10);
    EA_results.open(dir + "/EA_r_analysis.txt");
    header::make_header(&EA_results, "(mu + 1)-EA", seed);
    EA_experiments::make_legend(&EA_results);
    
    for (int r = 1; r < 100; r= r + 1){
        GA EA(dimension, mu, 2);
        EA.posteriorNoise(sigma, r);
        EA.N_PARENTS = 1;
        
        /* run for given number of steps */
        
        for (int k = 0; k < sample_size; k++){
            
            EA_results << dimension << " ";
            EA_results << mu << " ";
            EA_results << sigma << " ";
            EA_results << r << " ";
            EA_results << EA.run()*mu*r << endl;
            
        }
        
    }
    
    EA_results.close();
    return;
    
};

void EA_experiments::variance_analysis(string dir, int seed){
    
    randomEngine::set_seed(seed);
    int sample_size = 100;
    typedef std::numeric_limits< double > dbl;
    
    /* variables */
    
    int dimension = 100;
    int mu = 12;
    int r = 10;
    
    /* output file */
    
    ofstream EA_results;
    EA_results.precision(dbl::max_digits10);
    EA_results.open(dir + "/EA_variance_analysis.txt");
    header::make_header(&EA_results, "(mu + 1)-EA", seed);
    EA_experiments::make_legend(&EA_results);
    
    for (double sigma = ::sqrt(0); sigma < ::sqrt(10)*5.5; sigma = sigma + ::sqrt(10)/2){
        GA EA(dimension, mu, 2);
        EA.posteriorNoise(sigma, r);
        EA.N_PARENTS = 1;
        
        /* run for given number of steps */
        
        for (int k = 10; k < sample_size; k++){
            
            EA_results << dimension << " ";
            EA_results << mu << " ";
            EA_results << sigma << " ";
            EA_results << r << " ";
            EA_results << EA.run()*mu*r << endl;
            
        }
        
    }
    
    EA_results.close();
    return;
    
};

void EA_experiments::make_legend(ofstream* file){
    
    *file << "DIMENSION" << " ";
    *file << "MU" << " ";
    *file << "SIGMA" << " ";
    *file << "N_RE_EVALUATIONS" << " ";
    *file << "N_FITNESS_EVALUATIONS" << endl;
    
};