//
//  utility.hpp
//  bcTree
//
//  Created by Abhishek Singh on 26/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved.
//

#ifndef utility_hpp
#define utility_hpp
#include<vector>
#include <stdio.h>
#include "hoogaBugaa.hpp"

 /* @brief   Read from a file and returns an internal reprsentation of data
 ** @param [in] path_file -- path to the file that has data
 **
 ** @return Returns internal represenation of data
 **
*/

std::vector<std::vector<double> > * read_sample(const char * const path_file);
//std::vector<std::vector<double> > * read_sample1(const char * const  path_file);

std::vector<std::vector<double> > * read_sample_comma(const char * const  path_file);


//std::vector<std::vector<double> > * read_sample_comma1(const char * const  path_file);
//void streamingRead( );

//void read_sample_comma2(const char * const  path_file, std::vector<std::vector<double> >* train,std::vector<std::vector<double> >* test);

std::vector<std::vector<double> > * read_sample_training(const char * const  path_file, vector<long> *class_vector);
//std::vector<std::vector<double> > * read_sample_streaming(const char * const  path_file);
//std::vector<streamingPoint> * read_sample_streaming(const char * const  path_file);

std::vector<streamingPoint> * read_sample_streaming(const char * const  path_file);




#endif /* utility_hpp */
