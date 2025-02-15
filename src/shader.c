#include <stdio.h>
#include <stdlib.h>

#include <shader.h>

char *read_shader_source(const char *filename) {
    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Failed to open shader source.");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *shader = malloc(sizeof(char) * (length + 1));
    fread(shader, 1, length, file);
    shader[length] = '\0';
    return shader;
}

unsigned int compile_shader(const char *path, GLenum shaderType) {
    char *shaderSource = read_shader_source(path);
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const char * const *)&shaderSource, NULL);
    glCompileShader(shader);
    free(shaderSource);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("%s\n", infoLog);
        return -1;
    }

    return shader;
}

unsigned int create_shader_program(const char *vertexPath, const char *fragmentPath) {
    unsigned int vertexShader = compile_shader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compile_shader(fragmentPath, GL_FRAGMENT_SHADER);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("%s\n", infoLog);
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
