#include "headers.h"

#ifndef DRAW_OBJECT
#define DRAW_OBJECT

class drawObjects {
public:
  static VAO* create3DObject(GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* color_buffer_data, GLenum fill_mode);
  static void draw3DObject(struct VAO* vao);
};

#endif
