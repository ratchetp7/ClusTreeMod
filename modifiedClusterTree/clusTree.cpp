//
//  clusTree.cpp
//  bcTree
//
//  Created by Abhishek Singh on 27/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved.
//

#include "clusTree.hpp"
#include <cmath>
#include <vector>


std::vector<double>* ZEROLS = new std::vector<double>(DIM,0);

std::vector<double>* ZEROSS = new std::vector<double>(DIM,0);

double euclidean_distance2(const std::vector<double> * const point1, const std::vector<double> * const point2) {
    double distance = 0.0;
    //assert(point1->size() != point2->size());
    for (unsigned int dimension = 0; dimension < point1->size(); dimension++) {
        double difference = (point1->data()[dimension] - point2->data()[dimension]);
        distance += difference * difference;
    }
    // cout<< point1->data()[0]<<":" << point2->data()[0]<<":"<<sqrt(distance)<<endl;
    return sqrt(distance);
}

double get_distance(cluster * cluster1, cluster * cluster2){
    double distance = std::numeric_limits<double>::max();
    for(std::vector<std::vector<double>*>::iterator point1 =  cluster1->repPoints->begin(); point1 != cluster1->repPoints->end(); point1++){
        for(std::vector<std::vector<double>*>::iterator point2 = cluster2->repPoints->begin(); point2 != cluster2->repPoints->end();  point2++){
            double candidate_distance = euclidean_distance2(*point1, *point2);
            if(candidate_distance < distance){
                distance =  candidate_distance;
            }
        }
    }
    return distance;
}

//// given a point make a cluster out of it
//cluster* createCluster(std::vector<double>* onePint)
//{
//    cluster* newCluster = new cluster(onePint);
//    
//    return newCluster;
//}

//dept first search

void insertBreadthFirst(cluster* newPoint, int budget,  long timestamp)
{
    //what's the indicator of reaching the leaf?
    
}
//finding the pointer to the cluster that matches nbest with the

cluster* findBestCluster(cluster* toMerge, Node* pointer)
{
    double minDist =  std::numeric_limits<double>::max();
    double dist = 0.0;
    for(std::list<cluster *>:: iterator iter = pointer->begin(); iter != pointer->end(); iter++)
    {
        dist = get_distance(toMerge,(*iter));
        if(dist < minDist)
        {
            minDist = dist;
            toMerge->closest = (*iter);
            toMerge->distance_closest = minDist;
        }
    }
    return toMerge->closest;
    
    
}

//will update the cluster that this one is going to be merged
//get this verified

void updateBestCluster(cluster* toMerge, Node* oldNode)
{
    //updating mean
   // cout<<" MERGING :"<<((toMerge->mean)->data())[0]<<" WITH:  "<<toMerge->closest->mean->data()[0]<<" POINTS "<< toMerge->closest->numberOfPoints<<endl;
    
    
    
    for(int dimensions = 0; dimensions < toMerge->closest->mean->size(); dimensions++)
    {
        
        
        
        
        (*(toMerge->closest->mean))[dimensions] = ((toMerge->numberOfPoints * (*toMerge->mean)[dimensions]) + (toMerge->closest->numberOfPoints * (*toMerge->closest->mean)[dimensions]))/(toMerge->closest->numberOfPoints + (toMerge->numberOfPoints));
        
        //        (*oneTwo->mean)[dimensions] = ((one->numberOfPoints * (*one->mean)[dimensions]) + (two->numberOfPoints * (*two->mean)[dimensions])) / (one->numberOfPoints + two->numberOfPoints);
    }
    
    //updating  number of points
    toMerge->closest->numberOfPoints += toMerge->numberOfPoints;
    
    

    double radialDist = euclidean_distance2((*toMerge->points)[0], toMerge->closest->mean);
    double currNodeRadius = euclidean_distance2((*(toMerge->closest->repPoints))[0], toMerge->closest->mean);
    if(radialDist > currNodeRadius)
    {
        std::vector<double>* temporary = new std::vector<double>(*(*toMerge->points)[0]);

        
        //check if the number of reppoint size is over
        if(toMerge->closest->repPoints->size() >= REPR_COUNT)
        {
            //first create a vector of doubles to hold the value of the point
            //get it verified
                        //delete the previous ones
            delete (*(toMerge->closest->repPoints))[0];
            //update the representative point of the cluster
            (*(toMerge->closest->repPoints))[0] = temporary;
        }
        else
        {
            (*(toMerge->closest->repPoints)).push_back(temporary);
            
            
        }
        double distance = 0.0;
        for(std::list<cluster*>::iterator iter1  = oldNode->begin()   ; iter1 != oldNode->end(); iter1++)
        {
            double minDistance = std::numeric_limits<double>::max();
            for (std::list<cluster*>::iterator iter2 = oldNode->begin(); iter2 != oldNode->end(); iter2++) {
                
                 if(*iter1 != *iter2)
                 {
                     distance = get_distance(*iter1, *iter2);
                     if(distance < minDistance)
                     {
                         (*iter1)->distance_closest = distance;
                         (*iter1)->closest = *iter2;
                     }
                 }
            }
            
        }
        
        
        
    }
    
    //updating the dominance vector
    for(int i = 1 ; i < CLASSES ; i++)
    {
        (toMerge->closest->dom_vector)[i] += toMerge->dom_vector[i];
        if((toMerge->closest->dom_vector)[i] > 1000000 || toMerge->dom_vector[i] > 100000)
            cout<<" FARZI  RESULT HAI(1) "<<"lene wala:"<<(toMerge->closest->dom_vector)[i]<<"dene wala:"<<(toMerge->dom_vector)[i]<<endl;
    }
    
}

//get it verified
std::vector<std::vector<double> * >* giveResults(cluster* point)
{
    
    std::vector<std::vector<double> * >* rep =  new std::vector<std::vector<double>* >(*(point->closest->repPoints));
    
    return rep;

}

void pickHitchiker(cluster* pickFrom, cluster* putHere)
{
   
    
    std::vector<double>::iterator buffIter2 = pickFrom->buff->LS->begin();
    for(std::vector<double>::iterator buffIter1 = putHere->buff->LS->begin() ; buffIter1 != putHere->buff->LS->end() ; buffIter1++)
    {
        (*buffIter1) += (*buffIter2);
        buffIter2++;
    }
    //updating the squared sums
//    std::vector<double>::iterator buffIter2ss = pickFrom->buff->SS->begin();
//    for(std::vector<double>::iterator buffIter1ss = putHere->buff->SS->begin() ; buffIter1ss != putHere->buff->SS->end() ; buffIter1ss++)
//    {
//        (*buffIter1ss) += (*buffIter2ss);
//        buffIter2ss++;
//    }
    putHere->buff->numPoints += pickFrom->buff->numPoints;
    
    //initialse the buffer from the pickFrom cluster
    
    for(int i = 1; i < CLASSES; i++)
    {
        (putHere->buff->dom_buff_vector)[i] += (pickFrom->buff->dom_buff_vector)[i];
    }
    
    pickFrom->flushBuffer();
//    pickFrom->buff->LS = ZEROLS;
//    pickFrom->buff->SS = ZEROSS;
//    pickFrom->buff->numPoints = 0;
    //cout<<"hitchhicker picked:buff points:"<<pickFrom->buff->numPoints << ":" << (putHere->mean->data())[0]<< endl;
}

//BUFFER POINT

void dropPoint(cluster* newCluster, cluster* dropHere)
{
    std::vector<double>::iterator iterClus =  dropHere->buff->LS->begin();
    std::vector<double>::iterator iterPoint =  (*(newCluster->points))[0]->begin();
    while(iterClus != dropHere->buff->LS->end())
    {
        (*iterClus) += (*iterPoint);
        iterClus++;
        iterPoint++;
    }
    
   // std::vector<double>::iterator iterClusss =  dropHere->buff->SS->begin();
    //std::vector<double>::iterator iterPointss =  (*(newCluster->points))[0]->begin();
//    while(iterClusss != dropHere->buff->SS->end())
//    {
//        (*iterClusss) = (*iterClusss)+ ((*iterPointss)*(*iterPointss));
//        iterClusss++;
//        iterPointss++;
//    }
    dropHere->buff->numPoints += 1;
    for(int i = 1; i < CLASSES; i++)
    {
        (dropHere->buff->dom_buff_vector)[i] +=(newCluster->dom_vector)[i];
        if((dropHere->buff->dom_buff_vector)[i] > 1000000)
            cout<<" FARZI  RESULT HAI(2)"<< "lene wala:"<<(dropHere->buff->dom_buff_vector)[i]<<"dene wala: "<<(newCluster->dom_vector)[i]<<endl;
        

    }
    
    
   // cout<< "point buffered: number of points:" <<dropHere->buff->numPoints<<":"<< (dropHere->buff->LS->data())[0]<< endl;
    
    
}

//CHANGES
void dropHitchiker(cluster* pickFrom, cluster* dropHere)
{
    
    //updating the linear sums
    std::vector<double>::iterator buffIter2 = pickFrom->buff->LS->begin();
    for(std::vector<double>::iterator buffIter1 = dropHere->buff->LS->begin() ; buffIter1 != dropHere->buff->LS->end() ; buffIter1++)
    {
        (*buffIter1) += (*buffIter2);
        buffIter2++;
    }
//    //updating the squared sums
//    std::vector<double>::iterator buffIter2ss = pickFrom->buff->SS->begin();
//    for(std::vector<double>::iterator buffIter1ss = dropHere->buff->SS->begin() ; buffIter1ss != dropHere->buff->SS->end() ; buffIter1ss++)
//    {
//        (*buffIter1ss) += (*buffIter2ss);
//        buffIter2ss++;
//    }

    

   dropHere->buff->numPoints += pickFrom->buff->numPoints;
    //cout<< "HitchHicker buffered: number of points:" <<dropHere->buff->numPoints<< ":"<< (dropHere->buff->LS->data())[0]<<endl;
    
    for(int i = 1; i < CLASSES; i++)
    {
        (dropHere->buff->dom_buff_vector)[i] += (pickFrom->buff->dom_buff_vector)[i];
    }
    //initialse the buffer from the pickFrom cluster
    pickFrom->flushBuffer();
//    pickFrom->buff->LS = ZEROLS;
//    pickFrom->buff->SS = ZEROSS;
//    pickFrom->buff->numPoints = 0;
    
    
}


//decay funtion for a node
void makeOlder(Node* treeNode, long delta){
    double decayFactor = pow(BETA, (-1)*delta*LAMBDA);
    for(list<cluster*>::iterator decayItr = treeNode->begin(); decayItr != treeNode->end(); decayItr++){
        for(vector<vector<double>* >::iterator itr1 = (*decayItr)->repPoints->begin(); itr1 != (*decayItr)->repPoints->end(); itr1++){
            for(vector<double>::iterator itr2 = (*itr1)->begin(); itr2 != (*itr1)->end(); itr2++){
                (*itr2) *= decayFactor;
            }
        }
        
        //decay the mean
        for(vector<double> :: iterator meanItr = (*decayItr)->mean->begin(); meanItr != (*decayItr)->mean->end(); meanItr++){
            (*meanItr) *= decayFactor;
        }
        
        if((*decayItr)->buff->numPoints != 0){
            //decay the buff LS
            for(std::vector<double> :: iterator buffDecayItrLS = (*decayItr)->buff->LS->begin(); buffDecayItrLS != (*decayItr)->buff->LS->end(); buffDecayItrLS++){
                (*buffDecayItrLS) *= decayFactor;
            }
            //decay the buff SS
//            for(vector<double> :: iterator buffDecayItrSS = (*decayItr)->buff->SS->begin(); buffDecayItrSS != (*decayItr)->buff->SS->end(); buffDecayItrSS++){
//                (*buffDecayItrSS) *= decayFactor;
//            }
        }
    }
}

cluster* findBestBuffCluster(buff * buffer, Node* pointer)
{
    double minDist =  std::numeric_limits<double>::max();
    double dist;
    cluster*  closest = nullptr;
    //normalise the LS vector
    double singlePoint = 0.0;
    std::vector<double>* newLS = new vector<double>();
    
        for(std::vector<double>:: iterator buffIter = buffer->LS->begin(); buffIter != buffer->LS->end(); buffIter++)
    {
        singlePoint = (*buffIter)/(buffer->numPoints);
        newLS->push_back(singlePoint);
    }
    std::vector<double>* meanS;
    
    
    for(std::list<cluster *>:: iterator iter = pointer->begin(); iter != pointer->end(); iter++)
    {
        meanS = (*iter)->mean;
        dist = euclidean_distance2(newLS, meanS);
        
        
        if(dist < minDist)
        {
            minDist = dist;
            closest = (*iter);
        }
    }
    return closest;
}


void recalcNeighbors(cluster* clusterA, cluster* clusterB, cluster* clusterAB, Node* insertNode){
    double distanceA, distanceB;                 //temporaries to hold distances
    //check for the nearest neighbors of clusterA and clusterB
    //set clusterA and clusterB as each others closest
    clusterA->closest = clusterB;
    clusterA->distance_closest = get_distance(clusterA, clusterB);
    clusterB->closest = clusterA;
    clusterB->distance_closest = clusterA->distance_closest;
    
    //iterate over the whole node's clist
    for(list<cluster*>::iterator nodeItr = insertNode->cList.begin(); nodeItr != insertNode->cList.end(); nodeItr++){
        if((*nodeItr) != clusterAB){
            distanceA = get_distance(clusterA, (*nodeItr));
            distanceB = get_distance(clusterB, (*nodeItr));
            if(distanceA <= clusterA->distance_closest){
                clusterA->closest = *nodeItr;
                clusterA->distance_closest = distanceA;
            }
            if(distanceB <= clusterB->distance_closest){
                clusterB->closest = *nodeItr;
                clusterB->distance_closest = distanceB;
            }
            if((*nodeItr)->closest == clusterAB){
                (*nodeItr)->distance_closest = distanceA;
                (*nodeItr)->closest = clusterA;
                if(distanceB < (*nodeItr)->distance_closest){
                    (*nodeItr)->distance_closest = distanceB;
                    (*nodeItr)->closest = clusterB;
                }
            }
        }
    }
}
