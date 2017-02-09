#include "headers.h"

#ifndef EVENTHANDLER
#define EVENTHANDLER

class eventHandler{
public:
  static void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods);
  static void keyboardChar (GLFWwindow* window, unsigned int key);
  static void mouseButton (GLFWwindow* window, int button, int action, int mods);
};

#endif
