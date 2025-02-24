#include "transform.h"

void apply_translation(mat4 mat, float x, float y, float z) {
    glm_translate(mat, (vec3){x, y, z});
}

void apply_rotation(mat4 mat, float angle, float x, float y, float z) {
    vec3 axis = {x, y, z};
    glm_rotate(mat, angle, axis);
}

void apply_scaling(mat4 mat, float sx, float sy, float sz) {
    glm_scale(mat, (vec3){sx, sy, sz});
}
