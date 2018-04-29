
//
//  main.cpp
//  agloClusTree
//
//  Created by Abhishek Singh on 21/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved.
//

#include <iostream>
#include<queue>
#include<ctime>
#include "hoogaBugaa.hpp"
#include "kdtree.hpp"
//#include "utils.hpp"
//#include "cure_data.hpp"
#include "utility.hpp"
#include "clusTree.hpp"
#include <fstream>
#define RADIUS 2.0
#define ALPHA 1.0
//#define TEST 1.0
//#define DEBUG 0
void createStream();
void streamInfinitely(std::vector<streamingPoint> * stream);

int isMuCluster = 1;
Node* clustreeRoot = nullptr;
//std::vector<streamingPoint> * stream;
int clusterIdentity = 0;

void copy(heapNTree* thisOne, const heapNTree* src)

{
    
    
    for(std::list<cluster*>:: iterator it = src->heap->begin(); it != src->heap->end(); it++)
    {
        (thisOne->heap)->push_back(*it);
        
        
    }
    
    //debug
    
    // this may need a copy consyructor as well
    //thisOne->tree = src.tree;
    
    thisOne->tree->root =src->tree->root;
    thisOne->tree->dimension =  src->tree->dimension;
}


void printTreeBFTree(Node* root)
{
    cout<<"PRINTING TREE"<<endl;
    std::queue<cluster* >queue;
    size_t level = 0;
    size_t currentLen= 0;
    size_t previousLen = 0;
    
    //ofstream myfile ("/Users/abhisheksingh/Desktop/ADM ASSIGNMENT /runTests/bcTree/bcTree/resultTree.txt");
    ofstream resultFile("/Users/abhisheksingh/Desktop/ADM ASSIGNMENT /runTests/bcTree/bcTree/domVectorsTreefull.txt");
    
    
    
    
    if(root == nullptr)
    {
        cout<<"NULLED"<<endl;
    }
    
    //cout<<(*(root->cList.begin()))->mean->data()[0]<<endl;
    
    //cout<<" ^^^^^^^^^^^ROOT NODE HAS "<<root->cList.size()<<" CLUSTERS ^^^^^^^^^^^"<<endl;
    
   // myfile <<" ^^^^^^^^^^^ROOT NODE HAS "<<root->cList.size()<<" CLUSTERS ^^^^^^^^^^^\n";
   //currentLen = root->cList.size();
    previousLen = root->cList.size();
    for(std::list<cluster*>:: iterator it = root->cList.begin(); it != root->cList.end(); it++)
    {
        queue.push(*it);
    }
    if(queue.empty())
    {
        cout<<" NO TREE FORMED "<<endl;
      //  myfile<<" NO TREE FORMED \n";

    }
    
    
    while(!queue.empty())
    {
        //cout<<" I AM HERE "<<endl;
        cluster* clusterFront =  queue.front();
        queue.pop();
        previousLen -= 1;
        
        
//        cout<<"-C-"<<(clusterFront->dom_vector)[1]<< " " <<(clusterFront->dom_vector)[2]<<" "<<(clusterFront->dom_vector)[3]<<" "<<(clusterFront->dom_vector)[4]<<" "<<(clusterFront->dom_vector)[5]<<" "<<(clusterFront->dom_vector)[6]<<" "<<(clusterFront->dom_vector)[7]<<"---"<<endl;
//        
//        cout<<"-B-"<<(clusterFront->buff->dom_buff_vector)[1]<< " " <<(clusterFront->buff->dom_buff_vector)[2]<<" "<<(clusterFront->buff->dom_buff_vector)[3]<<" "<<(clusterFront->buff->dom_buff_vector)[4]<<" "<<(clusterFront->buff->dom_buff_vector)[5]<<" "<<(clusterFront->buff->dom_buff_vector)[6]<<" "<<(clusterFront->buff->dom_buff_vector)[7]<<"---"<<endl;
//        //cout<<" "<<clusterFront->mean->data()[0]<<" "<<clusterFront->mean->data()[1]<<endl;
      // cout<<endl;
      //  myfile<<"\n";

       // cout<<" *******************NEW MICRO-CLUSTERS ******************"<<endl;
       // myfile<<" *******************NEW MICRO-CLUSTERS ******************\n";
        
        //cout<< " MEAN OF THE MICRO CLUSTER "<<"["<<clusterFront->mean->data()[0]<<", "<<clusterFront->mean->data()[1]<<"]"<<endl;
       // myfile<< " MEAN OF THE MICRO CLUSTER "<<"["<<clusterFront->mean->data()[0]<<","<<clusterFront->mean->data()[1]<<","<<clusterFront->mean->data()[2]<<","<<clusterFront->mean->data()[3]<<","<<clusterFront->mean->data()[4]<<","<<clusterFront->mean->data()[5]<<","<<clusterFront->mean->data()[6]<<","<<clusterFront->mean->data()[7]<<","<<clusterFront->mean->data()[8]<<","<<clusterFront->mean->data()[9]<<"]\n";

       // cout<< " CLUSTER I;D  "<<clusterFront->clusID<<endl;
       // myfile<< " CLUSTER ID  "<<clusterFront->clusID<<"\n";

        
        //cout<<" POINTS OF THIS MICROCLUSTER "<<endl;
//        myfile<<" POINTS OF THIS MICROCLUSTER \n";
//        for(std::vector<vector<double>* >::iterator iter =  clusterFront->points->begin();  iter != clusterFront->points->end(); iter++)
//        {
//            //cout<<" I AM HERE TOO"<<endl;
//           
//            cout<<"("<<(*iter)->data()[0]<<","<<(*iter)->data()[1]<<")"<<endl;        }
//        
//       // cout<<"REP POINTS OF THE MICRO-CLUSTERS"<<endl;
        //myfile<<"REP POINTS OF THE MICRO-CLUSTERS \n";

        
//        for(std::vector<vector<double>* >::iterator iter = clusterFront->repPoints->begin(); iter != clusterFront->repPoints->end(); iter++)
//        {
//            
//            
//          //  cout<<"("<<(*iter)->data()[0]<<","<<(*iter)->data()[1]<<")"<<endl;
//            myfile<<"("<<(*iter)->data()[0]<<","<<(*iter)->data()[1]<<")\n" ;
//        }
        
       // cout<<" DOMINANCE ARRAY OF THE CLUSTER "<<endl;
       // myfile<<" DOMINANCE ARRAY OF THE CLUSTER \n" ;
        
        
       // myfile<<"C";
        resultFile<<"C";
        for(int i = 1; i < CLASSES; i++)
        {
           // cout<<" "<<(clusterFront->dom_vector)[i]<<" ";
           // myfile<<" "<<(clusterFront->dom_vector)[i]<<" ";
            resultFile<<" "<<(clusterFront->dom_vector)[i]<<" ";
            

            
        }
        //resultFile<<"\n";
        
        
        if(clusterFront->buff->numPoints > 0)
        {
            resultFile<<"\n";
            //myfile<<"B";
            resultFile<<"B";
            for(int i = 1; i < CLASSES; i++)
            {
                
                //cout<<" BBBBBBBBBBBBBBBBBBBBBBBB "<<(clusterFront->buff->dom_buff_vector)[i]<<" ";
               // myfile<<" "<<(clusterFront->buff->dom_buff_vector)[i]<<" ";
                resultFile<<" "<<(clusterFront->buff->dom_buff_vector)[i]<<" ";
                
                
                
            }

        }
       // cout<<endl;
       // myfile<<"\n";
        resultFile<<"\n";

       // cout<<":"<<clusterFront->mean->data()[0]<<" CLOSEST " <<clusterFront->closest->mean->data()[0]<<endl;
        if(clusterFront->childPtr != nullptr){
            for(std::list<cluster*>:: iterator it1 = clusterFront->childPtr->cList.begin(); it1 !=clusterFront->childPtr->cList.end(); it1++)
            {
                               // cout<< " PUSHING " << (*it1)->mean->data()[0]<<endl;
                //cout<<" NEXT LEVEL "<<endl;
                
                queue.push(*it1);
                currentLen += 1;
                
               

            }
            if( previousLen == 0)
            {
                level++;
               // cout<<endl;
               // myfile<<"\n";
               // cout<<" @@@@@@@@@@@@@@@ NEW LEVEL ::"<<level<<"@@@@@@@@@@@@@"<<endl;
                //myfile<<" @@@@@@@@@@@@@@@ NEW LEVEL ::"<<level<<"@@@@@@@@@@@@@ \n";
                resultFile<<"\n";
                resultFile<<"\n";
                previousLen = currentLen;
                currentLen = 0;
            }
            //queue.push(dummy);
        }
    }
    
    
   // myfile.close();
    cout<<" LEVEL OF THE OFFLINE TREE IS "<<level<<endl;
    resultFile.close();
}

void printTreeBFStream(Node* root)
{
   // cout<<"PRINTING TREE"<<endl;
    std::queue<cluster* >queue;
    size_t level = 0;
    size_t currentLen= 0;
    size_t previousLen = 0;
    
    //ofstream myfile ("/Users/abhisheksingh/Desktop/ADM ASSIGNMENT /runTests/bcTree/bcTree/resultStream.txt");
    ofstream resultFile("/Users/abhisheksingh/Desktop/ADM ASSIGNMENT /runTests/bcTree/bcTree/domVectorsStreamFull.txt");
    
    
    
    
    if(root == nullptr)
    {
        cout<<"NULLED"<<endl;
    }
    
    //cout<<(*(root->cList.begin()))->mean->data()[0]<<endl;
    
    //cout<<" ^^^^^^^^^^^ROOT NODE HAS "<<root->cList.size()<<" CLUSTERS ^^^^^^^^^^^"<<endl;
    
   // myfile <<" ^^^^^^^^^^^ROOT NODE HAS "<<root->cList.size()<<" CLUSTERS ^^^^^^^^^^^\n";
    //    currentLen = root->cList.size();
    previousLen = root->cList.size();
    for(std::list<cluster*>:: iterator it = root->cList.begin(); it != root->cList.end(); it++)
    {
        queue.push(*it);
    }
    if(queue.empty())
    {
        cout<<" NO TREE FORMED "<<endl;
       // myfile<<" NO TREE FORMED \n";
        
    }
    
    
    while(!queue.empty())
    {
        //cout<<" I AM HERE "<<endl;
        cluster* clusterFront =  queue.front();
        queue.pop();
        previousLen -= 1;
        
        //cout<<" "<<clusterFront->mean->data()[0]<<" "<<clusterFront->mean->data()[1]<<endl;
       // cout<<endl;
        //myfile<<"\n";
        
        //cout<<" *******************NEW MICRO-CLUSTERS ******************"<<endl;
       // myfile<<" *******************NEW MICRO-CLUSTERS ******************\n";
        
       // cout<< " MEAN OF THE MICRO CLUSTER "<<"["<<clusterFront->mean->data()[0]<<", "<<clusterFront->mean->data()[1]<<"]"<<endl;
       // myfile<< " MEAN OF THE MICRO CLUSTER "<<"["<<clusterFront->mean->data()[0]<<", "<<clusterFront->mean->data()[1]<<"]\n";
        
//        cout<< " CLUSTER ID  "<<clusterFront->clusID<<endl;
       // myfile<< " CLUSTER ID  "<<clusterFront->clusID<<"\n";
        
        
//        cout<<" POINTS OF THIS MICROCLUSTER "<<endl;
       // myfile<<" POINTS OF THIS MICROCLUSTER \n";
//        for(std::vector<vector<double>* >::iterator iter =  clusterFront->points->begin();  iter != clusterFront->points->end(); iter++)
//        {
//            //cout<<" I AM HERE TOO"<<endl;
//            
//            cout<<"("<<(*iter)->data()[0]<<","<<(*iter)->data()[1]<<")"<<endl;        }
//        
//        cout<<"REP POINTS OF THE MICRO-CLUSTERS"<<endl;
//       // myfile<<"REP POINTS OF THE MICRO-CLUSTERS \n";
//        
//        
//        for(std::vector<vector<double>* >::iterator iter = clusterFront->repPoints->begin(); iter != clusterFront->repPoints->end(); iter++)
//        {
//            
//            
//            cout<<"("<<(*iter)->data()[0]<<","<<(*iter)->data()[1]<<")"<<endl;
//         //   myfile<<"("<<(*iter)->data()[0]<<","<<(*iter)->data()[1]<<")\n" ;
//        }
//        
       // cout<<" DOMINANCE ARRAY OF THE CLUSTER "<<endl;
       // myfile<<" DOMINANCE ARRAY OF THE CLUSTER \n" ;
        
        
      //  myfile<<"C";
        resultFile<<"C";
        for(int i = 1; i < CLASSES; i++)
        {
           // cout<<" "<<(clusterFront->dom_vector)[i]<<" ";
          //  myfile<<" "<<(clusterFront->dom_vector)[i]<<" ";
            resultFile<<" "<<(clusterFront->dom_vector)[i]<<" ";
            
            
            
        }
        //resultFile<<"\n";
        
        
        if(clusterFront->buff->numPoints > 0)
        {
            resultFile<<"\n";
         //   myfile<<"B";
            resultFile<<"B";
            for(int i = 1; i < CLASSES; i++)
            {
                
               // cout<<" BBBBBBBBBBBBBBBBBBBBBBBB "<<(clusterFront->buff->dom_buff_vector)[i]<<" ";
              //  myfile<<" "<<(clusterFront->buff->dom_buff_vector)[i]<<" ";
                resultFile<<" "<<(clusterFront->buff->dom_buff_vector)[i]<<" ";
                
                
                
            }
            
        }
       // cout<<endl;
       // myfile<<"\n";
        resultFile<<"\n";
        
        // cout<<":"<<clusterFront->mean->data()[0]<<" CLOSEST " <<clusterFront->closest->mean->data()[0]<<endl;
        if(clusterFront->childPtr != nullptr){
            for(std::list<cluster*>:: iterator it1 = clusterFront->childPtr->cList.begin(); it1 !=clusterFront->childPtr->cList.end(); it1++)
            {
                // cout<< " PUSHING " << (*it1)->mean->data()[0]<<endl;
                //cout<<" NEXT LEVEL "<<endl;
                
                queue.push(*it1);
                currentLen += 1;
                
                
                
            }
            if( previousLen == 0)
            {
                level++;
                cout<<endl;
              //  myfile<<"\n";
               // cout<<" @@@@@@@@@@@@@@@ NEW LEVEL ::"<<level<<"@@@@@@@@@@@@@"<<endl;
              //  myfile<<" @@@@@@@@@@@@@@@ NEW LEVEL ::"<<level<<"@@@@@@@@@@@@@ \n";
                resultFile<<"\n";
                resultFile<<"\n";
                previousLen = currentLen;
                currentLen = 0;
            }
            //queue.push(dummy);
        }
    }
    
    
   // myfile.close();
    cout<<" LEVEL OF THE TREE AFTER STREAMING IS "<<level<<endl;
    resultFile.close();
}




void mergeNUpdate(heapNTree* tempQ, cluster* cluster1, cluster* cluster2, cluster* mergedCluster){
    cluster* nearest_cluster = nullptr;
    
    
    tempQ->remove_representative_points(cluster1);
    tempQ->remove_representative_points(cluster2);
    
    // std::cout<<"********MERGING********** "<<mergedCluster->mean->data()[0]<<endl;;
    //std::cout<<"MERGE AND UPDATE BEFORE REMOVING "<<cluster1->mean->data()[0]<<" "<<cluster2->mean->data()[0]<< " Size "<<tempQ->size()<<endl;
    
    
    (tempQ->heap)->remove(cluster1);
    (tempQ->heap)->remove(cluster2);
    
    // std::cout<<"MERGE AND UPDATE AFTER REMOVING C1 AND C2 "<<tempQ->size()<<endl;
    
    tempQ->insert_representative_points(mergedCluster);
    
    
    //tempQ->insert_cluster(mergedCluster);
    
    
    std::list<cluster *> * relocation_request = nullptr;
    
    //update the closest
    if ((tempQ->heap)->size() > 0) {
        mergedCluster->closest = *((tempQ->heap)->begin());
        mergedCluster->distance_closest = tempQ->get_distance(mergedCluster, mergedCluster->closest);
        
        
        /* relocation request */
        relocation_request = new std::list<cluster *>();
        
        for (heapNTree::iterator iterCluster = (tempQ->heap)->begin(); iterCluster != (tempQ->heap)->end(); iterCluster++) {
            double distance = tempQ->get_distance(mergedCluster, *iterCluster);
            
            /* Check if distance between new cluster and current is the best than now. */
            if (distance < (mergedCluster->distance_closest)) {
                mergedCluster->closest = *iterCluster;
                mergedCluster->distance_closest = distance;
            }
            
            /* Check if current cluster has removed neighbor. */
            if ( ((*iterCluster)->closest == cluster1) || ((*iterCluster)->closest == cluster2) ) {
                /* If previous distance was less then distance to new cluster then nearest cluster should be found in the tree. */
                if (((*iterCluster)->distance_closest) < distance) {
                    
                    nearest_cluster = nullptr;
                    double nearest_distance = std::numeric_limits<double>::max();
                    
                    for (std::vector<std::vector<double> * >::iterator point = (*iterCluster)->repPoints->begin(); point != (*iterCluster)->repPoints->end(); point++) {
                        container::kdtree_searcher searcher(*point, (tempQ->tree)->get_root(), distance);
                        
                        std::vector<double> * nearest_node_distances = new std::vector<double>();
                        std::vector<container::kdnode *> * nearest_nodes = searcher.find_nearest_nodes(nearest_node_distances);
                        
                        for (unsigned int index = 0; index < nearest_nodes->size(); index++) {
                            //cout<<"%%%%%%% NEAREST DISTANCES %%%%%%%% "<<(*nearest_node_distances)[index]<<endl;;
                            
                            if ( ((*nearest_node_distances)[index] < nearest_distance) && ( (*nearest_nodes)[index]->get_payload() != (*iterCluster) ) ) {
                                //nearest_distance = (*nearest_node_distances)[index];
                                
                                
                                nearest_cluster = (cluster*)(*nearest_nodes)[index]->get_payload();
                                nearest_distance = tempQ->get_distance((*iterCluster), nearest_cluster);
                                // cout<<" ////////HERE 1 "<<(*iterCluster)->mean->data()[0]<<"Value "<<nearest_distance<<endl;
                                //cout<<"CLOSEST POINT "<<nearest_cluster->mean->data()[0];
                            }
                        }
                        
                        delete nearest_nodes;
                        delete nearest_node_distances;
                    }
                    
                    if (nearest_cluster == nullptr) {
                        //cout<<" HERE 2 "<<(*iterCluster)->mean->data()[0]<<endl;
                        (*iterCluster)->closest = mergedCluster;
                        (*iterCluster)->distance_closest = distance;
                    }
                    else {
                        
                        (*iterCluster)->closest = nearest_cluster;
                        (*iterCluster)->distance_closest = nearest_distance;
                        // cout<<" /////////HERE 3 "<<(*iterCluster)->mean->data()[0]<<"Value "<<(*iterCluster)->distance_closest<<endl;
                        //cout<<"CLOSEST POINT "<<nearest_cluster->mean->data()[0];
                        
                    }
                }
                else {
                    // cout<<"HERE  "<<endl;
                    (*iterCluster)->closest = mergedCluster;
                    (*iterCluster)->distance_closest = distance;
                }
                
                relocation_request->push_back((*iterCluster));
                
                
            }
        }
    }
    
    // delete cluster1;
    //cluster1 = nullptr;
    //delete cluster2;
    // cluster2 = nullptr;
    //    std::cout<<" MERGE AND UPDATE before ADDING C1C2 "<<mergedCluster->mean->data()[0] <<endl;
    //    std::cout<<"&&&&&&&&&& THE TEMPQ CONDTION &&&&&&&&&&"<<endl;
    //    for(std::list<cluster*>:: iterator it = tempQ->heap->begin(); it != tempQ->heap->end(); it++)
    //    {
    //
    //        if((*it)->mean != nullptr)
    //            cout<<":"<<(*it)->mean->data()[0]<<":"<<endl;
    //        else
    //            cout<<"NULLED  "<<endl;
    //
    //    }
    
    /* insert merged cluster */
    
    //std::cout<<" MERGE AND UPDATE AFTER ADDING C1C2 "<<mergedCluster->mean->data()[0] <<endl;
    //    std::cout<<"########### THE TEMPQ CONDTION ##########"<<endl;
    //    for(std::list<cluster*>:: iterator it = tempQ->heap->begin(); it != tempQ->heap->end(); it++)
    //    {
    //
    //        if((*it)->mean != nullptr)
    //            cout<<":"<<(*it)->mean->data()[0]<<":"<<" nearest Point "<<(*it)->closest->mean->data()[0]<<" Dist "<< (*it)->distance_closest<<endl;
    //        else
    //            cout<<"NULLED  "<<endl;
    //
    //    }
    
    
    tempQ->insert_cluster(mergedCluster);
    
    //cout<<"MERGED CLUSTER INSERTED "<< (*mergedCluster).mean->data()[0]<<endl;
    
    if (relocation_request != nullptr) {
        for (heapNTree::iterator cluster = relocation_request->begin(); cluster != relocation_request->end(); cluster++) {
            tempQ->remove_cluster(*cluster);
            tempQ->insert_cluster(*cluster);
        }
        
        delete relocation_request;
        relocation_request = nullptr;
        
    }
    
}

void transferNUpdate(cluster* unmergable,heapNTree* from, heapNTree* to){
    //CHANGES IN THE OLD heapNTree
    // ASSUMED THAT THE CLUSTER HAS NOT BEEN DELETED FROM THE heap AND THE repPoints have been deleted from the
    //kDTree
    
    //removing the unmergable from the "from" heap
    from->remove_cluster(unmergable);
    from->remove_representative_points(unmergable);
    std::list<cluster *> * relocation_request1 = nullptr;
   if((from->heap)->size() >1){
        relocation_request1 = new std::list<cluster *>();
       
        for(heapNTree:: iterator iter1  = (from->heap)->begin(); iter1 != (from->heap)->end(); iter1++){
            if((*iter1)->closest == unmergable){
                //cout<<" POINTEEEEE "<<"("<<(*iter1)->mean->data()[0]<<","<<((*iter1)->mean->data())[1]<<")"<<endl;
                if((iter1) == from->heap->begin())
                {
                    heapNTree:: iterator iterw = ++iter1;
                    
                    iter1--;
                  //  cout<<"&&&&&&&&&&&&&&&& ITER1 HAI &&&&&&&&&&& "<<"("<<(*iter1)->mean->data()[0]<<","<<((*iter1)->mean->data())[1]<<")"<<endl;
                   // cout<<"&&&&&&&&&&&&&&&&  ITERW HAI &&&&&&&&&&&"<<"("<<(*iterw)->mean->data()[0]<<","<<((*iterw)->mean->data())[1]<<")"<<endl;
                    
                    (*iter1)->closest = (*iterw);
                    //cout<<"CLOSEST INTIAL "<<"("<<(*iter1)->mean->data()[0]<<","<<((*iter1)->mean->data())[1]<<")"<<endl;
                    (*iter1)->distance_closest = from->get_distance(*iter1,  (*iter1)->closest);
                   // cout<<"&&&&&&&&&&&&&& DISTANCE "<<(*iter1)->distance_closest<<endl;
                    
                }
                else
                {
                    (*iter1)->closest = *((from->heap)->begin());
                    (*iter1)->distance_closest = from->get_distance(*iter1,  (*iter1)->closest);
                }
                double distance = (*iter1)->distance_closest;
                
                cluster* nearest_cluster = nullptr;
                double nearest_distance = std::numeric_limits<double>::max();
                for (std::vector<std::vector<double> * >::iterator point = (*iter1)->repPoints->begin(); point != (*iter1)->repPoints->end(); point++)
                {
                    container::kdtree_searcher searcher(*point, from->tree->get_root(), distance);
                    
                    std::vector<double> * nearest_node_distances = new std::vector<double>();
                    
                    std::vector<container:: kdnode *> * nearest_nodes = searcher.find_nearest_nodes(nearest_node_distances);
                    
                    for (unsigned int index = 0; index < nearest_nodes->size(); index++) {
                        if ( ((*nearest_node_distances)[index] < nearest_distance) && ( (*nearest_nodes)[index]->get_payload() != (*iter1) ) ) {
                            //cout<<"%%%%%%% NEAREST DISTANCES %%%%%%%% "<<(*nearest_node_distances)[index]<<endl;
                            //nearest_distance = (*nearest_node_distances)[index];
                            nearest_cluster = (cluster *) (*nearest_nodes)[index]->get_payload();
                            nearest_distance = from->get_distance((*iter1), nearest_cluster);
                            //cout<<"%%%%%%%%%%% NEAREST  "<<nearest_distance<<endl;
                        }
                    }
                    
                    delete nearest_nodes;
                    delete nearest_node_distances;
                }
                if(nearest_cluster == nullptr)
                {
                    int run = 0;
                    cluster* cl = (*iter1);
                    double minDistance = numeric_limits<double>::max();
                    double distance ;
                    //cout<<" SIZE OF FROM HEAP IS "<<from->heap->size()<<endl;
                      for(heapNTree:: iterator iterNew = (from->heap)->begin(); iterNew != (from->heap)->end(); iterNew++)
                      {
                          //cout<<" RUN "<<++run<<endl;
                          //cout<<" ELEMENTS OF FROM "<<"("<<(*iterNew)->mean->data()[0]<<","<<(*iterNew)->mean->data()[1]<<")"<<endl;
                          if((*iter1) != (*iterNew)){
                          distance = get_distance(cl, (*iterNew));
                          if(distance < minDistance)
                          {
                              (*iter1)->closest = (*iterNew);
                              (*iter1)->distance_closest = distance;
                              minDistance = distance;
                          }
                          }
                      }
                    // cout<<"&&&&&&&&&&&&&&&& END MEIN  &&&&&&&&&&& "<<endl;
                    // cout<<"&&&&&&&&&&&&&&&& ITER1 HAI &&&&&&&&&&& "<<"("<<(*iter1)->mean->data()[0]<<","<<((*iter1)->mean->data())[1]<<")"<<endl;
                    //cout<<"&&&&&&&&&&&&&&&& CLOSEST HAI &&&&&&&&& "<<"("<<(*iter1)->closest->mean->data()[0]<<","<<(*iter1)->closest->mean->data()[1]<<")"<<endl;

                    //changed from here
//                    if((iter1) == from->heap->begin())
//                    {
//                        cout<<"&&&&&&&&&&&&&&&& END MEIN  &&&&&&&&&&& "<<"("<<(*((from->heap)->end()))->mean->data()[0]<<","<<(*((from->heap)->end()))->mean->data()[1]<<endl;
//
//                        (*iter1)->closest = *((from->heap)->end());
//                        (*iter1)->distance_closest = distance;
//                    }
//                    else
//                    {
//                        (*iter1)->closest = *((from->heap)->begin());
//                        (*iter1)->distance_closest = distance;
//                    }
//                    //chamged till here
                    
                }
                else
                {
                    (*iter1)->closest = nearest_cluster;
                    (*iter1)->distance_closest = nearest_distance;
                }
                
                relocation_request1 ->push_back((*iter1));
                
            }
//            cout<<" LOOKING   "<<"("<<(*iter1)->mean->data()[0]<<","<<((*iter1)->mean->data())[1]<<")"<<endl;
//            if((*iter1)->closest != NULL)
//            cout<<" FOUND     "<<"("<<(*iter1)->closest->mean->data()[0]<<","<<(*iter1)->closest->mean->data()[1]<<")"<<endl;
//            else if((*iter1)->closest == NULL)
//                cout<<"NULL CLOSEST HAI"<<endl;

        }
       
       
    }
    else if((from->heap)->size() == 1)
    {
        heapNTree:: iterator iterx  = (from->heap)->begin();
        (*iterx)->closest = nullptr;
        (*iterx)->distance_closest = std::numeric_limits<double>::max();
        
    }
    
    
    
    
    
    //insert all the relocation requests
    if(relocation_request1 != nullptr){
        for(std::list<cluster*>::iterator iter1 = relocation_request1->begin(); iter1 != relocation_request1->end(); iter1++){
            from->remove_cluster(*iter1);
            from->insert_cluster(*iter1);
            
        }
    }
    
    
    
    
    std::list<cluster *> * relocation_request = nullptr;
    
    //CHANGES IN THE NEW heapNTree
    //ASSUMED THAT THE CLUSTER HAS NOT BEEN ADDED AND KDTREE IS NOT INSERTED
    
        if((to->heap)->size() > 0){
        relocation_request = new std::list<cluster *>();
        
        
        unmergable->closest = *(to->heap->begin());
        
        
        
        unmergable->distance_closest = to->get_distance(unmergable,unmergable->closest);
        
        
        /*relocation requests of other clusters */
        
        
        for(heapNTree:: iterator iter1 = (to->heap)->begin(); iter1 != (to->heap)->end(); iter1++){
            double distance = to->get_distance(unmergable,*iter1);
            
            /*check if the distance between the new cluster and current better than previous*/
            if(distance < unmergable->distance_closest){
                unmergable->closest = *iter1;
                unmergable->distance_closest = distance;
            }
            //if others are closest to the newly entering cluster
            if((*iter1)->distance_closest >= distance)
            {
                
                (*iter1)->closest = unmergable;
                (*iter1)->distance_closest = distance;
                //these clusters will now need to be adjusted in the queue
                relocation_request->push_back((*iter1));
                
            }
        }
        
        //insert the unmerged to it's place
        to->insert_cluster(unmergable);
        
        
        //std::cout<<"TRANSFER AND UPDATE AFTER ADDING 'TO'(1)  "<<to->size()<<endl;
        //insert all the relocation requests
        if(relocation_request != nullptr){
            for(std::list<cluster*>::iterator iter2 = relocation_request->begin(); iter2 != relocation_request->end();  iter2++){
                to->remove_cluster(*iter2);
                to->insert_cluster(*iter2);
            }
        }
        
        //updating the kDTree as well
        to->insert_representative_points(unmergable);
    }
    
    
    else
    {
        unmergable->closest = nullptr;
        unmergable->distance_closest = std::numeric_limits<double>::max();
        to->heap->push_back(unmergable);
        //std::cout<<"TRANSFER AND UPDATE AFTER ADDING 'TO'(2) "<<to->size()<<endl;
        
    }
//        cout<<"@@@@@@@@@@ FROM AND ITS CLOSEST @@@@@@@@@"<<from->size()<<endl;
//        for(std::list<cluster*>:: iterator it = from->heap->begin(); it != from->heap->end(); it++)
//        {
//            //cout<<" TO UPDATE(2) "<<endl;
//           if((*it)->mean != nullptr)
//                cout<<"("<<(*it)->mean->data()[0]<<","<<((*it)->mean->data())[1]<<")"<<endl;
//            else if((*it)->mean == nullptr)
//                cout<<"NULLED (1)"<<endl;
//            if((*it)->closest != nullptr)
//               cout<<" CLOSEST :: ("<<((*it)->closest->mean->data())[0]<<","<<((*it)->closest->mean->data())[1]<<")"<<endl;
//            else if((*it)->closest  == nullptr)
//                cout<< " CLOSEST IS  NULL "<<endl;
//        }
//    
//    
//    cout<<" @@@@@@@@@@@ TO AND ITS CLOSEST @@@@@@@@@@ "<<to->size()<<endl;
//    for(std::list<cluster*>:: iterator it = to->heap->begin(); it != to->heap->end(); it++)
//    {
//        //cout<<" TO UPDATE(2) "<<endl;
//        if((*it)->mean != nullptr)
//            cout<<"("<<(*it)->mean->data()[0]<<","<<((*it)->mean->data())[1]<<")";
//        else if((*it)->mean == nullptr)
//            cout<<"NULLED (1)"<<endl;
//        if((*it)->closest  != nullptr)
//            cout<<" CLOSEST :: ("<<((*it)->closest->mean->data())[0]<<","<<((*it)->closest->mean->data())[1]<<")"<<endl;
//        else if((*it)->closest == nullptr)
//            cout<< " CLOSEST IS  NULL "<<endl;
//    }
    
    unmergable->modCount = 0;
}

//this recalculates all neighbor relations in a node
void settleNeighbors(Node *currentNode){
    for(std::list<cluster*>::iterator itr1 = currentNode->begin(); itr1!= currentNode->end(); itr1++){
        double minDistance = std::numeric_limits<double>::max();
        double distance;
        for(std::list<cluster*>::iterator itr2 = currentNode->begin(); itr2!= currentNode->end(); itr2++){
            if(*itr1 != *itr2){
                distance = get_distance(*itr1, *itr2);
                if(distance < minDistance){
                    (*itr1)->distance_closest = distance;
                    (*itr1)->closest = *itr2;
                }
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    
    clock_t begin = clock();
    
    double startTime = double(begin)/CLOCKS_PER_SEC;
    
    cout<< " ~~~~~~~~~~~~~~~~ START TIME ~~~~~~~~~~~~~~~~~~~~~~~~ "<<startTime<<endl;
    
    
    
    std::vector<long> *class_vector = new vector<long>;
    
    std::vector<vector<double> >* p_data = read_sample_training("/Users/abhisheksingh/Desktop/ADM ASSIGNMENT /runTests/bcTree/bcTree/trainingData60.txt", class_vector);
    
    
    
    //empty heap and tree to store q
    heapNTree* q = new heapNTree();
    
    //create a heap and KD TREE based on the points of the data
    heapNTree* tempQ =  new heapNTree(p_data,class_vector);
    
    
    
    
    
    
    
    size_t number_points =(REPR_COUNT) > (tempQ->getMinHeap()->points->size())? (tempQ->getMinHeap()->points->size()) : REPR_COUNT ;
//    cout<<" RACHECK SIZE "<<number_points<<endl;
//    cout<<" tempQ size "<<tempQ->size()<<endl;
    while((tempQ->heap->size()) > 1){
        
        /*
         cout<<" OUTSIDE  "<<endl;
         for(std::list<cluster*>:: iterator it = q->heap->begin(); it != q->heap->end(); it++)
         {
         cout<<" TO UPDATE(O) "<<endl;
         if((*it)->mean != nullptr)
         cout<<":"<<(*it)->mean->data()[0]<<":"<<endl;
         else
         cout<<"NULLED (1)"<<endl;
         
         }
         */
        
        
        cluster*  cluster1 = *(tempQ->heap->begin());
        cluster*  cluster2 = cluster1->closest;
        
//        cout<<" FORMING MICRO-CLUSTERS "<<endl;
        
        
        cluster* mergedCluster =  new cluster();
        //cout<<"MERGING "<<":"<<cluster1->mean->data()[0]<<":"<<cluster2->mean->data()[0];
        
        long numberPoints;
        numberPoints = cluster1->points->size() + cluster2->points->size();
        number_points = (REPR_COUNT) > numberPoints ? numberPoints : REPR_COUNT ;
        //cout<<" SIZE "<<number_points<<endl;
        tempQ->merge(cluster1, cluster2, mergedCluster, number_points, ALPHA);
        //cout<<"MERGED "<<":"<<mergedCluster->mean->data()[0]<<" RADIUS "<< mergedCluster->radius << endl;
        
        //result collection
        
//        cluster1->clusID = clusterIdentity;
//        cluster2->clusID = clusterIdentity;
//        mergedCluster->clusID = clusterIdentity;
        
        if((mergedCluster->radius) <=  RADIUS){
            
            mergeNUpdate(tempQ, cluster1,  cluster2, mergedCluster);
            
            
        }
        else {
            //cout<<" INSERTING ********* "<<(*cluster1).mean->data()[0]<<endl;
            clusterIdentity += 1;
            transferNUpdate(cluster1,tempQ, q);
            // delete cluster1; cluster1 = nullptr;
        }
    
    }
    //q->insert_cluster(*(tempQ->heap->begin()));
    //cout<<" THE LAST ONE "<<(*(tempQ->heap->begin()))->mean->data()[0]<<endl;
    transferNUpdate(*(tempQ->heap->begin()), tempQ, q);
    //q->tree = tempQ->tree;
    cluster* firstClus =(*(tempQ->heap->begin()));
    tempQ->remove_cluster(firstClus);
    
    
    
    
    //iteratively build up the tree
    cluster *x, *y, *xy;
    heapNTree *swapQ;
    
    //swap once
    swapQ = tempQ;
    
    tempQ = q;
    
    q = swapQ;
    
    while(tempQ->size() > 1){
        
//        cout<<"FORMING TREE"<<endl;
        swapQ = tempQ;
        
        tempQ = q;
        
        q = swapQ;
        
        while(q->size() != 1){
//            cout<<"FORMING TREE1"<<endl;

            x = q->getMinHeap();
            y = (*x).closest;
            size_t reprCount = (*x).repPoints->size()+(*y).repPoints->size();
            reprCount = reprCount < REPR_COUNT? reprCount : REPR_COUNT;
            if(x->modCount + y->modCount < 2){
                Node *currentNode;
                if(x-> modCount == 0 && y-> modCount == 0){
                    currentNode = new Node(x);
                    currentNode->insertCluster(y);
                    
                }else{
                    if(x-> modCount == 0){
                        currentNode = y->childPtr;
                        currentNode->insertCluster(x);
                    }else{
                        currentNode = x->childPtr;
                        currentNode->insertCluster(y);
                    }
                }
                xy = new cluster();
                
                // DELETE
                q->merge(x,y,xy,REPR_COUNT,ALPHA);
                xy->modCount = x->modCount + y->modCount + 1;
                xy->childPtr = currentNode;
                currentNode->leaf = isMuCluster;
                settleNeighbors(currentNode);
                mergeNUpdate(q, x, y, xy);
                
            }else{
                switch(x->modCount){
                    case 0:							//y is deemed to be unmergeable
                        q->remove_cluster(y);
                        

                        transferNUpdate(y, q, tempQ);
                        break;
                				case 1: case 2:					//x is deemed to be unmergeable
                        //                        tempQ->insert_cluster(x);
                        q->remove_cluster(x);
                        
                        
//                        cout<<endl;
//                        cout<<"*********** TRANSFERING *************"<<endl;
//                        //cout<<"TRANDFER"<<endl;
//                        for(std::vector<vector<double>*>::iterator iter = x->points->begin(); iter != x->points->end(); iter++)
//                        {
//                            cout<<"("<< (*iter)->data()[0]<<","<<(*iter)->data()[1]<<")"<<endl;
//                        }
                        transferNUpdate(x, q, tempQ);
//                        cout<<" TRANSFERING "<<x->mean->data()[0]<<endl;
//                        cout<<"@@@@@@@@@@@ CONTENTS IN Q @@@@@@@@@"<<endl;
//                        for(std::list<cluster*>:: iterator it = q->heap->begin(); it != q->heap->end(); it++)
//                        {
//                            
//                            //if((*it)->closest->mean == nullptr)
//                           // {
//                                cout<< " ISKA CLOSEST NULL HAI "<<(*it)->mean->data()[0]<<endl;
//                           // }
////                            if(((*it)->mean != nullptr)  )
//////                                cout<<":"<<(*it)->mean->data()[0]<<" MOD->"<< (*it)->modCount<<":"<<" CLOSEST IS  "<< (*it)->closest->mean->data()[0]<<":" <<" DISTANCE "<< (*it)->distance_closest<<endl;
//////                                //cout<<":"<<(*it)->mean->data()[0]<<" MOD->"<< (*it)->modCount<<endl;
////                            else
////                                cout<<"NULLED  "<<endl;
////                            
//                        }
                        break;
                				default:
                        cout<< "Error!!! node cannot merge. abnormal merge count:(X) "
                        << x->distance_closest<< ", (Y) " << y->distance_closest<< endl;
                }
            }
            
        }
        //copy the last cluster entry into the tempQ
        x = q->getMinHeap();
        cluster *y = new cluster(*x);
        if(x->modCount == 0){
            x->childPtr = new Node(y);
        }
        //        tempQ->insert_cluster(x);
        //        q->remove_cluster(x);
//        cout<<endl;
//        cout<<"*********** TRANSFERING *************"<<endl;
//        //cout<<"TRANDFER"<<endl;
//        for(std::vector<vector<double>*>::iterator iter = x->points->begin(); iter != x->points->end(); iter++)
//        {
//            cout<<"("<< (*iter)->data()[0]<<","<<(*iter)->data()[1]<<")"<<endl;
//        }

        transferNUpdate(x, q, tempQ);
        if(q->size() != 0)
            cout<< "q is not empty after the level has finished!!!";
        isMuCluster = 0;
        
    }
    
    
    /**we are left with the root of the tree
     * residing at the child pointer of the cluster at tp he top of tempQ
     */
    clustreeRoot = tempQ->getMinHeap()->childPtr;
    
    
    
    
    // clustreeRoot = (*(tempQ->begin()))->childPtr;
    //todo destruct all queues and objects
    //delete q;
    //delete tempQ;
    
    //todo start the streaming
    
    //trying to print the tree
    //printTreeBF(clustreeRoot);
    //cout<<"ROOT FIRST ELEMENT " << *(clustreeRoot->cList).
    
    
    //to dos ----->
    /** [0]simulate streams -- variable speeds
     ** [1]make a cluster out of a data point
     ** [2]aggregate a group of points in a cluster-- needs the standard deviation of leaves
     ** [3]find closest entry to the point
     ** [4]use timestamps?
     ** [5]incremental updating the repPoints points of the matching cluster in the node
     ** [6]leaving hitchhiker
     ** [7]the leaves operations -- merged? radius increase? split and ascend -----
     ** ---discuss with Rachit
     
     
     */
    
    /*
     Node* presentNode = nullptr;
     
     
     std::vector<double> point;
     cluster* newPoint, *closestCluster;
     //to do use aggregartion
     
     //to do write a copy constructor for this
     presentNode = clustreeRoot;
     
     // to do identify if leaf has been reached
     leafReached = 0
     
     
     while(!leafReached)
     {
     
     }
     
     newPoint = createDataCluster(point);
     
     closestCluster = findClosestCluster(newPoint); // do for hitchhiker as well
     
     pickHitchhiker(closestCluster,newPoint);
     updateIncremental(closestCluster,newPoint);
     
     
     //discuss with rachit
     leavesUpdate(newPoint);
     */
    
    //cout<< (*(clustreeRoot->begin()))->mean->data()[0]<<endl;
    
    
    
    //cout<<" %%%%%%%%%%%% PRE  RESULTS   %%%%%%%%%%"<<endl;
   // printTreeBF(clustreeRoot);
    
    
    
    
    printTreeBFTree(clustreeRoot);

    
    
    
   //DESTROY EVERYTHING
    
    //DESTROY KD TREE
    if (tempQ->tree != nullptr) {
        delete tempQ->tree;
        tempQ->tree = nullptr;
    }
    if (q->tree != nullptr) {
        delete q->tree;
        q->tree = nullptr;
    }

    //destroy the dataset
    
    delete p_data;
    
    
    
    clock_t intermediate = clock();
    
    double interTime = double(intermediate)/CLOCKS_PER_SEC;
    
    cout<< " ~~~~~~~~~~~~~~~~ ITERMEDIATE  TIME  ELASPED ~~~~~~~~~~~~~~~~~~~~~~~~ "<<interTime<<endl;
    
    double elapsed_secs1 = double(intermediate-begin)/CLOCKS_PER_SEC;

    cout<<" !!!!!!!!!!!!!!! HALF TIME!!!!!!!!!"<<elapsed_secs1<<endl;

    
    createStream();
    
    
    //cout<<" %%%%%%%%%%%% POST RESULTS   %%%%%%%%%%"<<endl;
    
    
    
    //printTreeBF(clustreeRoot);
    
    printTreeBFStream(clustreeRoot);
    
    
    
    
    clock_t end = clock();
    
    double endTime = double(end)/CLOCKS_PER_SEC;
    double online = double(end - intermediate)/CLOCKS_PER_SEC;
    
    cout<< " ~~~~~~~~~~~~~~~~ END TIME ~~~~~~~~~~~~~~~~~~~~~~~~ "<<endTime<<endl;
    
    
    double elapsed_secs = double(end-begin)/CLOCKS_PER_SEC;
    
    cout<<" !!!!!!!!!!!!!!! ONLINE + OFFLINE !!!!!!!!!"<<elapsed_secs<<endl;
    cout<<" *************** ONLINE ****************** "<<online<<endl;
    
    

    
    
    
    return 0;
}
/*
 void prepareResults(cluster_analysis::cluster_data & p_result,heapNTree* queue){
 p_result = cure_data();
 cluster_analysis::cure_data result = (cure_data &) p_result;
 
 
 cluster_analysis::cluster_sequence_ptr clusters = result.clusters();
 clusters->resize(queue->size());
 size_t cluster_index = 0;
 for (heapNTree::const_iterator cure_cluster = queue->begin(); cure_cluster != queue->end(); cure_cluster++, cluster_index++) {
 cluster & standard_cluster = (*clusters)[cluster_index];
 for (std::vector<std::vector<double> * >::const_iterator point = (*cure_cluster)->points->begin(); point != (*cure_cluster)->points->end(); point++) {
 size_t index_point = (size_t) (*point - &(*(data->begin())));
 standard_cluster.push_back(index_point);
 }
 
 representor_sequence_ptr representors = result.representors();
 representors->resize(queue->size());
 
 dataset & cluster_representors = (*representors)[cluster_index];
 for (auto point : *(*cure_cluster)->rep) {
 cluster_representors.push_back(*point);
 }
 
 result.means()->push_back((*(*cure_cluster)->mean));
 }
 
 p_result = result;
 
 delete queue;
 queue = nullptr;
 }
 */

void mergeToLeaf(cluster* pointer, Node* leaf)
{
    
    double closestDistance;
    pointer->distance_closest = std::numeric_limits<double>::max();
    
    for(list<cluster*>:: iterator leafIterator = leaf->begin(); leafIterator != leaf->end(); leafIterator++){
        closestDistance = get_distance(pointer, *leafIterator);
        if(pointer->distance_closest > closestDistance){
            pointer->distance_closest = closestDistance;
            pointer->closest = *leafIterator;
        }
    }
//    cluster* updatedCluster = pointer->closest;
    //incrementally update the rep point of closest
    updateBestCluster(pointer, leaf);
    
//    std::list<cluster *> * relocation_request = nullptr;
//    relocation_request = new std::list<cluster *>();
//    double distance;
//    //update closest pointer of all
//    for(list<cluster*>:: iterator leafIterator = leaf->begin(); leafIterator != leaf->end(); leafIterator++)
//    {
//        if(updatedCluster != *leafIterator){
//        distance = get_distance(updatedCluster, *leafIterator);
//        
//        if((*leafIterator)->distance_closest > distance )
//        {
//            (*leafIterator)->distance_closest = distance;
//            (*leafIterator)->closest = updatedCluster;
//        }
//        else
//            relocation_request->push_back(*leafIterator);
//        }
//        
//    }
//    
//    double minDistance;
//    if(relocation_request != nullptr)
//    {
//        for (std::list<cluster* >::iterator iter1 = relocation_request->begin(); iter1 != relocation_request->end(); iter1++){
//            minDistance = std::numeric_limits<double>::max();
//            for (std::list<cluster* >::iterator iter2 = leaf->begin(); iter2 != leaf->end(); iter2++) {
//                if(*iter2 != *iter1)
//                {
//                    distance = get_distance(*iter1, *iter2);
//                    if(distance < minDistance)
//                    {
//                        minDistance = distance;
//                        (*iter1)->distance_closest = distance;
//                        (*iter1)->closest = *iter2;
//                    }
//                }
//                
//            }
//        }
//    }
//    
    
    
}

void insertToLeaf(cluster* pointer, Node* leafNode){
    double min_distance = 0.0;
    pointer->distance_closest = std::numeric_limits<double>::max();
    for(list<cluster*>::iterator nodeItr = leafNode->cList.begin(); nodeItr != leafNode->cList.end(); nodeItr++){
        min_distance = get_distance(*nodeItr, pointer);
        if((*nodeItr)->distance_closest > min_distance){
            (*nodeItr)->distance_closest = min_distance;
            (*nodeItr)->closest = pointer;
        }
        
        if(pointer->distance_closest > min_distance){
            pointer->closest = *nodeItr;
            pointer->distance_closest = min_distance;
        }
    }
    
    leafNode->insertCluster(pointer);
}

//testing
void createStream()
{
    
    std::vector<streamingPoint> * stream;
    stream = new std::vector<streamingPoint> ();
    
    
    
    stream = read_sample_streaming("/Users/abhisheksingh/Desktop/ADM ASSIGNMENT /runTests/bcTree/bcTree/testData40.txt");
    cout<<"SIZE OF STREAM "<<stream->size()<<endl;
//    //points = new std::vector<std::vector<double>* >();
//    vector<double> point1= {4.0};
//    cluster* streamPoint1 = new cluster(&point1);
//    
//    streamingPoint* streamingPoint1;
//    streamingPoint1 = (streamingPoint *)malloc(sizeof(streamingPoint));
//    
//    streamingPoint1->cluster = streamPoint1;
//    streamingPoint1->timeStamp = 1;
//    streamingPoint1->budget = 1;
//    
//    stream->push_back(*streamingPoint1);
//    
//    vector<double> point2= {114.0};
//    cluster* streamPoint2 = new cluster(&point2);
//    
//    
//    
//    streamingPoint* streamingPoint2;
//    streamingPoint2 = (streamingPoint *)malloc(sizeof(streamingPoint));
//    
//    streamingPoint2->cluster = streamPoint2;
//    streamingPoint2->timeStamp = 2;
//    streamingPoint2->budget = 5;
//    
//    stream->push_back(*streamingPoint2);
//    
//    
//    
//    vector<double> point3= {500.0};
//    cluster* streamPoint3 = new cluster(&point3);
//    
//    streamingPoint* streamingPoint3;
//    streamingPoint3 = (streamingPoint *)malloc(sizeof(streamingPoint));
//    
//    streamingPoint3->cluster = streamPoint3;
//    streamingPoint3->timeStamp = 3;
//    streamingPoint3->budget = 5;
//    
//    stream->push_back(*streamingPoint3);
//    
//    vector<double> point4= {104.0};
//    cluster* streamPoint4 = new cluster(&point4);
//    
//    streamingPoint* streamingPoint4;
//    streamingPoint4 = (streamingPoint *)malloc(sizeof(streamingPoint));
//    
//    streamingPoint4->cluster = streamPoint4;
//    streamingPoint4->timeStamp = 4;
//    streamingPoint4->budget = 5;
//    
//    stream->push_back(*streamingPoint4);
//    
//    vector<double> point5= {2.0};
//    cluster* streamPoint5 = new cluster(&point5);
//    
//    streamingPoint* streamingPoint5;
//    streamingPoint5 = (streamingPoint *)malloc(sizeof(streamingPoint));
//    
//    streamingPoint5->cluster = streamPoint5;
//    streamingPoint5->timeStamp = 5;
//    streamingPoint5->budget = 5;
//    
//    stream->push_back(*streamingPoint5);
    
    streamInfinitely(stream);
    
}


void streamInfinitely(std::vector<streamingPoint> * stream){
    
   // cout<<" TREE IS HERE in stream infinitely"<<endl;
   // printTreeBF(clustreeRoot);
    list<Node *> splitChain;
    Node *nodeMarker = nullptr;;
    long currTimestamp = 0, budget = 0;
    int c = 0;
    cluster *nearestCluster = nullptr, *nearestBuffCluster = nullptr;
    cluster *clusterA, *clusterB, *clusterAB = nullptr;
    cluster* probeNode =  nullptr;
    std::vector<streamingPoint>::iterator streamDataIter = stream->begin();
    
    //infinite loop for the streaming data
    while(1){
//        cout<<"STREAMING "<<endl;
        splitChain.clear();
        //read a new point from the input vector: remove
        if(streamDataIter != stream->end()){
            currTimestamp = (*streamDataIter).timeStamp;
            probeNode = (*streamDataIter).cluster;
            budget = (*streamDataIter).budget;
            streamDataIter++;
           // cout<<" INSERTING "<<"("<<probeNode->mean->data()[0]<<","<<probeNode->mean->data()[1]<<")"<<endl;
            c = 0;
            
        }else{
            //finish the streaming
            //cout<<" LAST TIME "<<endl;
            //printTreeBF(clustreeRoot);
            //cout<< "streaming ends!!!"<<endl;
            break;
        }
        //traverse down the tree
        nodeMarker = clustreeRoot;
        
        while(!nodeMarker->leaf){
            
            makeOlder(nodeMarker, currTimestamp - nodeMarker->timestamp);                //time decay the node
            nodeMarker->timestamp = currTimestamp;
            budget--;//remove later
            nearestCluster = findBestCluster(probeNode, nodeMarker);
            //test begins
            
            
          // cout<<" $$$$ "<<" RESULTS ON LEVEL: "<< c <<endl;
           // cout<<"closest to probenode:"<<"("<<probeNode->closest->mean->data()[0]<<","<<probeNode->closest->mean->data()[1]<<")"<<endl;
//            for(std::vector<std::vector<double>*>::iterator iter = probeNode->closest->repPoints->begin(); iter != probeNode->closest->repPoints->end() ; iter++)
//            {
//                cout<<"::::"<<"("<<(*iter)->data()[0]<<","<<(*iter)->data()[1]<<")"<<endl;
//            }
//
            c++;
            //test ends
            
            
            splitChain.push_front(nodeMarker);
            //            else{
            //                splitChain.clear();
            //            }
            
            //changes
            //if(probeNode->buff != nullptr)
            
            if(probeNode->buff->numPoints != 0)
                
            {
                nearestBuffCluster = findBestBuffCluster(probeNode->buff, nodeMarker);
                if(nearestBuffCluster != nearestCluster){
                    dropHitchiker(probeNode, nearestBuffCluster);
                }
            }
            
            if(!budget){        //check if new data point arrived
                if(nearestBuffCluster == nearestCluster){
                    dropHitchiker(probeNode, nearestBuffCluster);
                }
                dropPoint(probeNode, nearestCluster);
                break;
            }
            if(nearestCluster->buff->numPoints != 0)
                pickHitchiker(nearestCluster, probeNode);
            updateBestCluster(probeNode, nodeMarker);
            if(probeNode->buff->numPoints != 0){
                cluster* hitchHickerCluster = new cluster(probeNode->buff->LS);
                hitchHickerCluster->numberOfPoints = probeNode->numberOfPoints;
                hitchHickerCluster->closest = probeNode->closest;
                hitchHickerCluster->distance_closest = get_distance(hitchHickerCluster, hitchHickerCluster->closest);
                for(int i=1; i<CLASSES; i++){
                    (hitchHickerCluster->dom_vector)[i] = (probeNode->buff->dom_buff_vector)[i];
                    if( (hitchHickerCluster->dom_vector)[i] > 1000000)
                    {
                        cout<<"FARZI (7)"<<"lene wqala: "<<(hitchHickerCluster->dom_vector)[i]<<"dene wala: "<<(probeNode->buff->dom_buff_vector)[i]<<endl;
                    }
                }
                updateBestCluster(hitchHickerCluster, nodeMarker);
            }
            nodeMarker = nearestCluster->childPtr;
        }
        
        if(nodeMarker->leaf){
            makeOlder(nodeMarker, currTimestamp - nodeMarker->timestamp);                //time decay the node
            nodeMarker->timestamp = currTimestamp;
            budget--;//remove later
            //insert the hitchhicker
            if(probeNode->buff->numPoints != 0){
                //calculate mean of buffer
                for(vector<double>::iterator itr = probeNode->buff->LS->begin(); itr != probeNode->buff->LS->end(); itr++ ){
                    *itr = (*itr)/(probeNode->buff->numPoints);
                }
                cluster *hitchickerCluster = new cluster(probeNode->buff->LS);
                hitchickerCluster->numberOfPoints = probeNode->buff->numPoints;
                for(int i=1; i<CLASSES; i++){
                    (hitchickerCluster->dom_vector)[i] = (probeNode->buff->dom_buff_vector)[i];
                    if( (hitchickerCluster->dom_vector)[i] > 1000000)
                    {
                        cout<<"FARZI (8)lene wala: "<< (hitchickerCluster->dom_vector)[i] <<"dene wala:"<< (probeNode->buff->dom_buff_vector)[i]<<endl;
                    }
                    
                    
                }
                if(nodeMarker->cList.size() == MAX_CAP){
                    mergeToLeaf(hitchickerCluster, nodeMarker);
                }else{
                    insertToLeaf(hitchickerCluster, nodeMarker);
                }
            }
            probeNode->flushBuffer();
            
            if(!budget){
                if(nodeMarker->cList.size() == MAX_CAP){
                    mergeToLeaf(probeNode, nodeMarker);
                }else{
                    insertToLeaf(probeNode, nodeMarker);
                }
            }else{
                
                insertToLeaf(probeNode, nodeMarker);
                //test begins
//                //cout<<" The leaf level "<<endl;
//                cout<<"closest to probenode:"<<probeNode->closest->mean->data()[0]<<endl;
//                for(std::vector<std::vector<double>*>::iterator iter = probeNode->closest->repPoints->begin(); iter != probeNode->closest->repPoints->end() ; iter++)
//                {
//                    cout<<"::"<<(*iter)->data()[0]<<endl;
//                }
                //cout<<" $$$$ "<<" RESULTS ON LEAF: "<< (probeNode->closest->repPoints->data()[0])->data()[0]<<endl;
                
                //test ends
                
                //cout<<"leaf size:"<<nodeMarker->cList.size()<<endl;
                if(nodeMarker->cList.size() == (MAX_CAP + 1)){
                    splitChain.push_front(nodeMarker);
                    Node* fullNode ;
                    for(list<Node*>::iterator splitChainItr = splitChain.begin(); splitChainItr != splitChain.end();){
                        fullNode = *splitChainItr;
                        
                        //RACHECK SHOULD THESE BE HERE??
                        clusterA = new cluster();
                        clusterB = new cluster();
                        fullNode->splitNode(clusterA, clusterB);
                        if((*splitChainItr) == clustreeRoot){//split the root and increase the level
                            clustreeRoot = new Node(clusterA);
                            clustreeRoot->insertCluster(clusterB);
                            clusterA->closest = clusterB;
                            clusterA->distance_closest = get_distance(clusterA, clusterB);
                            clusterB->closest = clusterA;
                            clusterB->distance_closest = clusterA->distance_closest;
                            clustreeRoot->timestamp = (*splitChainItr)->timestamp;
                            clustreeRoot->leaf = 0;
                            break;
                        }
                        ++splitChainItr;
                        for(std::list<cluster*>::iterator itr = (*splitChainItr)->begin(); itr != (*splitChainItr)->end(); itr++){
                            if((*itr)->childPtr == fullNode)
                                clusterAB = (*itr);
                        }
                        //cout<<" CLUSTER AB "<<clusterAB<<endl;
                        recalcNeighbors(clusterA, clusterB, clusterAB, *splitChainItr);
                        (*splitChainItr)->insertCluster(clusterA);
                        (*splitChainItr)->insertCluster(clusterB);
                        (*splitChainItr)->removeCluster(clusterAB);
                        clusterA = nullptr;
                        clusterB = nullptr;
                        //update the neighbors
//                        delete(clusterAB);
                        if((*splitChainItr)->cList.size() <= MAX_CAP)
                            break;
                    }
                }
            }
        }
        
    }
    
    
}




