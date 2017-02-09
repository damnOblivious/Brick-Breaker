#include "buckets.h"
#include "drawObjects.h"

buckets::buckets(int randColor){
  xCord = 0.0;
  yCord = -3.5;
  color = randColor;
  vector<GLfloat> colorVec;
  highlight = false;
  GLfloat vertex_buffer_data [] = {
    -2,1,0, // vertex 1
    -1,-1,0, // vertex 2
    1,-1,0, // vertex 3

    1,-1,0, // vertex 3
    2,1,0, // vertex 4
    -2,1,0  // vertex 1
  };

  if(randColor == 1) {
    colorVec  = {1,0,0};
  }
  else if(randColor == 2) {
    colorVec  = {0,1,0};
  }

  GLfloat color_buffer_data[18];
  for(int i = 0; i < 18 ; ++i){
    color_buffer_data[i] = colorVec[i%3];
  }
  bucket = drawObjects::create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);

  colorVec[0] = 0;
  colorVec[1] = 0;
  colorVec[2] = 0;
  for(int i = 0; i < 18 ; ++i){
    color_buffer_data[i] = colorVec[i%3];
  }
  bucket1 = drawObjects::create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void buckets::selected(bool b) {
  highlight = b;
  // cout << "highlight" << highlight << endl;
}


int buckets::getColor() {
  return color;
}

float buckets::getxCord() {
  return xCord;
}

void buckets::draw(){
  GLMatrices::Matrices.model = glm::mat4(1.0f);
  glm::mat4 scaling = glm::scale(glm::vec3(0.5f,0.5f,1.0f));
  glm::mat4 translate = glm::translate (glm::vec3(xCord, yCord, 0));
  GLMatrices::Matrices.model = translate * scaling;
  glm::mat4 MVP = GLMatrices::Matrices.projection * GLMatrices::Matrices.view *GLMatrices::Matrices.model  ;
  glUniformMatrix4fv(GLMatrices::Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  if(highlight) {
    drawObjects::draw3DObject(bucket1);
  }
  else {
    drawObjects::draw3DObject(bucket);
  }
}

void buckets::translate(float displacement){
  if(abs( xCord + displacement) < 3){
    xCord = xCord + displacement; //put a check on boundaries
  }
}
