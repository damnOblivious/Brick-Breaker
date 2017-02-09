#include "cannon.h"
#include "headers.h"
#include "buckets.h"
#include "mirrors.h"
#include "bullets.h"
#include "blocks.h"
#include "basicSetup.h"
#include "reshapeWindow.h"
#include "camera.h"

#define BITS 8

double last_update_time, current_time,fire_time;
cannon *cannon1;
buckets *bucket1, *bucket2;
vector<buckets *> bucketsCollection;
mirrors * tempMirror;
vector<mirrors *> mirrorCollection;
bullets *tempBullet, *bullet;
vector<bullets *> bulletsCollection;
blocks *tempBlock, *block;
vector<blocks *> blocksCollection;

float radius = 0.10f;
float mirrorWidth = 0.10f;
float blockWidth = 0.10f;
float distanceLeft;
float product1,product2;
glm::vec3 normalSurface;
glm::vec3 reflectedSurface;

float x,y,x2,y2;
int color,score;
float maxlimit = 4.0f ,minlimit = -4.0f;
bool dropped,inBucket,shoot,gameOver;
bool ctrlButton,altButton;

float delay_time = 0.5f;
float bullet_delay_time = 0.0f;

double cursor_x, cursor_y,currentcursor_x, currentcursor_y,cannon_x,cannon_y;
int window_width = 600;
int selectedBucket, selectedCannon;
bool draggedPanning;

/*************************getting co-ordinates of cursor****************************/

void getOriginalCoordinates(GLFWwindow * window, double * x, double * y) {
  glfwGetCursorPos(window, x, y);
  *x = (*x)/window_width * 2 - 1.0f;
  *y =  1.0f - (*y)/window_width * 2;
  // cout << *x <<  " by * " << *y << endl;
  glm::vec3 v1 = glm::vec3(GLMatrices::Matrices.inverseVP * glm::vec4((float)(*x),(float)(*y),0.0f,1.0f));
  *x = v1.x;
  *y = v1.y;
  // cout << *x <<  " by 1*1 " << *y << endl;
}

/**********************eventHandler Functions********************************************/
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_RELEASE) {
    switch (key) {
      case GLFW_KEY_A:
      cannon1->rotateMuzzle(-1);
      break;
      case GLFW_KEY_D:
      cannon1->rotateMuzzle(1);
      break;
      case GLFW_KEY_F:
      cannon1->moveCannon(-0.1f);
      break;
      case GLFW_KEY_N:
      blocks::speedUp();
      delay_time = delay_time - 0.05f;
      break;
      case GLFW_KEY_M:
      blocks::speedDown();
      delay_time = delay_time + 0.05f;
      break;
      case GLFW_KEY_P:
      break;
      case GLFW_KEY_S:
      cannon1->moveCannon(0.1f);
      break;
      case GLFW_KEY_X:
      break;
      case GLFW_KEY_LEFT_CONTROL:
      case GLFW_KEY_RIGHT_CONTROL:
      ctrlButton = false;
      break;
      case GLFW_KEY_LEFT_ALT:
      case GLFW_KEY_RIGHT_ALT:
      altButton = false;
      break;

      case GLFW_KEY_LEFT:
      if(ctrlButton){
        bucketsCollection[0]->translate(-0.1f);
      }
      else if(altButton) {
          bucketsCollection[1]->translate(-0.1f);
      }
      break;

      case GLFW_KEY_RIGHT:
      if(ctrlButton){
          bucketsCollection[0]->translate(0.1f);
      }
      else if(altButton) {
          bucketsCollection[1]->translate(0.1f);
      }
      break;

      default:
      break;
    }
  }
  else if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
      basicSetup::quit(window);
      break;

      case GLFW_KEY_SPACE:
      if(current_time - fire_time >= bullet_delay_time) {
        fire_time = glfwGetTime();
        bulletsCollection.push_back(cannon1->fireBullet());
      }


      case GLFW_KEY_LEFT_CONTROL:
      case GLFW_KEY_RIGHT_CONTROL:
      ctrlButton = true;
      break;
      case GLFW_KEY_LEFT_ALT:
      case GLFW_KEY_RIGHT_ALT:
      altButton = true;
      break;

      default:
      break;
    }
  }
  else if (action == GLFW_REPEAT) {
    switch (key) {
      case GLFW_KEY_RIGHT:
      if(ctrlButton == false && altButton == false){
        camera::panAlongX(-0.1f);
      }
      break;
      case GLFW_KEY_LEFT:
      if(ctrlButton == false && altButton == false){
        camera::panAlongX(0.1f);
      }
      break;
      case GLFW_KEY_UP:
      reshapeWindow::zoom(-0.03f);
      break;
      case GLFW_KEY_DOWN:
      reshapeWindow::zoom(0.03f);
      break;
    }
  }
}

void mouseButton (GLFWwindow* window, int button, int action, int mods) {
  switch (button) {
    case GLFW_MOUSE_BUTTON_RIGHT:
    if(action == GLFW_PRESS) {
      getOriginalCoordinates(window, &cursor_x,	&cursor_y);
      draggedPanning = true;
    }
    if (action == GLFW_RELEASE){
      draggedPanning = false;
    }
    break;

    case GLFW_MOUSE_BUTTON_LEFT:

    getOriginalCoordinates(window, &cursor_x,	&cursor_y);
    if(action == GLFW_PRESS) {
      cannon_x = cannon1->getxCord();
      cannon_y = cannon1->getyCord();
      distanceLeft = sqrt((cannon_x - cursor_x)*(cannon_x - cursor_x) + (cannon_y - cursor_y)*(cannon_y - cursor_y));
      if( distanceLeft <= 0.5f) {
        cannon1->selected(true);
        selectedCannon = 1;
      }
      else if(cursor_y <= -3.0f) {
        for(auto bucket: bucketsCollection){
          x2 = bucket->getxCord();
          if((cursor_x <= x2 + 1.0f) && (cursor_x >= x2 - 1.0f)) {
            selectedBucket = bucket->getColor();
            bucket->selected(true);
            // cout << "selectedBucket" << selectedBucket << endl;
          }
        }
      }
    }
    else if (action == GLFW_RELEASE) {
      if(selectedBucket != -1) {      //if anything was selected
        bucketsCollection[selectedBucket-1]->selected(false);
        selectedBucket = -1;
      }
      else if(selectedCannon != -1){
        cannon1->selected(false);
        selectedCannon = -1;
      }
      else {
        cannon1->rotateMuzzleOnClick(cursor_x,cursor_y);
        if(current_time - fire_time >= bullet_delay_time) {
          fire_time = glfwGetTime();
          bulletsCollection.push_back(cannon1->fireBullet());
        }
        // cout << cursor_x << " " << cursor_y << endl;
      }
    }
    break;
    default:
    break;
  }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  reshapeWindow::zoom(0.03 * yoffset);
}
/**********************************************************************/


void checkDragging(GLFWwindow * window) {
  if(selectedBucket != -1) {
    getOriginalCoordinates(window, &currentcursor_x, &currentcursor_y);
    bucketsCollection[selectedBucket-1]->translate(currentcursor_x - cursor_x);
    getOriginalCoordinates(window, &cursor_x, &cursor_y);
  }
  else if(selectedCannon != -1) {
    getOriginalCoordinates(window, &currentcursor_x, &currentcursor_y);
    cannon1->moveCannon(currentcursor_y - cursor_y);
    getOriginalCoordinates(window, &cursor_x, &cursor_y);
  }
  else if(draggedPanning) {
    getOriginalCoordinates(window, &currentcursor_x, &currentcursor_y);
    camera::panAlongX(currentcursor_x - cursor_x);
    camera::panAlongY(currentcursor_y - cursor_y);
    getOriginalCoordinates(window, &cursor_x, &cursor_y);
  }
}


void checkCollisions() {
  for (__typeof((blocksCollection).begin()) i = (blocksCollection).begin(); i != (blocksCollection).end();) {
    block = (*i);
    x = block->getxCord();
    y = block->getyCord();
    color = block->getColor();
    shoot = false;
    inBucket = false;

    for(auto bullet: bulletsCollection) {
      glm::vec3 bulletCenter = bullet->getPositionVector();
      distanceLeft = sqrt((x - bulletCenter.x)*(x - bulletCenter.x) + (y - bulletCenter.y)*(y - bulletCenter.y));
      shoot = (shoot  || (distanceLeft <=  (blockWidth)/2 + radius + 0.1f));
    }
    if( shoot ) {
      switch (color) {
        case 1:
        case 2:
        score = score - 2;
        break;
        case 3:
        score = score + 2;
        break;
      }
      // cout << score << endl;
    }

    if(y <= (-3.0f + blockWidth)) {
      for(auto bucket: bucketsCollection){
        x2 = bucket->getxCord();
        if((x >= x2 - 1.0f) && (x <= x2 + 1.0f)) {
          inBucket = true;
          if(color == 3) {
            gameOver = true;
          }
          else if(color == bucket->getColor()) {
            score = score + 1;
            // cout << score << endl;
          }
        }
      }
    }
    dropped = (y < -4.0f);        //check if block has left screen
    if( dropped || shoot || inBucket) {
      blocksCollection.erase(i);
      continue;
    }
    ++i;
  }

  for (__typeof((bulletsCollection).begin()) i = (bulletsCollection).begin(); i != (bulletsCollection).end();){
    bullet = (*i);
    glm::vec3 bulletCenter = bullet->getPositionVector();

    if( abs(bulletCenter.x) > 3.9f || abs(bulletCenter.y) > 4.0f ){   //NOTE Important
      bulletsCollection.erase(i);
      continue;
    }

    for(auto mirror: mirrorCollection) {

      glm::vec3 mirrorLine1 = mirror->getPositionVector();
      glm::vec3 mirrorLine2 = mirror->getPositionVector2();
      glm::vec3 v1 = (bulletCenter - mirrorLine1);
      glm::vec3 v2 = (mirrorLine2 - mirrorLine1);
      glm::vec3 v3 = (bulletCenter - mirrorLine2);
      glm::vec3 v4 = (mirrorLine1 - mirrorLine2);
      distanceLeft = glm::length(glm::cross(v1,v2))/glm::length(v2);
      product1 = glm::dot(v1,v2);
      product2 = glm::dot(v3,v4);
      if(distanceLeft <= mirrorWidth/2 + radius) {       //check distance.
        if(product1 > 0 && product2 > 0) {            //check angle are acute.
          normalSurface = glm::vec3(-v4.y,v4.x,0.0f);
          // normalSurface.y = ;
          // normalSurface.z = ;
          glm::vec3 incidentRay = bullet->gettranslationVector();
          if(glm::dot(normalSurface,incidentRay) < 0) {
            continue;
          }
          normalSurface = glm::normalize(normalSurface);
          reflectedSurface = glm::reflect(incidentRay, normalSurface);
          bullet->settranslationVector(reflectedSurface);
        }
      }
    }
    i++;
  }
}

void displayObjects() {
  for(auto bucket: bucketsCollection){
    bucket->draw();
  }
  for(auto block: blocksCollection){
    block->draw();
  }
  for(auto mirror: mirrorCollection){
    mirror->draw();
  }
  for(auto bullet: bulletsCollection){
    bullet->draw();
  }
  cannon1->draw();
}

void throwBlock() {
  x = minlimit + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxlimit - minlimit)));
  color = rand() % 3 + 1;
  blocksCollection.push_back(new blocks(x,color));
  last_update_time = current_time;
}

int main()
{
  basicSetup setup;
  GLFWwindow* window = setup.initGLFW();
  score = 0;

  mpg123_handle *mh;
  unsigned char *buffer;
  size_t buffer_size;
  size_t done;
  int err;

  int driver;
  ao_device *dev;

  ao_sample_format format;
  int channels, encoding;
  long rate;

  /* initializations */
  ao_initialize();
  driver = ao_default_driver_id();
  mpg123_init();
  mh = mpg123_new(NULL, &err);
  buffer_size = 4096;
  buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

  /* open the file and get the decoding format */
  mpg123_open(mh, "godzilla.mp3");
  mpg123_getformat(mh, &rate, &channels, &encoding);

  /* set the output format and open the output device */
  format.bits = mpg123_encsize(encoding) * BITS;
  format.rate = rate;
  format.channels = channels;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;
  dev = ao_open_live(driver, &format, NULL);

  cannon1 = new cannon();
  bucketsCollection.push_back(new buckets(1));
  bucketsCollection.push_back(new buckets(2));
  mirrorCollection.push_back(new mirrors(1,0,-45));
  mirrorCollection.push_back(new mirrors(-2.5,2.5,135));
  // mirrorCollection.push_back(new mirrors(2.5,3.5,0));
  // mirrorCollection.push_back(new mirrors(2.5,3.5,0));
  // mirrorCollection.push_back(new mirrors(2,1.5,0));
  // mirrorCollection.push_back(new mirrors(-2.5,-1.5,0));

  bucketsCollection[0]->translate(2);
  bucketsCollection[1]->translate(-2);

  setup.initGL(window);
  last_update_time = glfwGetTime();
  ctrlButton = false;
  altButton = false;
  gameOver = false;
  draggedPanning = false;
  selectedBucket = -1;
  selectedCannon = -1;
  fire_time = glfwGetTime();
  while(gameOver == false){

    if (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
      ao_play(dev, (char *)buffer, done);
    }
    else {
      mpg123_seek(mh, 0, SEEK_SET); // loop audio from start again if ended
    }

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    current_time = glfwGetTime();
    if ((current_time - last_update_time) >= delay_time) {
      throwBlock();
    }
    checkCollisions();
    checkDragging(window);
    displayObjects();
    glfwSwapBuffers(window);
    glfwPollEvents();
  };
  free(buffer);

  /* clean up */
  ao_close(dev);
  mpg123_close(mh);
  mpg123_delete(mh);
  mpg123_exit();
  ao_shutdown();

  cout << "Game Over" << endl << "Your Score:" << score << endl;
  glfwTerminate();
  exit(0);
}
