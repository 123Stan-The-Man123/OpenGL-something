#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "window.h"
#include "buffer.h"
#include "shader.h"

int main(void) {
    GLFWwindow *window = init_window(800, 600, "Test"); 
    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    
    unsigned int indices [] = {
        0, 1, 3,
        1, 2, 3
    };
    
    unsigned int VAO = create_vertex_array(vertices, sizeof(vertices), indices, sizeof(indices), GL_STATIC_DRAW, 0);

    unsigned int shaderProgram = create_shader_program("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
