#include "cannon.h"
#include "drawObjects.h"
#include "bullets.h"

cannon::cannon() {
  xCord = -3.9;
  yCord = 0;
  muzzleRotAngle = 270;
  shootAngle = 0;
  highlight = false;
  rotationMagnitude = 5;

  const GLfloat base_vertex_buffer_data [] = {
    0.0f,0.5f,0,
    0.5f,0,0,
    -0.5f,0,0
  };
  vector<GLfloat> colorVec = {1,1,1};
  GLfloat base_color_buffer_data[9];
  for(int i = 0; i < 9 ; ++i){
    base_color_buffer_data[i] = colorVec[i%3];
  }
  base = drawObjects::create3DObject(GL_TRIANGLES, 3, base_vertex_buffer_data, base_color_buffer_data, GL_FILL);

  colorVec[0] = 0;
  colorVec[1] = 0;
  colorVec[2] = 0;
  for(int i = 0; i < 9 ; ++i){
    base_color_buffer_data[i] = colorVec[i%3];
  }
  base1 = drawObjects::create3DObject(GL_TRIANGLES, 3, base_vertex_buffer_data, base_color_buffer_data, GL_FILL);
}

void cannon::selected(bool b) {
  highlight = b;
}


void cannon::draw() {
  glm::mat4 translate = glm::translate(glm::vec3(xCord, yCord, 0));
  for(int i = 1 ; i <= 3 ; ++i) {
    glm::mat4 rotate = glm::rotate((float)((muzzleRotAngle + (i-2)*10)*M_PI/180.0f),glm::vec3(0,0,1));
    GLMatrices::Matrices.model = translate * rotate;
    modelMatrix = GLMatrices::Matrices.model;
    glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view * GLMatrices::Matrices.model;
    glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(highlight) {
      drawObjects::draw3DObject(base1);
    }
    else {
      drawObjects::draw3DObject(base);
    }
  }
}

void cannon::rotateMuzzle(float deltaAngle) {
  if(abs(shootAngle + deltaAngle*rotationMagnitude) <= 45){
    muzzleRotAngle = muzzleRotAngle + deltaAngle*rotationMagnitude;
    shootAngle = shootAngle + deltaAngle*rotationMagnitude;
  }
}

void cannon::rotateMuzzleOnClick(float x, float y) {
  // cout <<  "shot and muzzle angke" << shootAngle << " " << muzzleRotAngle << endl;
  x = x- xCord;
  y = y - yCord;
  muzzleRotAngle = (270.0f + atan2 (y,x) * 180 / M_PI);
  if(muzzleRotAngle > 360) {
    muzzleRotAngle = muzzleRotAngle - 360;
  }
  shootAngle = (atan2 (y,x) * 180 / M_PI);
}


void cannon::moveCannon(float displacement) {
  if(abs(yCord + displacement)<3){
    yCord = yCord + displacement;
  }
}

bullets * cannon::fireBullet() {
  bullets * bullet;
  return bullet = new bullets(shootAngle, modelMatrix);
}

float cannon::getxCord() {
  return xCord;
}
float cannon::getyCord() {
  return yCord;
}
