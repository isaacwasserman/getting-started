// Aline Normoyle, 2020
//
// For documentation about this code, see the glfw3 quick start guide
//   https://www.glfw.org/docs/3.3/quick.html

#include "AGL.h"
#include "AGLM.h"
#include <cmath>

double cursor_xpos = 0.0;
double cursor_ypos = 0.0;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
   }
}

static void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
   cursor_xpos = xpos;
   cursor_ypos = ypos;
}

int main(int argc, char** argv)
{
  GLFWwindow* window;

  if ( !glfwInit() )
  {
     return -1;
  }

#ifdef __APPLE__
  // Explicitly ask for a 4.0 context on OS X 
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow( 1280, 720, "Hello World", NULL, NULL );
  if (!window)
  {
     glfwTerminate();
     return -1;
  }

  // Make the window's context current 
  glfwMakeContextCurrent(window);

  // Tell GLFW to call our callback fun when a key is pressed
  glfwSetKeyCallback(window, key_callback);

  // Tell GLFW to call our callback fun when the mouse moves
  glfwSetCursorPosCallback(window, cursor_callback);

  int window_width, window_height;

  // Loop until the user closes the window 
  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

    // Animate the screen color as a test
    double time = glfwGetTime();

    
    glfwGetWindowSize(window, &window_width, &window_height);
    double red = (sin(M_PI * cursor_xpos / window_width) + 1) * 0.5; // map sin value [-1,1] to color value [0,1]
    double green = (sin(time) + 1) * 0.5; // map sin value [-1,1] to color value [0,1]
    double blue = (sin(M_PI * cursor_ypos / window_height) + 1) * 0.5; // map cos value [-1,1] to color value [0,1]

    // Create a vector to test glm
    glm::vec3 color(red, green, blue);
    glClearColor(color.x, color.y, color.z, 1.0);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

