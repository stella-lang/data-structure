/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    //decalre new canvas and map and the vector to store colors
    vector<Point<3>> mycolors;
    map<Point<3>,TileImage> mymap;
    MosaicCanvas *mycanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (size_t i = 0; i < theTiles.size(); i++){
    //get the average color and map it with the tile
		RGBAPixel avg = theTiles[i].getAverageColor();
		Point<3> tilepx(avg.red, avg.green,avg.blue);
		mymap[tilepx] = theTiles[i];
		mycolors.push_back(tilepx);
	}
	//build a kdtree
	KDTree<3>::KDTree mytree(mycolors);
	for (int i =0; i < theSource.getRows(); i++){
		for (int j = 0; j < theSource.getColumns(); j++){
		//get the color for tile and then put tiles on canvas
			RGBAPixel avg2 = theSource.getRegionColor(i,j);
			Point<3> tilepx2(avg2.red, avg2.green,avg2.blue);
			Point<3> neighbor = mytree.findNearestNeighbor(tilepx2);
			TileImage target = mymap[neighbor];
			mycanvas->setTile(i,j,target);
		}
	}
    return mycanvas;
}

