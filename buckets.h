#include "headers.h"

#ifndef BUCKETS
#define BUCKETS

class buckets {
private:
  VAO *bucket,*bucket1;
  float xCord;
  float yCord;
  int color;
  bool highlight;

public:
  buckets(int randColor);
  void draw();
  void translate(float displacement);
  int getColor();
  float getxCord();
  void selected(bool b);
};

#endif
