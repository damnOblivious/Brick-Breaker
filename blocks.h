#include "headers.h"

#ifndef BLOCKS
#define BLOCKS

class blocks {
private:
  VAO* block;
  float xCord;
  float yCord;
  int color;
  static float speed;
  // int blockAdded;

public:
  blocks(float,int);
  void draw();
  void translate(int displacement);
  float getxCord();
  float getyCord();
  int getColor();
  static void speedUp();
  static void speedDown();
};

#endif
