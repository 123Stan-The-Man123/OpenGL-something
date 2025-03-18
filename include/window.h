#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

GLFWwindow *init_window(int width, int height, const char *title);

void processInput(GLFWwindow *window, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp, float deltaTime);
