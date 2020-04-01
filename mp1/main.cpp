#include "rgbapixel.h"
#include "png.h"
#include <iostream>

int main(){

  PNG in("in.png");
  int height = in.height();
  int width = in.width();
  PNG out(width, height);
  for (int i = 0;i < width; i++){
     	for (int j = 0; j < height; j++){
		*out(width-1-i, height-1-j) = *in(i,j);
	}
  }
  
  out.writeToFile("out.png");
}


