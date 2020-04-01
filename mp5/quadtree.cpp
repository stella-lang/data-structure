/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include <iostream>
#include "quadtree.h"
#include <cmath>


using namespace std;


//constructor
Quadtree::Quadtree(){
	root = NULL;
	myrsl = 0;
}


//constructor
Quadtree::Quadtree(PNG const & source,int resolution){
	buildTree(source, resolution);
}

//copy constructor
Quadtree::Quadtree(Quadtree const & other){
	root = copy(other.root);
	
}

//helper function copy
Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode * subroot)const{
	if ( subroot == NULL){
		return NULL;
	}
	
	QuadtreeNode* newtree = new QuadtreeNode;
		newtree->element = subroot->element;
		newtree->nwChild = copy(subroot->nwChild);
		newtree->neChild = copy(subroot->neChild);
		newtree->swChild = copy(subroot->swChild);
		newtree->seChild = copy(subroot->seChild);
		return newtree;
}

//destructor
Quadtree::~Quadtree(){
	clear(root);
	root = NULL;
	myrsl = 0;
}

//helper function clear
void Quadtree::clear(QuadtreeNode *& subroot){
	//check null
	if (subroot == NULL){
		return;
	}
	
	clear(subroot->nwChild);
	clear(subroot->neChild);
	clear(subroot->swChild);
	clear(subroot->seChild);
	delete subroot;
	
	
}

//assignment operator
Quadtree const & Quadtree::operator=(Quadtree const & other){
	//protect against re-assignment
	if (root != other.root){
		//clear lhs
		clear(root);
		//copy rhs
		root = copy(other.root);
		myrsl = other.myrsl;
	}
	
	return *this;
}


void Quadtree::buildTree (PNG const & source, int resolution){
	//clear(root);
	root = buildTreeHelper(source, resolution, 0, 0);
	myrsl = resolution;
}

//buildtree helper function
Quadtree::QuadtreeNode* Quadtree::buildTreeHelper(PNG const & source, int resolution, int x, int y){
	//base case
	if (resolution == 1){
		QuadtreeNode* newnode = new QuadtreeNode();
		newnode->element = *(source(x,y));
		
		return newnode;
	}
	QuadtreeNode* newnode = new QuadtreeNode();
	newnode->nwChild = buildTreeHelper(source, resolution/2, x, y);
	newnode->neChild = buildTreeHelper(source, resolution/2, x + resolution/2, y);
	newnode->swChild = buildTreeHelper(source, resolution/2, x, y + resolution/2);
	newnode->seChild = buildTreeHelper(source, resolution/2, x + resolution/2, y + resolution/2);
	
	
	//calculate color
	newnode->element.red = (newnode->nwChild->element.red + newnode->neChild->element.red + newnode->swChild->element.red + newnode->seChild->element.red)/4;
	newnode->element.green = (newnode->nwChild->element.green + newnode->neChild->element.green + newnode->swChild->element.green + newnode->seChild->element.green)/4;
	newnode->element.blue = (newnode->nwChild->element.blue + newnode->neChild->element.blue + newnode->swChild->element.blue + newnode->seChild->element.blue)/4;
	
	return newnode;
	
}


RGBAPixel Quadtree::getPixel(int x, int y) const{
	if (root == NULL || x >= myrsl || y >= myrsl || x <0 || y <0){
		return RGBAPixel();
	}
	
	return getPixelHelper(root, x, y, myrsl);
}

//helper function for getpixel
RGBAPixel Quadtree::getPixelHelper(QuadtreeNode* subroot, int x, int y, int resolution)const{
	if (subroot == NULL){
		return RGBAPixel();
	}
	else if (resolution == 1 || subroot->nwChild == NULL || subroot->neChild == NULL || subroot->swChild == NULL || subroot->seChild == NULL){
	return subroot->element;
	}
	else{
		if ( x < resolution/2 && y < resolution/2){
			return getPixelHelper(subroot->nwChild, x,y,resolution/2);
		}
		else if ( x >= resolution/2 && y < resolution/2){
			return getPixelHelper(subroot->neChild, x-resolution/2,y,resolution/2);
		}
		else if ( x < resolution/2 && y >= resolution/2){
			return getPixelHelper(subroot->swChild, x,y-resolution/2,resolution/2);
		}
		else{
			return getPixelHelper(subroot->seChild, x-resolution/2,y-resolution/2,resolution/2);
		}
	}
	

}


PNG Quadtree::decompress() const{
		if (root == NULL ){
			return  PNG();
		}
		
		PNG newpng = PNG(myrsl, myrsl);
		/*for (int i = 0; i < myrsl; i++){
			for (int j = 0; j < myrsl; j++){
				*(newpng(i,j)) = getPixel(i,j);
			}
		}*/
		decompress(root, newpng, 0, 0, myrsl);
		return newpng;	
}

//helper function for decompress
void Quadtree::decompress(QuadtreeNode* subroot, PNG & source, int x, int y, int resolution) const{
	if (subroot->nwChild == NULL || subroot->neChild == NULL || subroot->swChild == NULL || subroot->seChild == NULL){
		for (int i = 0; i < resolution; i++){
			for (int j = 0; j < resolution; j++){
				*(source(x+i,y+j)) = subroot->element;
			}
		}
	}
	else{
		decompress(subroot->nwChild, source, x, y, resolution/2);
		decompress(subroot->neChild, source, x+resolution/2, y, resolution/2);
		decompress(subroot->swChild, source, x, y+resolution/2, resolution/2);
		decompress(subroot->seChild, source, x+resolution/2, y+resolution/2, resolution/2);
	}
}

void Quadtree::clockwiseRotate(){
	if (root == NULL){
		return;
	}
	clockwiseRotate(root);
}

//helper function fro clockwiseRotate
void Quadtree::clockwiseRotate(QuadtreeNode* subroot){
	if (subroot == NULL){
		return;
	}
	
	QuadtreeNode* temp = subroot->nwChild;
	subroot->nwChild = subroot->swChild;
	subroot->swChild = subroot->seChild;
	subroot->seChild = subroot->neChild;
	subroot->neChild = temp;
	clockwiseRotate(subroot->nwChild);
	clockwiseRotate(subroot->neChild);
	clockwiseRotate(subroot->swChild);
	clockwiseRotate(subroot->seChild);
}


void Quadtree::prune(int tolerance){
	if (root == NULL){
		return;
	}
	pruneHelper(root, tolerance);
}

//helper function for prune
void Quadtree::pruneHelper(QuadtreeNode* subroot, int tolerance){
	if (subroot == NULL){
		return;
	}
	if (differ(subroot, subroot, tolerance)){
		clear(subroot->nwChild);
		clear(subroot->neChild);
		clear(subroot->swChild);
		clear(subroot->seChild);
		return;
	}
	pruneHelper(subroot->nwChild, tolerance);
	pruneHelper(subroot->neChild, tolerance);
	pruneHelper(subroot->swChild, tolerance);
	pruneHelper(subroot->seChild, tolerance);
}


//helper function to check whether the color value of no leaf in Tn differs from avg by more than tolerance
bool Quadtree::differ(QuadtreeNode* a, QuadtreeNode* b, int tolerance)const{
	if (a == NULL || b == NULL){
		return false;
	}
	int difference = pow((a->element.red - b->element.red),2) + pow((a->element.green - b->element.green),2) + pow((a->element.blue - b->element.blue),2);
	if (a->nwChild == NULL){
		if (difference <= tolerance){
			return true;
		}
		else{
			return false;
		}
	}
	return (differ(a->nwChild, b, tolerance) && differ(a->neChild, b, tolerance) && differ(a->swChild, b, tolerance) && differ(a->seChild, b, tolerance));
}

int Quadtree::pruneSize(int tolerance) const{
	if (root == NULL){
		return 0;
	}
	return pruneSizeHelper(root, tolerance);
}

//helper function for pruneSize
int Quadtree::pruneSizeHelper(QuadtreeNode* subroot, int tolerance)const{
	if (subroot == NULL){
		return 0;
	}
	if (subroot->nwChild == NULL){
		return 1;
	}
	if (differ(subroot, subroot, tolerance)){
		return 1;
	}
	return pruneSizeHelper(subroot->nwChild, tolerance) + pruneSizeHelper(subroot->neChild, tolerance) + pruneSizeHelper(subroot->swChild, tolerance) + pruneSizeHelper(subroot->seChild, tolerance);
}


int Quadtree::idealPrune(int numLeaves) const{
	if (root == NULL){
		return 0;
	}
	int lo = 0;
	int hi = 3*255*255;
	return idealPruneHelper( lo, hi, numLeaves);
}

//helper function for idealPrune
int Quadtree::idealPruneHelper(int lo, int hi, int numLeaves)const{
	int mid;
	while (lo < hi){
		mid = (lo+hi)/2;
		if (pruneSize(mid) > numLeaves){
			lo = mid + 1;
		}
		else{
			hi = mid;
		}
		
	}
	
	return lo;

}

