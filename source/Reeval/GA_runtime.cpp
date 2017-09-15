//
//  GA_runtime.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 04.01.16.
//  Copyright © 2016 Francesco Quinzan. All rights reserved.
//

#include "GA_runtime.hpp"

void GA_runtime::runtime(int seed){

    int mu = 5;
    
    typedef std::numeric_limits< double > dbl;
    ofstream GA_results;
    GA_results.precision(dbl::max_digits10);
    GA_results.open(GA_runtime::dir + "/GA_runtime.txt");
    
    class header header;
    header.make_header(&GA_results, "GA", seed);
    GA_runtime::makeLegend(&GA_results);
    
    for (double sigma = ::sqrt(0); sigma < ::sqrt(100); sigma = sigma + ::sqrt(10)/16){
        GA_runtime::mu(sigma, &mu);
        GA_results << 100 << " ";
        GA_results << sigma << " ";
        GA_results << 1 << " ";
        GA_results << mu << " ";
        GA_results << GA_runtime::GAruntime(mu, sigma) << endl;
    }
    
    GA_results.close();
    return;

};

void GA_runtime::mu(double sigma, int* mu){
    
    vector<int> runtime;
    for (int i = ::max(*mu - 3, 2); i < *mu + 10; i++){
        runtime.push_back(GAruntime(::max(i, 2), sigma));
    }
    *mu = minIndex(runtime) + ::max(*mu - 3, 2);
    return;
    
};

int GA_runtime::GAruntime(int mu, double sigma){
    
    GA GA(100, mu, 2);
    GA.posteriorNoise(sigma, 1);
    
    double sampleMean = 0;
    for (int i = 0; i < 100; i++){
        sampleMean = sampleMean + GA.run()*mu;
    }
    sampleMean = sampleMean/100;
    return((int)sampleMean);
    
}

int GA_runtime::minIndex(vector<int> arr){
    
    int minIndex = 0;
    for (int i = 0; i < arr.size(); i++)
        if (arr.at(minIndex) > arr.at(i)) minIndex = i;
    return(minIndex);
    
}

void GA_runtime::makeLegend(ofstream* file){
    
    *file << "DIMENSION" << " ";
    *file << "SIGMA" << " ";
    *file << "N_RE_EVALUATIONS" << " ";
    *file << "OPTIMAL_MU" << " ";
    *file << "N_FITNESS_EVALUATIONS" << endl;
    
};