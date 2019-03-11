#define PI 3.14159265358979323

mat4 rotate_x(float angle) {
    return mat4(1, 0, 0, 0,
                0, cos(angle), -sin(angle), 0,
                0, sin(angle), cos(angle), 0,
                0, 0, 0, 1);
}
