#include <glad/glad.h>
#include <stdbool.h>
#include <stdio.h>

#include "stb_image.h"

unsigned int create_texture(const char *filepath, GLenum tex_unit, GLenum format);
