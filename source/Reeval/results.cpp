//
//  results.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 26.10.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "results.hpp"
#include "table.hpp"

using namespace std;

void results::add(double value){
    
    results::data.RESIZE(data.GET_N_ROW()+1, 1);
    results::data.SET_VALUE(value, results::data.GET_N_ROW()-1, 0);
    return;
    
};

void results::clear(){
    
    results::data.CLEAR();
    return;
    
};

void results::del(int i){

    results::data.ERASE_ROW(i);
    return;

};

double results::get (int i){

    return(data.GET_VALUE(i, 0));

};

int results::size(){

    return(data.GET_N_ROW());
    
};

int results::min(){
    
    double inf = results::data.GET_VALUE(0,0);
    int min = 0;
    
    for (int i = 1; i < results::data.GET_N_ROW(); i++){
        if (results::data.GET_VALUE(i,0) < inf){
            inf = results::data.GET_VALUE(i,0);
            min = i;
        }
    }
    
    return (min);
    
};

int results::max(){
    
    double sup = results::data.GET_VALUE(0,0);
    int max = 0;
    
    for (int i = 0; i < results::data.GET_N_ROW(); i++){
        if (results::data.GET_VALUE(i,0) > sup){
            sup = results::data.GET_VALUE(i,0);
            max = i;
        }
    }
    
    return (max);
    
};

double results::minimum(){
    
    return (results::data.GET_VALUE(results::min(), 0));
    
};

double results::maximum(){
    
    return (results::data.GET_VALUE(results::max(), 0));
    
};