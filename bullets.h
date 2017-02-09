#include "headers.h"

#ifndef BULLETS
#define BULLETS

class bullets {
private:
  VAO *bullet;
  static GLfloat vertex_buffer_data [];
  static GLfloat color_buffer_data [];
  float yCord;
  float xCord;
  float shootAngle;
  float rotationAngle;
  float magnitude;
  glm::mat4 referenceModelMatrix;
  glm::mat4 translationModelMatrix;
  glm::vec3 translationVector;
  glm::vec3 positionVector;

public:
  bullets(float angle, glm::mat4 cannonMatrix);
  static void basicShape();
  glm::vec3 getPositionVector();
  glm::vec3 gettranslationVector();
  void settranslationVector(glm::vec3 vectorDirection);
  void draw();
  float getShootAngle();
};

#endif
