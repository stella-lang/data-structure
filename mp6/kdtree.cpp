/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include "math.h"
#include <iostream>

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim]){
    	return first < second;
    }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int disc = 0;
    int disp = 0;
    for (int i = 0; i < Dim; i++){
    	disc += pow(currentBest[i] - target[i], 2);
    	disp += pow(potential[i] - target[i], 2);
    }
    if (disc == disp){
    	return potential < currentBest;
    }
    return disp < disc;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
     /*points.resize(newPoints.size());
     if (newPoints.size() == 0){
     	return;
     }
     for (unsigned i = 0; i < newPoints.size(); i++){
     	points[i] = newPoints[i];
     }*/
     if (points.size() != 0)
     buildtree(0,newPoints.size()-1,0);
}

//helper function for ctor
template <int Dim>
void KDTree<Dim>::buildtree(int left, int right, int curDim){
	//base case
	if (left == right){
		return;
	}
	
	//find the median of points
	int m = (left+right)/2;
	select(left, right, m, curDim);
	//recurse on the left and right part using splitting dimension (d+1) mod k
	if (left < m){
		buildtree(left,m-1,(curDim+1)%Dim);
	}
	if (right > m){
		buildtree(m+1,right,(curDim+1)%Dim);
	}
}

//helper function quick select
template <int Dim>
void KDTree<Dim>::select(int left, int right, int med, int curDim){

	while(left <= right){
	int newindex = partition(left,right,med,curDim);
	if (  newindex == med){
		return;
	}
	else if (med < newindex){
		//select(left, newindex-1,m,curDim);
		right = newindex -1;
	}
	else{
		//select(newindex+1,right,m,curDim);
		left = newindex + 1;
	}
	}
}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int curDim){
	//move pivot to end
	int tempindex = left;
	Point<Dim> pivot = points[pivotIndex];
	Point<Dim> temp = points[right];
	points[right] = points[pivotIndex];
	points[pivotIndex] = temp;
	
	//swap elem if it's smaller than pivot value
	for (int i = left; i < right; i++){
	if (smallerDimVal(points[i], pivot, curDim) || points[i] == pivot){
		temp = points[tempindex];
		points[tempindex] = points[i];
		points[i] = temp;
		tempindex++;
	}
	}
	//place pivot to right place
	temp = points[right];
	points[right] = points[tempindex];
	points[tempindex] = temp;
	return tempindex;

}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    
    return nnHelper(query,0,points.size()-1,0);
}

//helper function for fnn
template <int Dim>
Point<Dim> KDTree<Dim>::nnHelper(const Point<Dim>& query, int left, int right, int x)const{
	int m = (left+right)/2;
	Point<Dim> curr;
	bool checked = false;
	//base case
	if (left >= right){
		return points.at(m);
	}
	else{
		if (smallerDimVal(query, points.at(m),x%Dim)){
			curr = nnHelper(query, left, m-1, x+1);
			checked = true;
		}
		else{
			curr = nnHelper(query, m+1,right,x+1);
		}
	}
	
	//check whether points.at(m) is closer
	if (shouldReplace(query,curr,points.at(m))){
		curr = points.at(m);
	}
	//calculate the distance
	int dis = 0;
	for (int i = 0; i < Dim; i++){
		dis += pow(curr[i]-query[i],2);
	}
	int dis2 = pow(query[x%Dim]-points.at(m)[x%Dim],2);
	Point<Dim> temp;
	if (dis >= dis2){
		if (!checked){
			temp = nnHelper(query, left, m-1,x+1);
		}
		else{
			temp = nnHelper(query, m+1,right,x+1);
		}
		
		//replace the orig if we find a better one
		if (shouldReplace(query,curr,temp)){
			curr = temp;
		}
	}
	return curr;

}
