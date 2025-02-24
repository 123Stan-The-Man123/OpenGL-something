#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <cglm/cam.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "window.h"

int main(void) {
    GLFWwindow *window = init_window(800, 600, "Test"); 
    float vertices[] = {
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };
    
    unsigned int indices [] = {
        0, 1, 2,
        0, 2, 3
    };
    
    unsigned int VAO = create_vertex_array(vertices, sizeof(vertices), indices, sizeof(indices), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int shaderProgram = create_shader_program("./shaders/vertex_shader.vert", "./shaders/fragment_shader.frag");
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

    unsigned int containerTexture = create_texture("./textures/container.jpg", GL_TEXTURE0, GL_RGB);
    unsigned int awesomeFaceTexture = create_texture("./textures/awesomeface.png", GL_TEXTURE1, GL_RGBA);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* float timeValue = glfwGetTime();
        float value = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, value, value, 1.0f, 1.0f);*/

        mat4 trans;
        glm_mat4_identity(trans);
        apply_translation(trans, 0.2f, 0.3f, 0.0f);
        apply_rotation(trans, (float)glfwGetTime(), 0.0f, 0.0f, 1.0f);

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (const GLfloat *)trans);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomeFaceTexture);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
