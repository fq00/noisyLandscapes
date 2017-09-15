//
//  EA_runtime.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 04.01.16.
//  Copyright © 2016 Francesco Quinzan. All rights reserved.
//

#include "EA_runtime.hpp"

void EA_runtime::runtime(int seed){
    
    int mu = 4;
    
    typedef std::numeric_limits< double > dbl;
    ofstream EA_results;
    EA_results.precision(dbl::max_digits10);
    EA_results.open(EA_runtime::dir + "/EA_runtime.txt");
    
    class header header;
    header.make_header(&EA_results, "EA", seed);
    EA_runtime::makeLegend(&EA_results);
    
    for (double sigma = ::sqrt(0); sigma < ::sqrt(100); sigma = sigma + ::sqrt(10)/16){
        EA_runtime::mu(sigma, &mu);
        EA_results << 100 << " ";
        EA_results << sigma << " ";
        EA_results << 1 << " ";
        EA_results << mu << " ";
        EA_results << EA_runtime::EAruntime(mu, sigma) << endl;
    }
    
    EA_results.close();
    return;
    
};

void EA_runtime::mu(double sigma, int* mu){
    
    vector<int> runtime;
    for (int i = ::max(*mu - 3, 2); i < *mu + 3; i++){
        runtime.push_back(EAruntime(::max(i, 2), sigma));
    }
    *mu = minIndex(runtime) + ::max(*mu - 3, 2);
    return;
    
};

int EA_runtime::EAruntime(int mu, double sigma){
    
    GA EA(100, mu, 2);
    EA.N_PARENTS = 1;
    EA.posteriorNoise(sigma, 1);
    
    double sampleMean = 0;
    for (int i = 0; i < 100; i++){
        sampleMean = sampleMean + EA.run()*mu;
    }
    sampleMean = sampleMean/100;
    return((int)sampleMean);
    
}

int EA_runtime::minIndex(vector<int> arr){
    
    int minIndex = 0;
    for (int i = 0; i < arr.size(); i++)
        if (arr.at(minIndex) > arr.at(i)) minIndex = i;
    return(minIndex);
    
}

void EA_runtime::makeLegend(ofstream* file){
    
    *file << "DIMENSION" << " ";
    *file << "SIGMA" << " ";
    *file << "N_RE_EVALUATIONS" << " ";
    *file << "OPTIMAL_MU" << " ";
    *file << "N_FITNESS_EVALUATIONS" << endl;
    
};