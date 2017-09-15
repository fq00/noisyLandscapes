//
//  header.cpp
//  Reeval
//
//  Created by Francesco Quinzan on 26.11.15.
//  Copyright © 2015 Francesco Quinzan. All rights reserved.
//

#include "header.hpp"

void header::make_header(ofstream * file, string algorithm, int seed){
    
    *file << "GLOBAL OPTIMUM SEARCH OF RE-EVALUATED BINARY ONEMAX" << endl;
    *file << "WITH ADDED POSTERIOR NOISE ~N(0, SIGMA)\n"  << endl;
    
    *file << "NUMBER OF FITNESS EVALUATIONS FOR   " << algorithm << "\n" << endl;
    
    *file << "DATE:   ";
    time_t t = time(0);
    struct tm * now = localtime( & t );
    *file << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' <<  now->tm_mday;
    *file << " (year-month-day)" << endl;
    
    *file <<"TIME:   ";
    *file << (now->tm_hour) << ':' << (now->tm_min) << ':' <<  now->tm_sec;
    *file << " (hour:min:sec)" << endl;
    
    *file << "SEED:   " << seed << "\n" << endl;
    
    *file << "EXPERIMENTS PERFORMED ON:   " << "MacBook Pro (13\" Retina, Beginning 2015)" << endl;
    *file << "OPERATING SYSTEM:   " << "Mac OS X Version 10.11.1" << endl;
    *file << "PROCESSOR:   " << "2.7GHz dual-core Intel Core i5 (Turbo Boost up to 3.1GHz) with 3MB shared L3 cache" << endl;
    *file << "MEMORY:   " << "8GB of 1866MHz LPDDR3\n" << endl;

};