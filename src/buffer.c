#include "buffer.h"

unsigned int create_vertex_array(float *vertices, size_t vertex_size, unsigned int *indices, size_t index_size, GLenum drawType, GLuint attribIndex) {
    unsigned int VAO, VBO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_size, vertices, drawType);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, indices, drawType);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(attribIndex);
    
    glBindVertexArray(0);

    return VAO;
}
