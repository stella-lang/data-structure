#include "scene.h"
#include "image.h"
#include <iostream>

using namespace std;

Scene::Scene(int max){
    this->max = max;
    x = new Image*[max];
    xcoords = new int[max];
    ycoords = new int[max];
    for (int i = 0; i < max; i++){
        x[i] = NULL;
    }
}


Scene::~Scene(){
    clear();
}


Scene::Scene(const Scene& source){
    copy(source);
}


const Scene& Scene::operator=(const Scene& source){
//   if (this != & source){
//	clear();
//	copy(source);
//   }
   
//   return *this; 
	if (this != & source){
	delete [] xcoords;
	delete [] ycoords;
	for ( int i = 0; i < max; i++){
		delete x[i];
		x[i] = NULL;
	}
	delete [] x;
	copy(source);
	}
	return *this;
	
}


void Scene::changemaxlayers(int newmax){
    Image **tempx = new Image*[newmax];
    int *tempxcoord = new int[newmax];
    int *tempycoord = new int[newmax];
   
    if (newmax < max){
	for (int i = newmax; i < max; i++){
	   if (x[i] == NULL){
		cout << "invalid newmax" << endl;
		return;
	   }
	}
    }


    if (newmax > max){
    	for (int i = 0; i < max; i++){
		tempx[i] = x[i];
        	tempxcoord[i] = xcoords[i];
		tempycoord[i] = ycoords[i];
   	}
	for (int i = max; i < newmax; i++){
		tempx[i] = NULL;
        	tempxcoord[i] = 0;
		tempycoord[i] = 0;
	}
    }
    else{
	for (int i = 0; i < newmax; i++){
		tempx[i] = x[i];
        	tempxcoord[i] = xcoords[i];
		tempycoord[i] = ycoords[i];
   	}
    }
    

    clear();
    x = tempx;
    xcoords = tempxcoord;
    ycoords = tempycoord;




}



void Scene::addpicture(const char* FileName, int index, int x, int y){
    if (index > max-1){
	cout << "index out of bounds" << endl;
	return;
    }
    
	Image *picture = new Image();
	picture->readFromFile(FileName);
		
//	x[index] = picture;
	xcoords[index] = x;
	ycoords[index] = y;
	delete picture;
	

}


void Scene::changelayer(int index, int newindex){
   if (index < 0 || index > max - 1 || newindex < 0 || newindex > max){
	cout << "invalid index" << endl;
	return;
    }
    
    	if (newindex == index){
		return;
   	}
    	if ( x[newindex] != NULL){
		delete x[newindex];
    	}
	x[newindex] = x[index];
	xcoords[newindex] = xcoords[index];
	ycoords[newindex] = ycoords[index];
	x[index] = NULL;
    
}



void Scene::translate(int index, int xcoord, int ycoord){
    if (index < 0 || index > max - 1 || x[index] == NULL){
	cout << "invalid index" << endl;
	return;
    }
    
	xcoords[index] = xcoord;
	ycoords[index] = ycoord;
    	return;

}



void Scene::deletepicture(int index){
    if (index < 0 || index > max - 1 || x[index] == NULL){
	cout << "invalid index" << endl;
	return;
    }
    else{
	delete x[index];
	x[index] = NULL;
    }
    return;


}


Image *Scene::getpicture(int index) const{
    if (index < 0 || index > max - 1 ){
	cout << "invalid index" << endl;
	return NULL;
    }
    else {
	return x[index];
    }


}


Image Scene::drawscene() const{
	size_t width = 0;
	size_t height = 0;
	for(int i = 0; i < max; i++){
        if(x[i] != NULL){
            
            if((unsigned int)height < (x[i]->height()+ycoords[i]))
                height = x[i]->height()+ycoords[i];
            if((unsigned int)width < (x[i]->width()+xcoords[i]))
                width = x[i]->width()+xcoords[i];
        }
    }
	Image newimage = Image();
	newimage.resize(width, height);
	return newimage;
	    	

}


void Scene::clear(){
    if ( x != NULL){
	for (int i = 0; i < max; i++){
		delete x[i];
	}
    }
    delete [] x;
    delete [] xcoords;
    delete [] ycoords;

}


void Scene::copy(const Scene& source){
    max = source.max;
    x = new Image*[max];
    xcoords = new int[max];
    ycoords = new int[max];
    for (int i = 0; i < max; i++){
	if(source.x[i] != NULL){
	x[i] = new Image(*(source.x[i]));
	xcoords[i] = source.xcoords[i];
	ycoords[i] = source.ycoords[i];
	}
	else{
	x[i] = NULL;
	xcoords[i] = source.xcoords[i];
	ycoords[i] = source.ycoords[i];
	}
    }
}
















