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
    delete [] image;
    return nullptr;
  }



  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {

      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;

  for (int i=0; i<width; ++i) {
    delete [] image[i];
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  int* seam = new int[length] {};
  for(int i = 0; i < length; i++){
    seam[i] = 0;
  }
  return seam;
}

void deleteSeam(int* seam) {
  delete [] seam;
  seam = nullptr;
}

bool loadImage(string filename, Pixel** image, int width, int height) {

  ifstream ifs (filename);


  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }


  char type[3];
  ifs >> type;
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) {
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }


  int w = 0, h = 0;
  ifs >> w >> h;
  if(ifs.fail() >> w){
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if(ifs.fail() >> h){
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (w != width) {
    cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
    return false;
  }
  if (h != height) {
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;
    return false;
  }


  int colorMax {};
  ifs >> colorMax;
  if(ifs.fail() >> colorMax){
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (colorMax != 255) {
    cout << "Error: invalid color value " << colorMax << endl;
    return false;
  }


  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      Pixel value;
      ifs >> value.r >> value.g >> value.b;
      if((value.r < 0) || (value.r > 255)){
        cout << "Error: invalid color value " << value.r << endl;
        return false;
      }
      if((value.g < 0) || (value.g > 255)){
        cout << "Error: invalid color value " << value.g << endl;
        return false;
      }
      if((value.b < 0) || (value.b > 255)){
        cout << "Error: invalid color value " << value.b << endl;
        return false;
      }
      if((ifs.fail() >> value.r) && (ifs.eof())){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if(ifs.fail() >> value.r){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if((ifs.fail() >> value.b) && (ifs.eof())){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if(ifs.fail() >> value.b){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if((ifs.fail() >> value.g) && (ifs.eof())){
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if(ifs.fail() >> value.g){
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      image[j][i] = value;
    }
  }
  Pixel value;
  ifs >> value.r >> value.g >> value.b;
  if((value.r > 0)){
    cout << "Error: too many color values" << endl;
    return false;
  }
  if((value.g > 0)){
    cout << "Error: too many color values" << endl;
    return false;
  }
  if((value.b > 0)){
    cout << "Error: too many color values" << endl;
    return false;
  }

  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
  ofstream ofs(filename);


  if(!ofs.is_open()){
    cout << "Error: failed to open output file " << filename << endl;
    return false;
  }


  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << "255" << endl;


  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      Pixel value = image[j][i];
      ofs << value.r << endl;
      ofs << value.g << endl;
      ofs << value.b << endl;
    }
  }
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) {
  Pixel value;
  int energy_value_x {};
  int energy_value_y {};
  int total_energy {};
  int width_edge = width - 1;
  int height_edge = height - 1;

  if((x == width_edge) && (y == height_edge)){
    energy_value_x = (pow((image[0][y].r - image[x-1][y].r), 2.0) + pow((image[0][y].g - image[x-1][y].g), 2.0) + pow((image[0][y].b - image[x-1][y].b), 2.0));
    energy_value_y = (pow((image[x][0].r - image[x][y-1].r), 2.0) + pow((image[x][0].g - image[x][y-1].g), 2.0) + pow((image[x][0].b - image[x][y-1].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }

  else if((x == width_edge) && (y == 0)){
    energy_value_x = (pow((image[0][y].r - image[x-1][y].r), 2.0) + pow((image[0][y].g - image[x-1][y].g), 2.0) + pow((image[0][y].b - image[x-1][y].b), 2.0));
    energy_value_y = (pow((image[x][y+1].r - image[x][height_edge].r), 2.0) + pow((image[x][y+1].g - image[x][height_edge].g), 2.0) + pow((image[x][y+1].b - image[x][height_edge].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }

  else if((x == 0) && (y == height_edge)){
    energy_value_x = (pow((image[x+1][y].r - image[width_edge][y].r), 2.0) + pow((image[x+1][y].g - image[width_edge][y].g), 2.0) + pow((image[x+1][y].b - image[width_edge][y].b), 2.0));
    energy_value_y = (pow((image[x][0].r - image[x][y-1].r), 2.0) + pow((image[x][0].g - image[x][y-1].g), 2.0) + pow((image[x][0].b - image[x][y-1].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }


  else if((x == 0) && (y == 0)){
    energy_value_x = (pow((image[x+1][y].r - image[width_edge][y].r), 2.0) + pow((image[x+1][y].g - image[width_edge][y].g), 2.0) + pow((image[x+1][y].b - image[width_edge][y].b), 2.0));
    energy_value_y = (pow((image[x][y+1].r - image[x][height_edge].r), 2.0) + pow((image[x][y+1].g - image[x][height_edge].g), 2.0) + pow((image[x][y+1].b - image[x][height_edge].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }


  else if((x == width_edge) && (y > 0)){
    energy_value_x = (pow((image[0][y].r - image[x-1][y].r), 2.0) + pow((image[0][y].g - image[x-1][y].g), 2.0) + pow((image[0][y].b - image[x-1][y].b), 2.0));
    energy_value_y = (pow((image[x][y+1].r - image[x][y-1].r), 2.0) + pow((image[x][y+1].g - image[x][y-1].g), 2.0) + pow((image[x][y+1].b - image[x][y-1].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }


  else if((y == height_edge) && (x > 0)){
    energy_value_x = (pow((image[x+1][y].r - image[x-1][y].r), 2.0) + pow((image[x+1][y].g - image[x-1][y].g), 2.0) + pow((image[x+1][y].b - image[x-1][y].b), 2.0));
    energy_value_y = (pow((image[x][0].r - image[x][y-1].r), 2.0) + pow((image[x][0].g - image[x][y-1].g), 2.0) + pow((image[x][0].b - image[x][y-1].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }


  else if((y >= 1) && (x == 0) && (x < (width)) && (y < (height))){
    int end_col = width-1;
    energy_value_x = (pow((image[x+1][y].r - image[end_col][y].r), 2.0) + pow((image[x+1][y].g - image[end_col][y].g), 2.0) + pow((image[x+1][y].b - image[end_col][y].b), 2.0));
    energy_value_y = (pow((image[x][y+1].r - image[x][y-1].r), 2.0) + pow((image[x][y+1].g - image[x][y-1].g), 2.0) + pow((image[x][y+1].b - image[x][y-1].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }


  else if((y == 0) && (x >= 1) && (x < (width)) && (y < (height))){
    int end_row = height-1;
    energy_value_x = (pow((image[x+1][y].r - image[x-1][y].r), 2.0) + pow((image[x+1][y].g - image[x-1][y].g), 2.0) + pow((image[x+1][y].b - image[x-1][y].b), 2.0));
    energy_value_y = (pow((image[x][y+1].r - image[x][end_row].r), 2.0) + pow((image[x][y+1].g - image[x][end_row].g), 2.0) + pow((image[x][y+1].b - image[x][end_row].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }


  else{
    energy_value_x = (pow((image[x+1][y].r - image[x-1][y].r), 2.0) + pow((image[x+1][y].g - image[x-1][y].g), 2.0) + pow((image[x+1][y].b - image[x-1][y].b), 2.0));
    energy_value_y = (pow((image[x][y+1].r - image[x][y-1].r), 2.0) + pow((image[x][y+1].g - image[x][y-1].g), 2.0) + pow((image[x][y+1].b - image[x][y-1].b), 2.0));
    total_energy = energy_value_x + energy_value_y;
  }

  return total_energy;
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {

  int total_energy_seam {};
  seam[0] = start_col;
  int x = start_col;
  int y = 0;
  total_energy_seam = energy(image,x,y,width,height);

  for(int i = 1; i < (height); i++){
    y+=1;


    if(x == 0){
      if((energy(image,x,y,width,height) > energy(image,x+1,y,width,height))){
        total_energy_seam += energy(image,x+1,y,width,height);
        x += 1;
      }
      else if((energy(image,x,y,width,height) <= energy(image,x+1,y,width,height))){
        total_energy_seam += energy(image,x,y,width,height);
      }
    }

    else if(x == (width-1)){
      if((energy(image,x,y,width,height) > energy(image,x-1,y,width,height))){
        total_energy_seam += energy(image,x-1,y,width,height);
        x -= 1;
      }
      else if((energy(image,x,y,width,height) <= energy(image,x-1,y,width,height))){
        total_energy_seam += energy(image,x,y,width,height);
      }
    }

    else{

      if((energy(image,x,y,width,height) <= energy(image,x+1,y,width,height)) && (energy(image,x,y,width,height) <= energy(image,x-1,y,width,height))){
        total_energy_seam += energy(image,x,y,width,height);
      }

      else if((energy(image,x,y,width,height) >= energy(image,x+1,y,width,height)) && (energy(image,x-1,y,width,height) >= energy(image,x+1,y,width,height))){
        total_energy_seam += energy(image,x+1,y,width,height);
        x += 1;
      }

      else{
        total_energy_seam += energy(image,x-1,y,width,height);
        x -= 1;
      }
    }
    seam[i] = x;
  }
  return total_energy_seam;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {

  int total_energy_seam {};
  seam[0] = start_row;
  int x = 0;
  int y = start_row;
  total_energy_seam = energy(image,x,y,width,height);

  for(int i = 1; i < (width); i++){
    x+=1;

    if(y == 0){
      if((energy(image,x,y,width,height) > energy(image,x,y+1,width,height))){
        total_energy_seam += energy(image,x,y+1,width,height);
        y += 1;
      }
      else if((energy(image,x,y,width,height) <= energy(image,x,y+1,width,height))){
        total_energy_seam += energy(image,x,y,width,height);
      }
    }

    else if(y == (height-1)){
      if((energy(image,x,y,width,height) > energy(image,x,y-1,width,height))){
        total_energy_seam += energy(image,x,y-1,width,height);
        y -= 1;
      }
      else if((energy(image,x,y,width,height) <= energy(image,x,y-1,width,height))){
        total_energy_seam += energy(image,x,y,width,height);
      }
    }

    else{

      if((energy(image,x,y,width,height) <= energy(image,x,y+1,width,height)) && (energy(image,x,y,width,height) <= energy(image,x,y-1,width,height))){
        total_energy_seam += energy(image,x,y,width,height);
      }

      else if((energy(image,x,y,width,height) >= energy(image,x,y-1,width,height)) && (energy(image,x,y+1,width,height) >= energy(image,x,y-1,width,height))){
        total_energy_seam += energy(image,x,y-1,width,height);
        y -= 1;
      }

      else{
        total_energy_seam += energy(image,x,y+1,width,height);
        y += 1;
      }
    }
    seam[i] = y;
  }
  return total_energy_seam;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int* min_seam = createSeam(height);
  int* candidate_seam = createSeam(height);

  int minimum_energy = loadVerticalSeam(image,0,width,height,min_seam);
  int candidate_energy = 0;
  int* pointer_store = nullptr;

  for(int i = 1; i < width; i++){

    candidate_energy = loadVerticalSeam(image,i,width,height,candidate_seam);
    if(minimum_energy > candidate_energy){
      minimum_energy = candidate_energy;

      pointer_store = min_seam;
      min_seam = candidate_seam;
      candidate_seam = pointer_store;

      pointer_store = nullptr;
    }
  }

  deleteSeam(candidate_seam);

  return min_seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {

  int* min_seam = createSeam(width);
  int* candidate_seam = createSeam(width);

  int minimum_energy = loadHorizontalSeam(image,0,width,height,min_seam);
  int candidate_energy = 0;
  int* pointer_store = nullptr;

  for(int i = 1; i < height; i++){
    candidate_energy = loadHorizontalSeam(image,i,width,height,candidate_seam);
    if(minimum_energy > candidate_energy){
      minimum_energy = candidate_energy;

      pointer_store = min_seam;
      min_seam = candidate_seam;

      candidate_seam = pointer_store;

      pointer_store = nullptr;
    }
  }

  deleteSeam(candidate_seam);

  return min_seam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  int last_column = width-1;
  int red;
  int green;
  int blue;
  for(int i = 0; i < height; i++){

    red = image[verticalSeam[i]][i].r;
    green = image[verticalSeam[i]][i].g;
    blue = image[verticalSeam[i]][i].b;

    for(int j = verticalSeam[i]; j < last_column; j++){
      image[j][i] = image[j+1][i];
    }

    image[last_column][i].r = red;
    image[last_column][i].g = green;
    image[last_column][i].b = blue;
  }
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  int last_row = height-1;
  int red;
  int green;
  int blue;
  for(int i = 0; i < width; i++){
    red = image[i][horizontalSeam[i]].r;
    green = image[i][horizontalSeam[i]].g;
    blue = image[i][horizontalSeam[i]].b;
    for(int j = horizontalSeam[i]; j < last_row; j++){
      image[i][j] = image[i][j+1];
    }
    image[i][last_row].r = red;
    image[i][last_row].g = green;
    image[i][last_row].b = blue;
  }
}
