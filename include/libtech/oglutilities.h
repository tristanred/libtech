#include "libtech.h"

#ifdef LIBTECH_BUILD_OPENGL

#include <GLFW/glfw3.h>
#include <glad/glad.h>

LIBTECH_API GLuint create_default_shaders();
LIBTECH_API const char* get_default_vertex_shader();
LIBTECH_API const char* get_default_fragment_shader();

#endif