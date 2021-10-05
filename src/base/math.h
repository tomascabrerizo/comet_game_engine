#ifndef MATH_H
#define MATH_H

#include "base/base.h"
#include <math.h>

// NOTE: common math funtions

#define NUM_PI 3.1415926f

COMET f32 to_rad(f32 angle);
COMET f32 f32_cos(f32 angle);
COMET f32 f32_sin(f32 angle);
COMET f32 f32_tan(f32 angle);

// NOTE: get vector components as an array
#define VEC_INDEX(v, index) ((f32 *)&v)[index]

typedef struct v2
{
    f32 x;
    f32 y;
} v2;
#define v2(x, y) (v2){(f32)x, (f32)y}

COMET v2 v2_add(v2 a, v2 b);
COMET v2 v2_sub(v2 a, v2 b);
COMET v2 v2_mult(v2 a, v2 b);
COMET v2 v2_scale(v2 a, f32 b);

COMET v2 v2_normalize(v2 a);

COMET f32 v2_dot(v2 a, v2 b);
COMET f32 v2_cross(v2 a, v2 b);
COMET f32 v2_length_sqrt(v2 a);
COMET f32 v2_length(v2 a);

typedef struct v3
{
    f32 x;
    f32 y;
    f32 z;
} v3;
#define v3(x, y, z) (v3){(f32)x, (f32)y, (f32)z}

COMET v3 v3_add(v3 a, v3 b);
COMET v3 v3_sub(v3 a, v3 b);
COMET v3 v3_mult(v3 a, v3 b);
COMET v3 v3_scale(v3 a, f32 b);

COMET v3 v3_normalize(v3 a);

COMET f32 v3_dot(v3 a, v3 b);
COMET v3 v3_cross(v3 a, v3 b);
COMET f32 v3_length_sqrt(v3 a);
COMET f32 v3_length(v3 a);

typedef struct v4
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} v4;
#define v4(x, y, z, w) (v4){(f32)x, (f32)y, (f32)z, (f32)w}

COMET v4 v4_add(v4 a, v4 b);
COMET v4 v4_sub(v4 a, v4 b);
COMET v4 v4_mult(v4 a, v4 b);
COMET v4 v4_scale(v4 a, f32 b);

COMET v4 v4_normalize(v4 a);

COMET f32 v4_dot(v4 a, v4 b);
COMET f32 v4_length_sqrt(v4 a);
COMET f32 v4_length(v4 a);

typedef struct m4
{
    f32 m[4][4];
} m4;

COMET m4 m4_identity(void);
COMET m4 m4_scale(f32 scale);
COMET m4 m4_translate(v3 translate);

COMET m4 m4_rotate_x(f32 angle);
COMET m4 m4_rotate_y(f32 angle);
COMET m4 m4_rotate_z(f32 angle);

COMET m4 m4_mult(m4 a, m4 b);
COMET v4 m4_mult_v4(m4 matrix, v4 v);

COMET m4 m4_orthographic(f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far);
COMET m4 m4_perspective(f32 fov, f32 aspect, f32 near, f32 far);

#endif // MATH_H
