#include "headers.h"

#ifndef MIRRORS
#define MIRRORS

class mirrors {
private:
  VAO *mirror;
  float yCord;
  float xCord;
  float circleRadius;
  float thi;
  float mirrorRotAngle;
  glm::mat4 modelMatrix;
  glm::vec3 positionVector;
  glm::vec3 positionVector2;

public:
  mirrors(float=0, float=0, float=45);
  glm::vec3 getPositionVector();
  glm::vec3 getPositionVector2();
  float getAngle();
  void draw();
};

#endif
