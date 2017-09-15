//
//  individuals.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 06.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "individuals.hpp"

using namespace std;

/* get individuals dimension */
int individuals::dimension(){
    
    return(individuals::data.GET_N_COL());
    
};

/* get value of specific individual */
int individuals::get (int i, int j){
    
    return(individuals::data.GET_VALUE(i, j));
    
};


/* get individual as vector<int> */
vector<int> individuals::individual(int i){
    
    return(individuals::data.GET_ROW(i));
    
};

/* generate random population */
void individuals::set(distribution* distribution){
    
    individuals::data.CLEAR();
    individuals::data.RESIZE(2, distribution->dimension());
    
    for (int i = 0; i < individuals::data.GET_N_ROW(); i++){
        for (int j = 0; j < individuals::data.GET_N_COL(); j++){
            
            if (randomEngine::uar() < distribution->get(i))
                individuals::data.SET_VALUE(1, i, j);
        };
    };
    
    return;
    
};

/* get number of individuals - 2 by default*/
int individuals::size(){
    
    return(individuals::data.GET_N_ROW());
    
};

/* swap vectors accoring to fitness */
void individuals::swap(fitness* fitness){
    
    if(fitness->results::min() != fitness->results::max()){
        if (fitness->results::min() == 0){
            
            vector<int> temp = individuals::data.GET_ROW(0);
            for (int i = 0; i < individuals::data.GET_N_COL(); i++){
                individuals::data.SET_VALUE(individuals::data.GET_VALUE(1, i), 0, i);
                individuals::data.SET_VALUE(temp.at(i), 1, i);
            }
            
        }
    }
    
    return;
    
};

/* check if true optimum has been found */
int individuals::check(){
    
    int err = 0;
    
    for (int i = 0; i < data.GET_N_ROW(); i++){
        for (int j = 0; j < data.GET_N_COL(); j++){
            err = err + data.GET_VALUE(i, j);
        }
        if (err == data.GET_N_COL())
            break;
        else
            err = 0;
        
    }
    return err;
    
};