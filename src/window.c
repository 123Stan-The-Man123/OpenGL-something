#include <glad/glad.h>
#include <stdbool.h>
#include <stdio.h>

#include "callback.h"
#include "window.h"

GLFWwindow *init_window(int width, int height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    if (window == NULL) {
        puts("Failed to create GLFW window.");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwFocusWindow(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        puts("Failed to initialize GLAD.");
        return NULL;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    return window;
}

void processInput(GLFWwindow *window, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp, float deltaTime) {
    const float cameraSpeed = 2.5f * deltaTime;
    vec3 temp;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        glm_vec3_scale(cameraFront, cameraSpeed, temp);
        glm_vec3_add(cameraPos, temp, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        glm_vec3_scale(cameraFront, cameraSpeed, temp);
        glm_vec3_sub(cameraPos, temp, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glm_vec3_cross(cameraFront, cameraUp, temp);
        glm_vec3_normalize(temp);
        glm_vec3_scale(temp, cameraSpeed, temp);
        glm_vec3_sub(cameraPos, temp, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm_vec3_cross(cameraFront, cameraUp, temp);
        glm_vec3_normalize(temp);
        glm_vec3_scale(temp, cameraSpeed, temp);
        glm_vec3_add(cameraPos, temp, cameraPos);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
