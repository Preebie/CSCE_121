#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { 
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { 
      fail = true;
    }
  }
  
  if (fail) { 
    for (int i=0; i < width; ++i) {
      delete [] image[i]; 
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
	int* seam = new int[length];
	for(int i = 0; i < length; i++){
		seam[i] = 0;
	}
	return seam;
}

void deleteSeam(int* seam) {
	delete[] seam;
	seam = nullptr;
}

bool loadImage(string filename, Pixel** image, int width, int height) {

  ifstream ifs(filename);

  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }

  char type[3];
  ifs >> type; // should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  int w = 0, h = 0;
  ifs >> w >> h;
  if (ifs.fail() >> w) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (ifs.fail() >> h) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (w != width) { 
    cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;
    return false;
  }

  int colorMax{};
  ifs >> colorMax;
  if (ifs.fail() >> colorMax) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (colorMax != 255) {
    cout << "Error: invalid color value " << colorMax << endl;
    return false;
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      Pixel value;
      ifs >> value.r >> value.g >> value.b;
      if ((value.r < 0) || (value.r > 255)) {
        cout << "Error: invalid color value " << value.r << endl;
        return false;
      }
      if ((value.g < 0) || (value.g > 255)) {
        cout << "Error: invalid color value " << value.g << endl;
        return false;
      }
      if ((value.b < 0) || (value.b > 255)) {
        cout << "Error: invalid color value " << value.b << endl;
        return false;
      }
      if ((ifs.fail() >> value.r) && (ifs.eof())) {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if (ifs.fail() >> value.r) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if ((ifs.fail() >> value.b) && (ifs.eof())) {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if (ifs.fail() >> value.b) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if ((ifs.fail() >> value.g) && (ifs.eof())) {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if (ifs.fail() >> value.g) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      image[j][i] = value;
    }
  }
  Pixel value;
  ifs >> value.r >> value.g >> value.b;
  if ((value.r > 0)) {
    cout << "Error: too many color values" << endl;
    return false;
  }
  if ((value.g > 0)) {
    cout << "Error: too many color values" << endl;
    return false;
  }
  if ((value.b > 0)) {
    cout << "Error: too many color values" << endl;
    return false;
  }

  return true;
}
bool outputImage(string filename, Pixel** image, int width, int height) {
	ofstream ofs(filename);
	if(!ofs.is_open()){
		cout << "Error: failed to open output file - " << filename << endl;
		return false;
	}
	
	ofs << "P3" << endl;
	ofs << width << " ";
	ofs << height << endl;
	ofs << "255" << endl;
	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			Pixel temp = image[j][i];
			ofs << temp.r << " ";
			ofs << temp.g << " ";
			ofs << temp.b << endl;
		}
	}
	return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
	int energy = 0; 
	int x_energy, y_energy;
	int w_edge = width - 1;
	int h_edge = height - 1;
	int r_energy, g_energy, b_energy;
	
	if(x == w_edge && y == h_edge){
		r_energy = image[0][y].r - image[x-1][y].r;
		g_energy = image[0][y].g - image[x-1][y].g;
		b_energy = image[0][y].b - image[x-1][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][0].r - image[x][y-1].r;
		g_energy = image[x][0].g - image[x][y-1].g;
		b_energy = image[x][0].b - image[x][y-1].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	else if(x == w_edge && y == 0){
		r_energy = image[0][y].r - image[x-1][y].r;
		g_energy = image[0][y].g - image[x-1][y].g;
		b_energy = image[0][y].b - image[x-1][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][y+1].r - image[x][h_edge].r;
		g_energy = image[x][y+1].g - image[x][h_edge].g;
		b_energy = image[x][y+1].b - image[x][h_edge].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	else if(x == 0 && y == h_edge){
		r_energy = image[x+1][y].r - image[w_edge][y].r;
		g_energy = image[x+1][y].g - image[w_edge][y].g;
		b_energy = image[x+1][y].b - image[w_edge][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][0].r - image[x][y-1].r;
		g_energy = image[x][0].g - image[x][y-1].g;
		b_energy = image[x][0].b - image[x][y-1].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	else if(x == w_edge){
		r_energy = image[0][y].r - image[x-1][y].r;
		g_energy = image[0][y].g - image[x-1][y].g;
		b_energy = image[0][y].b - image[x-1][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][y+1].r - image[x][y-1].r;
		g_energy = image[x][y+1].g - image[x][y-1].g;
		b_energy = image[x][y+1].b - image[x][y-1].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	else if(y == h_edge){
		r_energy = image[x+1][y].r - image[x-1][y].r;
		g_energy = image[x+1][y].g - image[x-1][y].g;
		b_energy = image[x+1][y].b - image[x-1][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][0].r - image[x][y-1].r;
		g_energy = image[x][0].g - image[x][y-1].g;
		b_energy = image[x][0].b - image[x][y-1].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	else if(x == 0 && y == 0){
		r_energy = image[x+1][y].r - image[w_edge][y].r;
		g_energy = image[x+1][y].g - image[w_edge][y].g;
		b_energy = image[x+1][y].b - image[w_edge][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][y+1].r - image[x][h_edge].r;
		g_energy = image[x][y+1].g - image[x][h_edge].g;
		b_energy = image[x][y+1].b - image[x][h_edge].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	else if(x == 0){
		r_energy = image[x+1][y].r - image[w_edge][y].r;
		g_energy = image[x+1][y].g - image[w_edge][y].g;
		b_energy = image[x+1][y].b - image[w_edge][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][y+1].r - image[x][y-1].r;
		g_energy = image[x][y+1].g - image[x][y-1].g;
		b_energy = image[x][y+1].b - image[x][y-1].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	else if(y == 0){
		r_energy = image[x+1][y].r - image[x-1][y].r;
		g_energy = image[x+1][y].g - image[x-1][y].g;
		b_energy = image[x+1][y].b - image[x-1][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][y+1].r - image[x][h_edge].r;
		g_energy = image[x][y+1].g - image[x][h_edge].g;
		b_energy = image[x][y+1].b - image[x][h_edge].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	else{
		r_energy = image[x+1][y].r - image[x-1][y].r;
		g_energy = image[x+1][y].g - image[x-1][y].g;
		b_energy = image[x+1][y].b - image[x-1][y].b;
		x_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
		r_energy = image[x][y+1].r - image[x][y-1].r;
		g_energy = image[x][y+1].g - image[x][y-1].g;
		b_energy = image[x][y+1].b - image[x][y-1].b;
		y_energy = pow(r_energy, 2.0) + pow(g_energy, 2.0) + pow(b_energy, 2.0);
	}
	energy = x_energy + y_energy;
		
	return energy;
}

//int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
//	return 0;
//}
//
//int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
//  return 0;
//}
//
//int* findMinVerticalSeam(Pixel** image, int width, int height) {
//	
//	return nullptr;
//}
//
//int* findMinHorizontalSeam(Pixel** image, int width, int height) {
//  return nullptr;
//}
//
//void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
//}
//
//void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
//}
