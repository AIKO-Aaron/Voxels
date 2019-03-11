#define PI 3.14159265358979323

mat4 rotate_x(float angle) {
    return transpose(mat4(1, 0, 0, 0,
                0, cos(angle), sin(angle), 0,
                0, -sin(angle), cos(angle), 0,
                0, 0, 0, 1));
}

mat4 rotate_y(float angle) {
    return transpose(mat4(cos(angle), 0, sin(angle), 0,
                          0, 1, 0, 0,
                          -sin(angle), 0, cos(angle), 0,
                          0, 0, 0, 1));
}

mat4 rotate_z(float angle) {
    return transpose(mat4(cos(angle), sin(angle), 0, 0,
                          -sin(angle), cos(angle), 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1));
}

mat4 translate(vec3 dir) {
    return transpose(mat4(1, 0, 0, dir.x,
                          0, 1, 0, dir.y,
                          0, 0, 1, dir.z,
                          0, 0, 0, 1));
}
