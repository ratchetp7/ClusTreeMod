//
//  clusTree.hpp
//  bcTree
//
//  Created by Abhishek Singh on 27/03/17.
//  Copyright © 2017 Abhishek Singh. All rights reserved.
//

#ifndef clusTree_hpp
#define clusTree_hpp
#include<vector>
#include <stdio.h>
#include "hoogaBugaa.hpp"

#define LAMBDA 1.0
#define BETA 1.0
/*
 * @brief creates a cluster consisting of a single point
 * @param [in] a pointer to the single point(which is a vector of doubles)
 * @output gives you a pointer to a cluster
 */
cluster* createCluster(std::vector<double>* onePint);

/* @brief traverses the tree in depth(depth or breadth?) first fashion
 * @param [in] the new cluster to be inserted
 *        [in] the amount of time this data point has
 *        [in] the time at which this point arrived
 *
 */
 void insertBreadthFirst(cluster* newPoint, int budget,  long timestamp);

/*@brief find the closest leaf node
 *@param [in] the cluster to be merged
 *       [in] the node in which we will be looking for the closest cluster 
 *@recursively finds the best node to the cluster
 *
 *
 */


cluster* findBestCluster(cluster* toMeger,Node* pointer );

/* @brief picks the hitchhiker in  the points buffer
 *@param [in] the cluster from where to pick
 *       [in] the cluster to where to pick
 *
 */
void pickHitchiker(cluster* pickFrom, cluster* putHere);

/*@brief drops the hitchiker to it's closest cluster's buffer
 *@param [in] the cluster that has the hitchhiker
 *       [in] the the cluster to where the hitchiker is going to be dropped
 *
 *
 */
//void dropHitchhiker(buff* toDrop);
void dropHitchiker(cluster* pickFrom, cluster* dropHere);


/*@brief find best node for buffer entry in the node
 *@param [in] buffer of the cluster that the point was inserted to
 *@param [in] the current node pointer
 */
cluster* findBestBuffCluster(buff * buffer, Node* pointer);

/*@brief performs damping effect on the clusters of the nodes it visits
 *@param [in] the node that will be taken by the point
 *recursively
 */

void makeOlder(Node* treeNode, long pTimestamp);
/*@changes incrementally the representative points of the cluster to which the point is to be inserted
 *@param [in] the cluster that is being inserted
 *
 */
void updateBestCluster(cluster* toMerge);
/*@brief inserts the cluster to the node and no spliting needed
 *@param [in] the input to the leaf node
 *
 */


void insertWithoutSplit(Node* leafNode);

/*@brief inserts the cluster to the leaf and needs splitting
 *param [in] the input to the leaf node
 *
 */
void insertWithSplit(Node* leafNode);


/*@brief ascend and split 
 *@param [in] the parent of the child node where this was inserted 
 *
 */
void upToTop(cluster* bestParent);
/*@brief gives back the representative points of the computed  cluster
 *@param [in]  the pointer to the cluster
 *
 *
 */
std::vector<std::vector<double> * >* giveResults(cluster* point);

/*@brief buffers the point to the nearest cluster
 *@param [in]  the pointer to the cluster
 *@param [in] pointer to the destination cluster
 *
 */
 
void dropPoint(cluster* newCluster, cluster* dropHere);

double get_distance(cluster * cluster1, cluster * cluster2);

void updateBestCluster(cluster* toMerge, Node* oldNode);

void recalcNeighbors(cluster* clusterA, cluster* clusterB, cluster* clusterAB, Node* insertNode);




#endif /* clusTree_hpp */
