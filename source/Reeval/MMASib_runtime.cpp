//
//  MMASib_runtime.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 04.01.16.
//  Copyright © 2016 Francesco Quinzan. All rights reserved.
//

#include "MMASib_runtime.hpp"

void MMASib_runtime::runtime(int seed){
        
    double rho = 0.04;
    int ants = 7;
        
    randomEngine::set_seed(1);
        
    typedef std::numeric_limits<double> dbl;
    ofstream MMASib_results;
    MMASib_results.precision(dbl::max_digits10);
    MMASib_results.open(MMASib_runtime::dir + "/MMASib_runtime.txt");
        
    class header header;
    header.make_header(&MMASib_results, "MMASib", seed);
    MMASib_runtime::makeLegend(&MMASib_results);
    
    
    double sigma = ::sqrt(10);
    //for (double sigma = ::sqrt(0); sigma < ::sqrt(100); sigma = sigma + ::sqrt(10)/16){
    for (int dimension = 2; dimension <= 100; dimension = dimension + 5){
    
        MMASib_runtime::parametersCalibration(sigma, &rho, &ants, dimension);
        MMASib_runtime::MMASibRuntime(ants, rho, sigma, dimension, &MMASib_results);
        //MMASib_results << dimension << " ";
        //MMASib_results << sigma << " ";
        //MMASib_results << 1 << " ";
        //MMASib_results.precision(3);
        //MMASib_results << rho << " ";
        //MMASib_results.precision(dbl::max_digits10);
        //MMASib_results << ants << " ";
        //MMASib_results << MMASib_runtime::MMASibRuntime(ants, rho, sigma, dimension) << endl;
        
    }
        
    MMASib_results.close();
    return;
        
};

void MMASib_runtime::parametersCalibration(double sigma, double* rho, int* ants, int dimension){
    
    ofstream fl;
    fl.open("Users/fq00/Desktop/temp.txt");
    
    vector<int> runTime;
    for (int i = *ants - 5; i < *ants + 5; i++){
        for (double j = *rho - 0.01; j < *rho + 0.01; j=j+0.001){
            runTime.push_back(MMASibRuntime(::max(i, 2), ::max(j, 0.001), sigma, dimension, &fl));
        }
    }
    *ants = ::floor(minIndex(runTime)/20) + ::max(*ants - 5, 2);
    *rho = ::max(*rho - 0.01, 0.001) + (minIndex(runTime)%20)*0.001;
    
    fl.close();
    
};

int MMASib_runtime::MMASibRuntime(int ants, double rho, double sigma, int dimension, ofstream *  MMASib_results){
    
    ACO MMASib(dimension, ants, rho);
    MMASib.posteriorNoise(sigma, 1);
    
    int sampleMean = 0;
    int temp = 0;
    
    for (int i = 0; i < 100; i++){
        temp = MMASib.run()*ants;
        sampleMean = sampleMean + temp;
        *MMASib_results << dimension << " ";
        *MMASib_results << sigma << " ";
        *MMASib_results << 1 << " ";
        //*MMASib_results.precision(3);
        *MMASib_results << rho << " ";
        //MMASib_results.precision(dbl::max_digits10);
        *MMASib_results << ants << " ";
        *MMASib_results << temp << endl;
    }
    sampleMean = sampleMean/100;
    return(sampleMean);
    
}

int MMASib_runtime::minIndex(vector<int> arr){
    
    int minIndex = 0;
    for (int i = 0; i < arr.size(); i++)
        if (arr.at(minIndex) > arr.at(i)) minIndex = i;
    return(minIndex);
    
}

void MMASib_runtime::makeLegend(ofstream* file){
    
    *file << "DIMENSION" << " ";
    *file << "SIGMA" << " ";
    *file << "N_RE_EVALUATIONS" << " ";
    *file << "OPTIMAL_RHO" << " ";
    *file << "OPTIMAL_N_ANTS" << " ";
    *file << "N_FITNESS_EVALUATIONS" << endl;
    
};