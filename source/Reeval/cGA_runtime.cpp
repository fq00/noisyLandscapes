//
//  cGA_runtime.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 05.01.16.
//  Copyright © 2016 Francesco Quinzan. All rights reserved.
//

#include "cGA_runtime.hpp"

void cGA_runtime::runtime(int seed){
    
    //int K = 10;
    
    typedef std::numeric_limits< double > dbl;
    ofstream cGA_results;
    cGA_results.precision(dbl::max_digits10);
    cGA_results.open(cGA_runtime::dir + "/cGA_runtime.txt");
    
    class header header;
    header.make_header(&cGA_results, "cGA", seed);
    cGA_runtime::makeLegend(&cGA_results);
    
    for (double sigma = ::sqrt(0); sigma < ::sqrt(1000000); sigma = sigma + ::sqrt(10)*2){
        
        cout << sigma << endl;
        
        //cGA_runtime::parametersCalibration(sigma, &K);
        for (int K = 1; K < 6; K++){
        CGA cGA(100, K);
        cGA.posteriorNoise(sigma, 1);
        
        for (int i = 1; i < 100000; i++){
            cGA_results << 100 << " ";
            cGA_results << sigma << " ";
            cGA_results << 1 << " ";
            cGA_results << K << " ";
            cGA_results << cGA.run() << endl;
            //cGA_results << cGA_runtime::cGAruntime(K, sigma) << endl;
            }
        }
    }
    
    cGA_results.close();
    return;
    
};

void cGA_runtime::parametersCalibration(double sigma, int* K){
    
    vector<int> runtime;
    for (int i = ::max(*K - 10, 2); i < *K + 10; i++){
        runtime.push_back(cGAruntime(::max(i, 2), sigma));
    }
    *K = minIndex(runtime) + ::max(*K - 10, 2);
    return;
    
};

int cGA_runtime::cGAruntime(int K, double sigma){
    
    CGA cGA(100, K);
    cGA.posteriorNoise(sigma, 1);
    
    double sampleMean = 0;
    for (int i = 0; i < 100; i++){
        sampleMean = sampleMean + cGA.run()*2;
    }
    sampleMean = sampleMean/100;
    return((int)sampleMean);
    
}

int cGA_runtime::minIndex(vector<int> arr){
    
    int minIndex = 0;
    for (int i = 0; i < arr.size(); i++)
        if (arr.at(minIndex) > arr.at(i)) minIndex = i;
    return(minIndex);
    
}

void cGA_runtime::makeLegend(ofstream* file){
    
    *file << "DIMENSION" << " ";
    *file << "SIGMA" << " ";
    *file << "N_RE_EVALUATIONS" << " ";
    *file << "OPTIMAL_K" << " ";
    *file << "N_FITNESS_EVALUATIONS" << endl;
    
};