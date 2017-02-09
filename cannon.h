#include "headers.h"
#include "bullets.h"
#ifndef CANNON
#define CANNON

class cannon {
private:
  VAO *base, *base1, *muzzle, *bullet;
  float yCord;
  float xCord;
  float muzzleRotAngle;
  float shootAngle;
  float rotationMagnitude;
  glm::mat4 modelMatrix;
  bool highlight;

public:
  cannon();
  void draw();
  bullets * fireBullet();
  void rotateMuzzle(float deltaAngle);
  void moveCannon(float displacement);
  void rotateMuzzleOnClick(float x, float y);
  float getxCord();
  float getyCord();
  void selected(bool b);
};

#endif
