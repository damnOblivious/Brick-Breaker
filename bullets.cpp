#include "bullets.h"
#include "cannon.h"
#include "drawObjects.h"

GLfloat bullets::vertex_buffer_data []= {
    0,0,0,
    0,1,0,
    cos(M_PI/6.0f),cos(M_PI/3.0f),0,

    0,0,0,
    0,-1,0,
    0.866,-0.5,0,

    0,0,0,
    -0.866,-0.5,0,
    -0.866,0.5,0
};
GLfloat bullets::color_buffer_data []= {
  1,1,1,
  1,1,1,
  1,1,1,
  1,1,1,
  1,1,1,
  1,1,1,
  1,1,1,
  1,1,1,
  1,1,1
};

bullets::bullets(float angle, glm::mat4 cannonMatrix):shootAngle(angle),referenceModelMatrix(cannonMatrix) {
  rotationAngle = 0;
  magnitude = 0.1f;
  translationModelMatrix = glm::mat4(1.0f);
  translationVector = 0.1f * glm::vec3((float)(cos(shootAngle*M_PI/180.f)),(float)(sin(shootAngle*M_PI/180.f)),0);
  bullet = drawObjects::create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color_buffer_data, GL_FILL);
  positionVector = glm::vec3(cannonMatrix * glm::vec4(0.0f,0.0f,0.0f,1.0f));
}

glm::vec3 bullets::gettranslationVector() {
    return translationVector;
}

float bullets::getShootAngle() {
    return translationVector.x;
}

void bullets::settranslationVector(glm::vec3 vectorDirection) {
  translationVector = vectorDirection;
}

glm::vec3 bullets::getPositionVector() {
    return positionVector;
}

void bullets::draw() {
  glm::mat4 scale = glm::scale(glm::vec3(0.10f,0.10f,0));
  translationModelMatrix = translationModelMatrix * glm::translate(translationVector);
  glm::mat4 rotate = glm::rotate((float)(rotationAngle*M_PI/180.0f),glm::vec3(0,0,1));
  GLMatrices::Matrices.model = translationModelMatrix * referenceModelMatrix * rotate * scale;

  positionVector = glm::vec3(GLMatrices::Matrices.model * glm::vec4(0,0,0,1));
  glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view * GLMatrices::Matrices.model;

  glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  drawObjects::draw3DObject(bullet);

  rotationAngle = rotationAngle + 20.0f;
}
