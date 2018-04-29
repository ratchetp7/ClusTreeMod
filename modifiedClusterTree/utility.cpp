//
//  utility.cpp
//  bcTree
//
//  Created by Abhishek Singh on 26/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved.
//

#include "utility.hpp"
#include <string>
#include<iostream>
#include<fstream>
#include <sstream>
#include<stdlib.h>
#include "hoogaBugaa.hpp"
#define CLASSID 54
//#include<stdio>
std::vector<std::vector<double> > * read_sample(const char * const  path_file)
{
    std::string filename(path_file);
    
    std::ifstream file_stream(filename.c_str(),std::fstream::in);
    
    
    //file_stream.open(filename, std::ios::in);
    
    
    if(!file_stream.is_open())
    {
        return NULL;
    }
    
    std:: string line;
    std::vector<std::vector<double> > * dataset = new std::vector<std::vector<double> >();
    while(std::getline(file_stream, line)) {
        std::istringstream parser(line);
        std::vector<double> point;
        
        double coordinate = 0.0;
        while(parser >> coordinate) {
            point.push_back(coordinate);
//            std::cout<< "READ " << coordinate <<std::endl;
        }
                dataset->push_back(point);
    }
    file_stream.close();
    
    return dataset;
    
    
}

std::vector<std::vector<double> > * read_sample_training(const char * const  path_file, vector<long> *class_vector)
{
    //cout<<" TRAINING "<<endl;
    std::string filename(path_file);
    long classID= 0;
    
    std::ifstream file_stream(filename.c_str(),std::fstream::in);
    
    
    //file_stream.open(filename, std::ios::in);
    
    
    if(!file_stream.is_open())
    {
        return NULL;
    }
    
    std:: string line;
    std::vector<std::vector<double> > * dataset = new std::vector<std::vector<double> >();
    int count = 0;
    int c = 0;
    while(std::getline(file_stream, line)) {
        count = 0;
        std::istringstream parser(line);
        std::vector<double> point;
        std::string token;
        
        
        double coordinate = 0.0;
        //        while(parser >> coordinate) {
        //            point.push_back(coordinate);
        //            std::cout<< "READ " << coordinate <<std::endl;
        //        }
        c++;
        if( c > NUM_POINTS_TRAINING)
            break;
        //std::cout<<"LINE "<< c<<std::endl;
        //cout<<DIM+1<<endl;
        while(std::getline(parser, token, ',')) {
            
            if(count == (CLASSID))
            {
                classID = stof(token);
                class_vector->push_back(classID);
                //cout<<"HEY HEY CLASS IS "<<classID<<endl;
            }
            
            if(count >= DIM)
            {
                count++;
            }
            //std::cout<<"number "<<count<<std::endl;
            //std::cout << token << std::endl;;
            else{
            coordinate = stof(token);
           // cout<<"POINT IS "<<coordinate<<endl;
            point.push_back(coordinate);
            count++;

            //std::cout<<coordinate<<std::endl;;
            }
            //cgheck this out
            
        }
        
        dataset->push_back(point);
    }
    
    
    
    
    
    // cout<<ftell(file_stream)<<endl;
    file_stream.close();
    
    return dataset;
    
    
}

std::vector<streamingPoint> * read_sample_streaming(const char * const  path_file)
{
    long timeStamp = 0;
    long classID = 0;
    //cout<<" TESTING "<<endl;
    std::string filename(path_file);
    
    std::ifstream file_stream(filename.c_str(),std::fstream::in);
    
    std::vector<streamingPoint> * stream;
    stream = new std::vector<streamingPoint> ();

    
    //file_stream.open(filename, std::ios::in);
    
    
    if(!file_stream.is_open())
    {
        return NULL;
    }
    
    std:: string line;
    //std::vector<std::vector<double> > * dataset = new std::vector<std::vector<double> >();
    int count = 0;
    int c = 0;
//    int streamCount = 0;
    while(std::getline(file_stream, line)) {
        count = 0;
        std::istringstream parser(line);
        std::vector<double> point;
        std::string token;
        
        
        double coordinate = 0.0;
        //        while(parser >> coordinate) {
        //            point.push_back(coordinate);
        //            std::cout<< "READ " << coordinate <<std::endl;
        //        }
        c++;
        if( c > NUM_POINTS_STREAMING)
            break;
        //std::cout<<"LINE "<< c<<std::endl;
        while(std::getline(parser, token, ',')) {
            //count++;
//            if(count > DIM)
//            {
//                break;
//            }
            //std::cout<<"number "<<count<<std::endl;
            //std::cout << token << std::endl;;
//            coordinate = stof(token);
//            point.push_back(coordinate);
           // std::cout<<coordinate<<std::endl;;
            
            if(count == (CLASSID))
            {
                classID = stof(token);
                //class_vector->push_back(classID);
               // cout<<"HEY HEY CLASS IS "<<classID<<endl;
            }
            
            if(count >= DIM)
            {
                count++;
            }
            //std::cout<<"number "<<count<<std::endl;
            //std::cout << token << std::endl;;
            else{
                coordinate = stof(token);
               // cout<<"POINT IS "<<coordinate<<endl;
                point.push_back(coordinate);
                count++;
                
                //std::cout<<coordinate<<std::endl;;
            }
            //cgheck this out
            
        }
        
       // dataset->push_back(point);
        cluster* streamPoint = new cluster(&point,classID);
        
        streamingPoint* streamingPoint1;
        streamingPoint1 = (streamingPoint *)malloc(sizeof(streamingPoint));
        streamingPoint1->cluster = streamPoint;
        streamingPoint1->timeStamp = timeStamp++;
        streamingPoint1->budget = 1+random()%21;
       // cout<<"budget allocation-"<< streamingPoint1->budget << endl;
//        streamingPoint1->budget = 1;
        
//        7.0,18.0,5 2
//        10.0,15.0,4 5
//        4.0,16.0,5  5
        
//        if(streamCount == 0){
//            
//           streamingPoint1->budget = 2;//rand()% 21;
//            
//        }
//        if(streamCount == 1)
//        {
//            streamingPoint1->budget = 5;
//            
//        }
//        if(streamCount == 2)
//        {
//            streamingPoint1->budget = 5;
//            
//        }
//        streamCount++;
        
        stream->push_back(*streamingPoint1);

        
    }
    
    
    
    
    
    // cout<<ftell(file_stream)<<endl;
    file_stream.close();
    
    
    
    //points = new std::vector<std::vector<double>* >();
    
    

    
    //return dataset;
    return stream;
    
    
}



std::vector<std::vector<double> > * read_sample_comma1(const char * const  path_file)
{
    cout<<" READING FOR FIRST TIME "<<endl;
    std::string filename(path_file);
    
    std::ifstream file_stream(filename.c_str(),std::fstream::in);
    
    
    //file_stream.open(filename, std::ios::in);
    
    
    if(!file_stream.is_open())
    {
        return NULL;
    }
    
    std:: string line;
    std::vector<std::vector<double> > * dataset = new std::vector<std::vector<double> >();
    int count = 0;
    int c = 0;
    while(std::getline(file_stream, line)) {
        count = 0;
        std::istringstream parser(line);
        std::vector<double> point;
        std::string token;
        
        
        double coordinate = 0.0;
        //        while(parser >> coordinate) {
        //            point.push_back(coordinate);
        //            std::cout<< "READ " << coordinate <<std::endl;
        //        }
        c++;
        if( c > NUM_POINTS_TRAINING)
            break;
        //std::cout<<"LINE "<< c<<std::endl;
        while(std::getline(parser, token, ',')) {
            count++;
            if(count > DIM)
            {
                break;
            }
            //std::cout<<"number "<<count<<std::endl;
            //std::cout << token << std::endl;;
            coordinate = stof(token);
            point.push_back(coordinate);
            std::cout<<coordinate<<std::endl;;
        }
        
        dataset->push_back(point);
    }
    
    
    
    
    
   // cout<<ftell(file_stream)<<endl;
    file_stream.close();
    
    return dataset;
    
    
}







 
