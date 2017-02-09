#include "basicSetup.h"
#include "eventHandler.h"
#include "cannon.h"

void eventHandler::keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // Function is called first on GLFW_PRESS.
  if (action == GLFW_RELEASE) {
    switch (key) {
      // case GLFW_KEY_A:
      // cannon::rotateMuzzle(-1);
      // break;
      case GLFW_KEY_S:
      break;
      case GLFW_KEY_D:
      break;
      case GLFW_KEY_F:
      break;
      case GLFW_KEY_P:
      break;
      case GLFW_KEY_X:
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
      default:
      break;
    }
  }
}

/* Executed for character input (like in text boxes) */
void eventHandler::keyboardChar (GLFWwindow* window, unsigned int key)
{
  switch (key) {
    case 'Q':
    case 'q':
    basicSetup::quit(window);
    break;
    default:
    break;
  }
}

void eventHandler::mouseButton (GLFWwindow* window, int button, int action, int mods)
{
  switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
    if (action == GLFW_RELEASE){
      // basicSetup::quit(window);
    }
    break;
    case GLFW_MOUSE_BUTTON_RIGHT:
    if (action == GLFW_RELEASE) {
    }
    break;
    default:
    break;
  }
}
