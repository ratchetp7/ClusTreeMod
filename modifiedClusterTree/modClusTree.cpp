//
//  hoogaBugaa.cpp
//  bcTree
//
//  Created by Abhishek Singh on 23/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved.
//



#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>
//
//  agloClusTree.cpp
//  agloClusTree
//
//  Created by Abhishek Singh on 21/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved. //

#include "hoogaBugaa.hpp"






//bool compare_nocase (const std::string& first, const std::string& second)
//{
//    unsigned int i=0;
//    while ( (i<first.length()) && (i<second.length()) )
//    {
//        if (tolower(first[i])<tolower(second[i])) return true;
//        else if (tolower(first[i])>tolower(second[i])) return false;
//        ++i;
//    }
//    return ( first.length() < second.length() );
//}
//
//
//void Node::updateClosest()
//{
//    cluster* c1;
//    cluster* c2;
//    //arranging by closest means and not representative points
//    for(std::list<cluster*>::iterator iter = this->cList.begin(); iter != this->cList.end(); iter ++)
//    {
//        c1 =     }
//}
//

//bool compare_nodes(const cluster* one, const cluster* two)
//{
//    
//}















double euclidean_distance1(const std::vector<double> * const point1, const std::vector<double> * const point2) {
    double distance = 0.0;
 //assert(point1->size() != point2->size());
 for (unsigned int dimension = 0; dimension < point1->size(); dimension++) {
 double difference = (point1->data()[dimension] - point2->data()[dimension]);
 distance += (difference * difference);
 }
    distance = sqrt(distance);
 return distance;
 }


double heapNTree::get_distance(cluster * cluster1, cluster * cluster2){
    //cout<<"GET DISTANCE CALLED"<<endl;
    double distance = std::numeric_limits<double>::max();
    //std:: vector<std::vector<double>* >* repPoints;
    for(std::vector<std::vector<double>*>::iterator point1 =  cluster1->repPoints->begin(); point1 != cluster1->repPoints->end(); point1++){
        for(std::vector<std::vector<double>*>::iterator point2 = cluster2->repPoints->begin(); point2 != cluster2->repPoints->end();  point2++){
            double candidate_distance = euclidean_distance1(*point1, *point2);
            if(candidate_distance < distance){
                distance =  candidate_distance;
            }
        }
    }
    return distance;
}

double get_distancelol(cluster * cluster1, cluster * cluster2){
    //cout<<"GET DISTANCE CALLED"<<endl;
    double distance = std::numeric_limits<double>::max();
    //std:: vector<std::vector<double>* >* repPoints;
    for(std::vector<std::vector<double>*>::iterator point1 =  cluster1->repPoints->begin(); point1 != cluster1->repPoints->end(); point1++){
        for(std::vector<std::vector<double>*>::iterator point2 = cluster2->repPoints->begin(); point2 != cluster2->repPoints->end();  point2++){
            double candidate_distance = euclidean_distance1(*point1, *point2);
            if(candidate_distance < distance){
                distance =  candidate_distance;
            }
        }
    }
    return distance;
}


//racheck
void remerge(cluster* one, cluster* two, cluster* oneTwo)
{
    oneTwo->numberOfPoints = (one->numberOfPoints + two->numberOfPoints + one->buff->numPoints + two->buff->numPoints);
    //find the new mean
    for(int dimensions = 0; dimensions < oneTwo->mean->size(); dimensions++)
    {
        (*oneTwo->mean)[dimensions] = ((one->numberOfPoints * (*one->mean)[dimensions]) + (*one->buff->LS)[dimensions] + (*two->buff->LS)[dimensions] + (two->numberOfPoints * (*two->mean)[dimensions])) / oneTwo->numberOfPoints;

 
//        (*oneTwo->mean)[dimensions] = ((one->numberOfPoints * (*one->mean)[dimensions]) + (two->numberOfPoints * (*two->mean)[dimensions])) / (one->numberOfPoints + two->numberOfPoints);
    }
    long number_repr_points = 0;
    //how many representative points to be considered?
    if((one->repPoints->size() + two->repPoints->size()) > REPR_COUNT)
        number_repr_points = REPR_COUNT;
    else
        number_repr_points = (one->repPoints->size() + two->repPoints->size());
    
    
    // make a temporary holder for repPoints of one and two points
    std:: vector<std::vector<double>* >* holder;
    holder =  new std::vector<std::vector<double>* >();
    
    holder->insert(holder->end(),one->repPoints->begin(),one->repPoints->end());
    holder->insert(holder->end(),two->repPoints->begin(),two->repPoints->end());

    std::vector<double> *meanBuffOne = new std::vector<double>();
    std::vector<double> *meanBuffTwo = new std::vector<double>();
    if(one->buff->numPoints != 0){
        for(int dim = 0; dim < DIM; dim++){
            meanBuffOne->push_back((*one->buff->LS)[dim]/one->buff->numPoints);
        }
        holder->push_back(meanBuffOne);
    }
//    if(two->buff->numPoints != 0){
//        for(int dim = 0; dim < DIM; dim++){
//            meanBuffTwo->push_back((*two->buff->SS)[dim]/two->buff->numPoints);
//        }
//        holder->push_back(meanBuffTwo);
//    }
    
    double distance = 0;
    double maximal_distance = 0;
    std::vector<double>* maximal_pointer = nullptr;
    std::vector<double>* point1 = nullptr;
    std::vector<std::vector<double>* >::iterator remove;
    
    //take 2c representative points and find the furthest ones
    
    for(unsigned int index =  0; index < number_repr_points; index++)
    {
        
        distance = 0;
        remove = holder->end();
        maximal_distance = 0;
        maximal_pointer = *(holder->begin());
        if(index == 0)
        {
            point1 = oneTwo->mean;
        }
        for(std::vector<std::vector<double>* >::iterator iter = holder->begin(); iter != holder->end() ; iter++)
        {
            distance =  euclidean_distance1(point1, (*iter));
            if(maximal_distance < distance)
            {
                maximal_distance = distance;
                maximal_pointer = (*iter);
                remove = iter;
            }
            
        }
        (oneTwo->repPoints->push_back(new vector<double>(*maximal_pointer)));
//        (*(oneTwo->repPoints))[index] = new vector<double>(*maximal_pointer);
        point1 = maximal_pointer;
        if(remove != holder->end())
            holder->erase(remove);
    }
    //update the radius too!!!
    oneTwo->radius = euclidean_distance1(oneTwo->mean, (*oneTwo->repPoints)[0]);
    for(int i=1; i <CLASSES; i++){
        (oneTwo->dom_vector)[i] = (one->dom_vector)[i] + (two->dom_vector)[i];
        if((oneTwo->dom_vector)[i] > 1000000)
            cout<<" FARZI  RESULT HAI (3)"<<"pehla:"<<(one->dom_vector)[i]<<" dusra:"<< (two->dom_vector)[i]<<endl;
    }
    
    for(int i=1; i <CLASSES; i++){
        (oneTwo->buff->dom_buff_vector)[i] += (one->buff->dom_buff_vector)[i] + (two->buff->dom_buff_vector)[i];
        if((oneTwo->dom_vector)[i] > 1000000)
            cout<<" FARZI  RESULT HAI (4) pehla:"<< (one->buff->dom_buff_vector)[i] << "dusra: "<<(two->buff->dom_buff_vector)[i]<<endl;
    }
    
    
}

void heapNTree::buildHeap(std::vector< std::vector<double> > * data,std::vector<long>* class_vector){
    std::vector<std::vector<double> > :: iterator it;
    //int pointNumber = 0;
    long dom_class = 0;
    std::vector<long>::iterator vec =  class_vector->begin();
    for( it = data->begin()  ; it != data->end() ; it++){
        dom_class = (*vec);
        vec++;
       // cout<<"THE CLASSES "<< dom_class<<endl;
        std::list<cluster*> :: iterator heapit = heap->end();
        cluster* newCluster =  new cluster((std::vector<double> *) &(*it),dom_class);
        (heap)->insert(heapit,newCluster);
        //cout<< heap->size()<< endl;
        //debug
        //dummyHeap->push_back(*newCluster);
    }
    
    for(std::list<cluster *> :: iterator firstCluster = heap->begin();  firstCluster != heap->end(); firstCluster++){
       // cout<<"BEFORE MICRO-CLUSTERS"<<endl;
        double minimumDist = std::numeric_limits<double>::max();
        cluster* closestCluster =  nullptr;
        for (std::list<cluster*> :: iterator secondCluster = heap->begin(); secondCluster != heap->end();  secondCluster++){
           
            if(*firstCluster !=  *secondCluster){
                double distance =  get_distance(*firstCluster, *secondCluster);
                if(distance < minimumDist){
                    minimumDist = distance;
                    closestCluster =  *secondCluster;
                    
                }
                
            }
            
          
        }
        (*firstCluster)->closest = closestCluster;
       // if(DEBUG)
           // cout<<closestCluster<<endl;
        
        (*firstCluster)->distance_closest = minimumDist;
        // cout<<"first" << *firstCluster << "firstClosest" << closestCluster << endl;
        
        //cout<<"closest"<<minimumDist<<endl;
    }
        auto distance_comparison = [](cluster * cluster1, cluster * cluster2) { return cluster1->distance_closest < cluster2->distance_closest; };
        heap->sort(distance_comparison);
//    cout<<"INITIAL HEAP CREATION"<<endl;
//    for(std::list<cluster*>:: iterator it = heap->begin(); it != heap->end(); it++){
//        cout<<"Point "<< ":"<< (*it)->mean->data()[0]<<"Closest Point "<<":"<< (*it)->closest->mean->data()[0]<<":"<<(*it)->distance_closest <<endl;
//        cout<<endl;
    

    
    
  /*  if(DEBUG){
        
            std::cout<< "INITIAL HEAP"<<std::endl;
        
            for(list<cluster*>::iterator it = heap->begin(); it != heap->end(); it++){
                std::cout<< (((*it)->points[0][0])) << std::endl;
            }
        
        
    } */
    
        
}
    
    



void heapNTree::merge(cluster * cluster1, cluster * cluster2, cluster* merged_cluster,const size_t number_repr_points,const double compression){
    
    
    // create new cluster pointer and add all the points of both clusters
    
    merged_cluster->insertPoint(cluster1->points);
    merged_cluster->insertPoint(cluster2->points);
    
    
    merged_cluster->mean = new std::vector<double>((*cluster1->points)[0]->size(), 0);
    
    
    //update the means of the merged cluster
    for(int dimensions = 0; dimensions < merged_cluster->mean->size(); dimensions ++){
        (*merged_cluster->mean)[dimensions] = (cluster1->points->size() * (*cluster1->mean)[dimensions] + cluster2->points->size() * (*cluster2->mean)[dimensions]) / (cluster1->points->size() + cluster2->points->size());
        
    }
    
    
    
    // finding the rep points of the merged cluster
    std::set<std::vector<double> *> * temporary = new std::set<std::vector<double> *>();
    for (unsigned int index = 0; index < number_repr_points; index++) {
       // cout<<"THE NUMBER OF REP POINTS FOR "<<merged_cluster->mean->data()[0]<< " IS "<< number_repr_points <<endl;
        double maximal_distance = 0;
        std::vector<double> * maximal_point = nullptr;
        
        
        for (std::vector<std::vector<double> *>::iterator point = merged_cluster->points->begin(); point != merged_cluster->points->end(); point++) {
            double minimal_distance = 0;
            if (index == 0) {
                minimal_distance = euclidean_distance1(*point, merged_cluster->mean);
            }
            else {
                double temp_minimal_distance = std::numeric_limits<double>::max();
                for (auto p : (*temporary)) {
                    double minimal_candidate = euclidean_distance1(*point, p);
                    if (minimal_candidate < temp_minimal_distance) {
                        temp_minimal_distance = minimal_candidate;
                    }
                }
                
                minimal_distance = temp_minimal_distance;
            }
            if(index == 0){
                if (minimal_distance >= maximal_distance) {
                    merged_cluster->radius = minimal_distance;
                }
                
            }
            
            if (minimal_distance >= maximal_distance) {
                maximal_distance = minimal_distance;
                maximal_point = *point;
            }
            
            
        }
        if (temporary->find(maximal_point) == temporary->end()) {
            temporary->insert(maximal_point);
        }
        
    }
    
   // cout << "!!!!!!!!!!!!!!!!!! REP POINTS OF !!!!!!!!!!!!!!!!!  number "<< number_repr_points<<endl;
    //inserting the rep points from temporary to the merged cluster
    for (std::set<std::vector<double> *>::iterator point = temporary->begin(); point != temporary->end(); point++) {
        std::vector<double> * representative_point = new std::vector<double>((*point)->size(), 0);
        for (unsigned int index = 0; index < (*point)->size(); index++) {
           // cout<< " DEKH0 " << ((*(*point))[index]) <<endl;
           // cout<< " AUR DEKHO "<< (*(*point))[index] + compression * ( (*merged_cluster->mean)[index] - (*(*point))[index])<<endl;
            (*representative_point)[index] = (*(*point))[index];
           // + compression * ( (*merged_cluster->mean)[index] - (*(*point))[index] );
        }
        
        merged_cluster->repPoints->push_back(representative_point);
       
      //  cout << " POINT ::"<<merged_cluster->mean->data()[0]<<" REP  :: "<<representative_point->data()[0]<<endl;
        
    }
   // cout<<endl;
    
    delete temporary;
    temporary = nullptr;
    
    for(int i = 1; i < CLASSES; i++)
    {
        (merged_cluster->dom_vector)[i] = (cluster1->dom_vector)[i] + (cluster2->dom_vector)[i];
        if((merged_cluster->dom_vector)[i] > 1000000)
            cout<<" FARZI  RESULT HAI (5)"<< "pehla: "<<(cluster1->dom_vector)[i]<<" Dusra: "<< (cluster2->dom_vector)[i]<<endl;

    }
    
}



void heapNTree::remove_representative_points(cluster * cluster) {
    for (std::vector<std::vector<double> *>::iterator point = cluster->repPoints->begin(); point != cluster->repPoints->end(); point++) {
        tree->remove(*point);
    }
}


void heapNTree::insert_representative_points(cluster * cluster) {
    for (std::vector<std::vector<double> *>::iterator point = cluster->repPoints->begin(); point != cluster->repPoints->end(); point++) {
        tree->insert(*point, cluster);
    }
}

void heapNTree::insert_cluster(cluster * inserted_cluster) {
    for (heapNTree::iterator cluster = heap->begin(); cluster != heap->end(); cluster++) {
        if ( inserted_cluster->distance_closest < (*cluster)->distance_closest ) {
            heap->insert(cluster, inserted_cluster);
            return;
        }
    }
    
    heap->push_back(inserted_cluster);
}



void Node::splitNode(cluster *parentClusterA,cluster *parentClusterB){
//    Node* nodeA = new Node();
    Node* nodeB = new Node();
    list<cluster*>::iterator itr = this->cList.begin();
    list<cluster*>::iterator tempItr;
//    list<cluster*>::iterator itrClst;
//   for (int c = 0; c < 2 ; c++){
//       if(c == 0)
//            nodeA->cList.push_back(*itr);
//        else
//            nodeB->cList.push_back(*itr);
//        for(int i = 1; i < (MAX_CAP+1)/2; i++){
//            if(c == 0)
//                nodeA->cList.push_back((*itr)->closest);
//            else
    nodeB->cList.push_back(*itr);
    nodeB->cList.push_back((*itr)->closest);
//    if((*itr)->closest->closest != *itr){
        (*itr)->closest->closest = (*itr);
        (*itr)->closest->distance_closest = get_distancelol((*itr)->closest, *itr);
//    }
    
    remerge((*itr), (*itr)->closest, parentClusterB);
    parentClusterB->childPtr = nodeB;
    nodeB->leaf = this->leaf;
    nodeB->timestamp = this->timestamp;
    
//    parentClusterB = mergedCluster;
//            itrClst = itr;
//            while(!(*itrClst == (*itr)->closest)){
//                itrClst++;
//                if(itrClst == cList.end()){
//                    cout<<"closest not found" <<endl;
//                }
//            }
    cList.remove((*itr)->closest);
    cList.remove(*itr);
//            cList.remove(*itrClst);
//    itr = cList.begin();
//        }
//        if(c == 0)
    itr = cList.begin();
    tempItr = cList.begin();
    tempItr++;
    remerge((*itr), *(tempItr), parentClusterA);
//    if((*tempItr)->closest != *itr){
        (*tempItr)->closest = (*itr);
        (*tempItr)->distance_closest = get_distancelol(*tempItr, *itr);
//    }
//    if((*itr)->closest != *tempItr){
        (*itr)->closest = (*tempItr);
        (*itr)->distance_closest = (*tempItr)->distance_closest;
//    }
    
    parentClusterA->childPtr = this;
//    parentClusterA = mergedCluster;
//        else
//            parentClusterB = *itr;
//        cList.remove(*itr);
//        itr = cList.begin();
    if(cList.size() != 2){
        cout<< "split failed. size:"<< cList.size()<<":"<< nodeB->cList.size()<<endl;
        
          
    }
//        Node result[2];
//        result[0] = nodeA;
//        result[1] = nodeB;
//        return result;
//    }
}

                             
