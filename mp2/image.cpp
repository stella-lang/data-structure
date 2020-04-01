#include "image.h"

void Image::flipleft(){
   //PNG* original = new PNG;
   //original->readFromFile("in.png");
   int width = this->width();
   int height = this->height();
   RGBAPixel *temp = new RGBAPixel();
   for (int x = 0; x < width/2; x++){
	for (int y = 0; y < height; y++){
	   *temp = *(*this)(x,y);
	   *(*this)(x,y) = *(*this)(width-x-1,y);
	   *(*this)(width-x-1,y) = *temp;
	}
   }
   delete temp;
   temp=NULL;
}


void Image::adjustbrightness(int r, int g, int b){
   //PNG* original = new PNG;
   //original->readFromFile("in.png");
   int width = this->width();
   int height = this->height();
   RGBAPixel *temp = new RGBAPixel();
   for (int x = 0; x < width; x++){
	for (int y = 0; y < height; y++){
	   temp = (*this)(x,y);
	   if ( temp->red + r < 0){
		temp->red = 0;
	   }
	   else if (temp->red + r > 255){
		temp->red = 255;
	   }
	   else{
		temp->red = temp->red + r;
	   }


	   if ( temp->green + g < 0){
		temp->green = 0;
	   }
	   else if (temp->green + g > 255){
		temp->green = 255;
	   }
	   else{
		temp->green = temp->green + g;
	   }


           if ( temp->blue + b < 0){
		temp->blue = 0;
	   }
	   else if (temp->blue + b > 255){
		temp->blue = 255;
	   }
	   else{
		temp->blue = temp->blue + b;
	   }
	}
   }
   //delete temp;
   //temp=NULL;
}



void Image::invertcolors(){
   //PNG* original = new PNG;
   //original->readFromFile("in.png");
   int width = this->width();
   int height = this->height();
   RGBAPixel *temp = new RGBAPixel();
   for (int x = 0; x < width; x++){
	for (int y = 0; y < height; y++){
	   temp = (*this)(x,y);
	   temp->red = 255 - temp->red;
	   temp->green = 255 - temp->green;
	   temp->blue = 255 - temp->blue;
	}
   }
   //delete temp;
   //temp=NULL;
}


