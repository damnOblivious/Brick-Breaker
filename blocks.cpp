#include "blocks.h"
#include "drawObjects.h"

float blocks::speed = 0.01f;
blocks::blocks(float x, int randColor) {
  xCord = x;
  yCord = 3.5;
  color = randColor;
  vector<GLfloat> colorVec;
  const GLfloat vertex_buffer_data [] = {
    -1,1,0,
    -1,-1,0,
    1,-1,0,
    1,-1,0,
    -1,1,0,
    1,1,0
  };

  if(randColor == 1) {
    colorVec  = {1,0,0};
  }
  else if(randColor == 2) {
    colorVec  = {0,1,0};
  }
  else if(randColor == 3) {
    colorVec  = {0,0,0};
  }
  else {
    colorVec  = {1,1,1};
  }

  vector<GLfloat> color_buffer_data;
  for(int i = 0; i < 6 ; ++i){
    color_buffer_data.insert(color_buffer_data.end(), colorVec.begin() , colorVec.end());
  }

  // create3DObject creates and returns a handle to a VAO that can be used later
  block = drawObjects::create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, &color_buffer_data[0], GL_FILL);
}

float blocks::getxCord() {
  return xCord;
}
float blocks::getyCord() {
  return yCord;
}
void blocks::speedUp() {
  if(speed < 0.2f)
    speed = speed + 0.01f;
}
void blocks::speedDown() {
  if(speed > 0.01f)
    speed = speed - 0.01f;
}
int blocks::getColor() {
  return color;
}

void blocks::draw() {
  GLMatrices::Matrices.model = glm::mat4(1.0f);
  glm::mat4 scaling = glm::scale(glm::vec3(0.1f,0.1f,1.0f));
  glm::mat4 translate = glm::translate (glm::vec3(xCord, yCord, 0));
  GLMatrices::Matrices.model = translate * scaling;
  glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view *GLMatrices::Matrices.model  ;
  glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  drawObjects::draw3DObject(block);
  yCord = yCord - speed;
}
