//
//  CGA.cpp
//  OneMax
//
//  Created by Francesco Quinzan on 06.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "CGA.hpp"

using namespace std;

/* constructor - set dimension and K parameter */
CGA::CGA(int dimension, double K){
    
    CGA::dimension = dimension;
    CGA::K = K;
    
    return;
    
}

/* set posterior noise */
void CGA::posteriorNoise(double sigma, int n){
    
    CGA::sigma = sigma;
    CGA::n = n;
    
    return;
    
};

/* run algorithm */
int CGA::run(){
    
    /* Step 1: set up values */
    //class fitness fitness;
    
    /* Do dostribution*/
    vector<long double> distribution;
    for (int i = 0; i < CGA::dimension; i++)
        distribution.push_back(0.5);
    
    vector<int> x, y;
    for(int i = 0; i < distribution.size(); i++){
        x.push_back(0);
        y.push_back(0);
    }
    
    for (CGA::nSteps = 0; CGA::nSteps < CGA::maxSteps; CGA::nSteps++){
        
        /* Step 2: set random individuals with distribution */
        for(int i = 0; i < distribution.size(); i++){
            if ((long double)randomFunction::realUar() < distribution.at(i))
                x.at(i) = 1;
            else
                x.at(i) = 0;
            if ((long double)randomFunction::realUar() < distribution.at(i))
                y.at(i) = 1;
            else
                y.at(i) = 0;
        }
        
        /* Step 4: check convergence condition */
        if ((int)CGA::g(&x) == CGA::dimension) break;
        if ((int)CGA::g(&y) == CGA::dimension) break;
        
        /* Step 5: swap elements according to fitness */
        if (CGA::f(&x) < CGA::f(&y)) CGA::swap(&x, &y);
        
        /* Step 6: adjust pheromone to fitness (food gain) */
        for (int i = 0; i < distribution.size(); i++){
            if (x.at(i) > y.at(i))
                distribution.at(i) = distribution.at(i) + 1/CGA::K;
            if (x.at(i) < y.at(i))
                distribution.at(i) = distribution.at(i) - 1/CGA::K;
        }
        
    }
    
    return (CGA::nSteps*2*CGA::n);
    
}

double CGA::f(vector<int>* vec){
    
    int res = 0;
    for (int i = 0; i < vec->size(); i++) res = res + vec->at(i);
    return res + randomFunction::nrm(0, n*cGA::sigma)/n;
    
}

double CGA::g(vector<int>* vec){
    
    int res = 0;
    for (int i = 0; i < vec->size(); i++) res = res + vec->at(i);
    return res;
    
}

void CGA::swap(vector<int> * x, vector<int> * y){
    
    vector<int> z;
    for (int i = 0; i < x->size(); i++){
        z.push_back(y->at(i));
        y->at(i) = x->at(i);
        x->at(i) = z.at(i);
    }
    return;
    
}
