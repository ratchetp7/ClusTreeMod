//
//  hoogaBugaa.hpp
//  bcTree
//
//  Created by Abhishek Singh on 23/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved.
//

#ifndef hoogaBugaa_hpp
#define hoogaBugaa_hpp

#include <stdio.h>




//
//  agloClusTree.hpp
//  agloClusTree
//
//  Created by Abhishek Singh on 21/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved.
//


#include<vector>
#include<list>
#include<set>
#include<stdlib.h>
#include "kdtree.hpp"
#include<iostream>
 
#define MAX_CAP 3
#define MIN_CAP 1
#define DIM 12
#define REPR_COUNT 3
#define DIM_VECTOR DIM*sizeof(int)
#define NUM_POINTS_TRAINING 348607
#define NUM_POINTS_STREAMING 232405
#define CLASSES 8



//#include "cluster_algorithm.hpp"
//#include "cure_data.hpp"

//#include "utils.hpp"
 


using namespace std;

typedef struct buffer{
public:
    std::vector<double>* LS;
    //std::vector<double>* SS;
    int numPoints;
    long dom_buff_vector[CLASSES];
}buff;

class Node;
typedef struct cluster{
public:
    std:: vector<double>* mean;
    std:: vector<std::vector<double>* >* points;
    std:: vector<std::vector<double>* >* repPoints;
    
    struct cluster*  closest;
    double distance_closest;
    double radius;
    int modCount;
    Node* childPtr;
    buffer* buff;
    long numberOfPoints;
   // int clusID;
    //change: dom_vector
    long dom_vector[CLASSES];
    //change: dom vector ends
    //define the multiply decay factor: "$" operator
//    cluster* operator$(const double decayFactor){
//        for(vector<vector<double>* >::iterator itr1 = this->repPoints->begin(); itr1 != this->repPoints->end(); itr1++){
//            for(vector<double>::iterator itr2 = ***(*itr1)->begin(); itr2 != (*itr1)->end(); itr2++){
//                (*itr2) *= decayFactor;
//            }
//        }
//        return this;
//    }

    
    
public:
    
    /**
        default constructor
     **/
    cluster(void): closest(nullptr), distance_closest(0),  modCount(0), radius(0)  {
        points = new std::vector<std::vector<double>* >();
        mean =  new std::vector<double>(DIM,0);
        repPoints =  new std::vector<std::vector<double>* >();
        buff = (buffer*) calloc(1,sizeof(buffer));
        buff->LS = new std::vector<double>(DIM,0);
        
       // buff->SS = new std::vector<double>(DIM,0);

        buff->numPoints = 0;
        childPtr = NULL;
        //parentNode = NULL;
        numberOfPoints = 0;
       // buff = {nullptr,nullptr,0};
        
        //change: dom_vector
        for(int i =0; i< CLASSES; i++){
            dom_vector[i] = 0;
            (buff->dom_buff_vector)[i] = 0;
            
        //change: dom_vector ends
        }
    }
    
    
    
//    one point constructor
    
    cluster(std::vector<double> * OnePoint) : closest(nullptr) , distance_closest(0) ,modCount(0) ,radius(0.0) {
        mean =   new  std::vector<double> (*OnePoint);
        points =  new std::vector<std::vector<double>* > (1,new std::vector<double> (*OnePoint));  // this will point to the user data point
        repPoints =    new std::vector<std::vector<double>* >(1, new std::vector<double> (*OnePoint));   // we are creating our own copy of the points
        //buff = (buffer*) malloc(sizeof(buffer));
         buff = (buffer*) calloc(1,sizeof(buffer));
        buff->LS = new std::vector<double>(DIM,0);
        
       // buff->SS = new std::vector<double>(DIM,0);
        buff->numPoints = 0;
        childPtr = NULL;
        //parentNode = NULL;
        numberOfPoints = 1;
        //buff = {nullptr,nullptr,0};
        //change: dom_vector
        for(int i =0; i< CLASSES; i++){
            dom_vector[i] = 0;
            (buff->dom_buff_vector)[i] = 0;
            //change: dom_vector ends
        }
        
    }
    
    //change: dom_vector begins
    cluster(std::vector<double> * OnePoint, long dom_class): closest(nullptr) , distance_closest(0) ,modCount(0) ,radius(0.0) {
        mean =   new  std::vector<double> (*OnePoint);
        points =  new std::vector<std::vector<double>* > (1,new std::vector<double> (*OnePoint));  // this will point to the user data point
        repPoints =    new std::vector<std::vector<double>* >(1, new std::vector<double> (*OnePoint));   // we are creating our own copy of the points
        //buff = (buffer*) malloc(sizeof(buffer));
         buff = (buffer*) calloc(1,sizeof(buffer));
        buff->LS = new std::vector<double>(DIM,0);
        
        //buff->SS = new std::vector<double>(DIM,0);
        buff->numPoints = 0;
        childPtr = NULL;
        //parentNode = NULL;
        numberOfPoints = 1;
        //buff = {nullptr,nullptr,0};
        for(int i =1; i< CLASSES; i++)
        {
            if(dom_class == i)
            {
                dom_vector[i] = 1;
            }
            else
                dom_vector[i] = 0;
           // dom_vector[i] = i != dom_class ? 0: 1;
            (buff->dom_buff_vector)[i] = 0;
            
        }
             
    }
    //change: dom_vector end
    
    
    
    /**
     **copy constructor
     **/
    cluster(const cluster &src)
    {
        mean =  new std::vector<double>;
        for(std::vector<double>::iterator iter = src.mean->begin(); iter != src.mean->end(); iter++)
        {
            mean->push_back(*iter);
        }
        points = new std::vector<std::vector<double>* >;
        for(std::vector<std::vector<double>* >::iterator iter =  src.points->begin(); iter != src.points->end(); iter++)
        {
            vector<double>* temp =  new vector<double>;
            for(std::vector<double>::iterator iter1 = (*iter)->begin(); iter1 != (*iter)->end(); iter1++)
            {
                temp->push_back(*iter1);
            }
            points->push_back(temp);

        }
        
        
        repPoints = new std::vector<std::vector<double>* >;
        for(std::vector<std::vector<double>* >::iterator iter =  src.repPoints->begin(); iter != src.repPoints->end(); iter++)
        {
            vector<double>* temp =  new vector<double>;
            for(std::vector<double>::iterator iter1 = (*iter)->begin(); iter1 != (*iter)->end(); iter1++)
            {
                temp->push_back(*iter1);
            }
            repPoints->push_back(temp);
            
        }
        
        //buff = (buffer*) malloc(sizeof(buffer));
         buff = (buffer*) calloc(1,sizeof(buffer));
        buff->LS = new std::vector<double>;
        
        for(std::vector<double>::iterator iter = src.buff->LS->begin(); iter != src.buff->LS->end(); iter++)
        {
            buff->LS->push_back(*iter);
        }
        
//        buff->SS = new std::vector<double>;
//        
//        for(std::vector<double>::iterator iter = src.buff->SS->begin(); iter != src.buff->SS->end(); iter++)
//        {
//            buff->SS->push_back(*iter);
//        }
        
        
        buff->numPoints =  src.buff->numPoints;
        
        
        childPtr = src.childPtr;
        
        numberOfPoints = src.numberOfPoints;

         
        
        closest = src.closest;
        
        distance_closest = src.distance_closest;
        
        modCount = src.modCount;
        
        radius = src.radius;
        
       // clusID = src.clusID;

        //change: dom_vector
        for(int i =0; i< CLASSES; i++){
            dom_vector[i] = src.dom_vector[i];
             if(dom_vector[i] > 1000000)
             {
                 cout<<" FARZI RESULT (6) lene wala: "<<dom_vector[i]<<" dene wala:"<< src.dom_vector[i]<<endl;
             }
        }
        //change: dom_vector ends
        
        
    }
    ~cluster(void){
        if(mean != nullptr){
            delete mean;
            mean = nullptr;
        }
        delete points;
        points = nullptr;
        
        for (auto point_ptr : *repPoints) {
            delete point_ptr;
        }
        
        delete repPoints;		/* only storage, we are not owners of points */
        repPoints = nullptr;
        
    }
    
    //inserting points to the cluster(used while adding points of two cluster in a merged micro-microcluster
    
    void insertPoint(std::vector<std::vector<double>* >* newPoints){
        //std::vector<std::vector<double*> >:: iterator it = points->end();
        //std::vector<std::vector<double*> >:: iterator it2 = newPoints->begin();
        //std::vector<std::vector<double*> >:: iterator it3 = newPoints->end();
        
        points->insert(points->end(),newPoints->begin(),newPoints->end());
        //Racheck
        numberOfPoints = numberOfPoints + newPoints->size();
        
        
        
        
        
        
    }
    void flushBuffer()
    {
        for(int i = 0; i < DIM ; i++)
        {
            (*(buff->LS))[i] = 0;
           // (*(buff->SS))[i] = 0;
        }
        buff->numPoints = 0;
        for(int i = 0; i < CLASSES; i++)
        {
            (buff->dom_buff_vector)[i] = 0;
        }
    }
    
    
    
}clus;

class Node{
    
public:
    std::list<cluster*> cList;
    int leaf;
    long timestamp;
public:
    Node(){
        timestamp = 0;
        leaf = 0;
    }
    
    
    typedef std::list<cluster *>::iterator iterator;
    
    //typedef std::list<cluster *>::iterator iterator;
    
    iterator begin(){return cList.begin();}
    
    iterator end(){return cList.end();}
    
    void insertCluster(cluster *c){cList.push_back(c);}
    
    void removeCluster(cluster *c){cList.remove(c);}
    
    void updateClosest();
    
    Node(cluster* c){
        timestamp = 0;
        leaf = 0;
        insertCluster(c);
    }
    
    /**
     //	this returns the pointer to the newly created node after the split has taken place
     **/
    void splitNode(cluster *parentClusterA,cluster *parentClusterB);
    
    
};

class heapNTree{
    
public:
    std:: list<cluster *> *heap;
    //std:: list<cluster*>  dummyHeap;
    container::kdtree* tree;
    
public:
    
    
    
    
    /**
     *
     *Creates sorted queue of points for specified data.
     *
     *[in] data: pointer to points.
     *
     */
    void buildHeap(std::vector< std::vector<double> > * data,std::vector<long>* class_vector);
    
    
    /**
     *
     *Remove representative points of specified cluster from KD Tree.
     *
     *cluster: pointer to points.
     *
     */
    void remove_representative_points(cluster * cluster);
    
    /**
     *
     *Insert representative points of specified cluster to KD tree.
     *
     *[in] cluster: pointer to points.
     *
     */
    void insert_representative_points(cluster * cluster);
    /**
     *
     * Insert cluster to sorted queue.
     *
     *
     * [in] inserted_cluster: pointer to points.
     *
     */
    void insert_cluster(cluster * inserted_cluster);
    
    
    /**
     *
     *  Remove cluster from sorted queue (it's not removing of new object). Used by sorting
     *          procedures.
     *
     *  [in] removed_cluster: pointer to points.
     *
     */
    
    inline void remove_cluster(cluster * removed_cluster) {
        heap->remove(removed_cluster);
    }
    
    
    
    
    
    
    
public:
    typedef std::list<cluster *>::iterator iterator;
    
    //.typedef std::list<cluster *>::iterator iterator;
    
    /**
     *
     * Default constructor of cure queue (always keeps sorted state).
     *
     */
    heapNTree(void){
        heap = new std::list<cluster *>();
        tree = new container::kdtree();
        //debug
        //dummyHeap = *(std::list<cluster>());
    }
    /**
     *
     * Default constructor of sorted queue of cure clusters.
     *
     * [in] data: pointer to points.
     *
     */
    heapNTree(std::vector< std::vector<double> > * data, std::vector<long>* class_vector){
        
        this->heap = new std::list<cluster *>();
        buildHeap(data,class_vector);
        //debug
        //this->dummyHeap = new std::list<cluster>();
        
        tree = new container::kdtree();
        
        for (heapNTree::iterator cluster1 = heap->begin(); cluster1 != heap->end(); cluster1++) {
            for (std::vector<std::vector<double> *>::iterator point = (*cluster1)->repPoints->begin(); point != (*cluster1)->repPoints->end(); point++) {
                tree->insert(*point, *cluster1);
            }
        }
        
    }
    
    //copy constructor
    
    heapNTree(const heapNTree &src)
    {
        heap = new std::list<cluster *>();
        for(std::list<cluster*>:: iterator it = src.heap->begin(); it != src.heap->end(); it++)
        {
            heap->push_back(*it);
            
            
        }
        tree = new container::kdtree();
        for (heapNTree::iterator cluster1 = heap->begin(); cluster1 != heap->end(); cluster1++) {
            for (std::vector<std::vector<double> *>::iterator point = (*cluster1)->repPoints->begin(); point != (*cluster1)->repPoints->end(); point++) {
                tree->insert(*point, *cluster1);
            }
        }
        
        
    }
    
    
    /**
     *
     * Default destructor.
     *
     */
    ~heapNTree(void){
        if (heap != nullptr) {
            for (auto cluster : *heap) {
                delete cluster;
            }
            
            delete heap;
            heap = nullptr;
        }
        
        if (tree != nullptr) {
            delete tree;
            tree = nullptr;
        }
    }
    
    /**
     * Calculate distance between clusters.
     *
     * [in] cluster1: pointer to cure cluster 1.
     * [in] cluster2: pointer to cure cluster 2.
     *
     * Return distance between clusters.
     *
     */
    
    
    double get_distance(cluster * cluster1, cluster * cluster2);
    
    /**
     *
     * Merge cure clusters in line with the rule of merging of cure algorithm.
     *
     *  [in|out] cluster1: pointer to cure cluster 1.
     *  [in|out] cluster2: pointer to cure cluster 2.
     *  [in|out] mergedCluster: pointer to the merged cluster.
     *  [in] number_repr_points: number of representative points for merged cluster.
     *  [in] compression: level of compression for calculation representative points.
     *
     */
    
    void merge(cluster *cluster1, cluster *cluster2, cluster*  mergedCluster, const size_t number_repr_points, const double compression);
    
    
    
    
    
    
    
    
    /**
     *
     * @brief   Returns iterator to the first CURE cluster.
     *
     */
    inline iterator begin(void) { return heap->begin(); }
    
    /**
     *
     * @brief   Returns constant iterator to the first CURE cluster.
     *
     */
    //inline iterator begin(void)   { return heap->begin(); };
    
    /**
     *
     * @brief   Returns iterator to the end of CURE cluster collection (not a last element).
     *
     */
    //inline iterator end(void) { return heap->end(); }
    
    /**
     *
     * @brief   Returns constant iterator to the end of CURE cluster collection (not a last element).
     *
     */
    inline iterator end(void)   { return heap->end(); }
    
    /**
     *
     * @brief   Returns amount of CURE clusters in the queue.
     *
     */
    inline size_t size(void) { return heap->size(); }
    
    inline cluster* getMinHeap(void){ return heap->front(); }
    
    
    
    
    
    
};

void remerge(cluster* one, cluster* two, cluster* oneTwo);


typedef struct streamingPoint
{
    cluster* cluster;
    long timeStamp;
    long budget;
    
}streamingPoint;

#endif /* agloClusTree_hpp */



