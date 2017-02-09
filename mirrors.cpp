#include "mirrors.h"
#include "drawObjects.h"

mirrors::mirrors(float x, float y, float angle) {
  xCord = x;
  yCord = y;
  thi = 1;
  mirrorRotAngle = angle;
  const GLfloat vertex_buffer_data [] = {
    -0.1f,1.0f,0,     //vertex1
    -0.1f,-1.0f,0,    //vertex2
    0.1f,-1.0f,0,     //vertex3

    0.1f,-1.0f,0,     //vertex3
    -0.1f,1.0f,0,     //vertex1
    0.1f,1.0f,0       //vertex4
  };
  const GLfloat color_buffer_data [] = {
    1.0f,1.0f,1.0f,     //vertex1
    1.0f,1.0f,1.0f,     //vertex1
    0.0f,0.0f,0.0f,     //vertex3

    0.0f,0.0f,0.0f,     //vertex3
    1.0f,1.0f,1.0f,     //vertex1
    0.0f,0.0f,0.0f       //vertex4
  };
  glm::mat4 scale = glm::scale(glm::vec3(0.5f,0.8f,1));
  glm::mat4 rotate = glm::rotate((float)(mirrorRotAngle * M_PI/180.0f),glm::vec3(0,0,1));
  glm::mat4 translate = glm::translate (glm::vec3(xCord, yCord, 0));
  modelMatrix = translate * rotate * scale;
  positionVector  = glm::vec3(modelMatrix * glm::vec4(0.0,-1,0.0,1.0));
  positionVector2 = glm::vec3(modelMatrix * glm::vec4(0.0,1,0.0,1.0));
  circleRadius = sqrt(xCord*xCord + yCord*yCord);
  // cout << "Mirror1 x=" << positionVector.x << " y=" <<positionVector.y << " z=" << positionVector.z << endl;
  // cout << "Mirror1 x=" << positionVector2.x << " y=" <<positionVector2.y << " z=" << positionVector2.z << endl;
  mirror = drawObjects::create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data,GL_FILL);
}

float mirrors::getAngle() {
  return mirrorRotAngle;
}

glm::vec3 mirrors::getPositionVector() {
  return positionVector;
}

glm::vec3 mirrors::getPositionVector2() {
  return positionVector2;
}

void mirrors::draw() {
  glm::mat4 scale = glm::scale(glm::vec3(0.5f,0.8f,1));
  glm::mat4 rotate = glm::rotate((float)(mirrorRotAngle * M_PI/180.0f),glm::vec3(0,0,1));
  glm::mat4 translate = glm::translate (glm::vec3(xCord, yCord, 0));
  modelMatrix = translate * rotate * scale;

  xCord = circleRadius/2 * cos(thi * M_PI/180.0f);
  yCord = circleRadius/2 * sin(thi * M_PI/180.0f);
  positionVector  = glm::vec3(modelMatrix * glm::vec4(0.0f,-1.0f,0.0f,1.0f));
  positionVector2 = glm::vec3(modelMatrix * glm::vec4(0.0f,1.0f,0.0f,1.0f));
  thi = thi + 1;
  // thi = 70.0f;
  if(thi > 360) {
    thi = thi - 360;
  }
  // cout << thi << endl;
  glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view * modelMatrix;
  glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  drawObjects::draw3DObject(mirror);
}
