/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
	Quadtree();
	Quadtree(const PNG & source, int resolution);
	Quadtree(Quadtree const & other);
	~Quadtree();
	Quadtree const & operator=(Quadtree const & other);
	void buildTree(PNG const & source, int resolution);
	RGBAPixel getPixel (int x, int y) const;
	PNG decompress() const;
	void clockwiseRotate();
	void prune(int tolerance);
	int pruneSize(int tolerance) const;
	int idealPrune(int numLeaves) const;
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
        
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */
    int myrsl;
	//helper function
	void clear(QuadtreeNode *& subroot);
	QuadtreeNode* copy(QuadtreeNode * subroot)const;
	QuadtreeNode* buildTreeHelper(PNG const & source, int resolution, int xcoord, int ycoord);
	void decompress(QuadtreeNode* subroot, PNG & source, int x, int y, int resolution) const;
	RGBAPixel getPixelHelper(QuadtreeNode* subroot, int x, int y, int resolution)const;
	void clockwiseRotate(QuadtreeNode* subroot);
	void pruneHelper(QuadtreeNode* subroot, int tolerance);
	bool differ(QuadtreeNode* a, QuadtreeNode* b, int tolerance)const;
	int pruneSizeHelper(QuadtreeNode* subroot, int tolerance)const;
	int idealPruneHelper(int lo, int hi, int numLeaves)const;
/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
