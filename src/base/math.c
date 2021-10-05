#include "base/math.h"
#include <math.h>

// NOTE: vector 2d functions

v2 v2_add(v2 a, v2 b)
{
    v2 result = v2(a.x + b.x, a.y + b.y);
    return result;
}

v2 v2_sub(v2 a, v2 b)
{
    v2 result = v2(a.x - b.x, a.y - b.y);
    return result;
}

v2 v2_mult(v2 a, v2 b)
{
    v2 result = v2(a.x * b.x, a.y * b.y);
    return result;
}

v2 v2_scale(v2 a, f32 b)
{
    v2 result = v2(a.x * b, a.y * b);
    return result;
}

v2 v2_normalize(v2 a)
{
    v2 result = v2_scale(a, 1.0f/v2_length(a));
    return result;
}

f32 v2_dot(v2 a, v2 b)
{
    f32 result = (a.x * b.x + a.y * b.y);
    return result;
}

f32 v2_cross(v2 a, v2 b)
{
    f32 result = ((a.x * b.y) - (b.x * a.y));
    return result;
}

f32 v2_length_sqrt(v2 a)
{
    f32 result = v2_dot(a, a);
    return result;
}

f32 v2_length(v2 a)
{
    f32 result = sqrtf(v2_length_sqrt(a));
    return result;
}

// NOTE: vector 3d functions

v3 v3_add(v3 a, v3 b)
{
    v3 result = v3(a.x + b.x, a.y + b.y, a.z + b.z);
    return result;
}

v3 v3_sub(v3 a, v3 b)
{
    v3 result = v3(a.x - b.x, a.y - b.y, a.z - b.z);
    return result;
}

v3 v3_mult(v3 a, v3 b)
{
    v3 result = v3(a.x * b.x, a.y * b.y, a.z * b.z);
    return result;
}

v3 v3_scale(v3 a, f32 b)
{
    v3 result = v3(a.x * b, a.y * b, a.z * b);
    return result;
}

v3 v3_normalize(v3 a)
{
    v3 result = v3_scale(a, 1.0f/v3_length(a));
    return result;
}

f32 v3_dot(v3 a, v3 b)
{
    f32 result = (a.x * b.x + a.y * b.y + a.z * b.z);
    return result;
}

v3 v3_cross(v3 a, v3 b)
{
    v3 result = v3(
        (a.y*b.z - a.z*b.y),
        (a.z*b.x - a.x*b.z),
        (a.x*b.y - a.y*b.x)
    );
    return result;
}

f32 v3_length_sqrt(v3 a)
{
    f32 result = v3_dot(a, a);
    return result;
}

f32 v3_length(v3 a)
{
    f32 result = sqrtf(v3_length_sqrt(a));
    return result;
}

// NOTE: vector 4d funtions

v4 v4_add(v4 a, v4 b)
{
    v4 result = v4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    return result;
}

v4 v4_sub(v4 a, v4 b)
{
    v4 result = v4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    return result;
}

v4 v4_mult(v4 a, v4 b)
{
    v4 result = v4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    return result;
}

v4 v4_scale(v4 a, f32 b)
{
    v4 result = v4(a.x * b, a.y * b, a.z * b, a.w * b);
    return result;
}

v4 v4_normalize(v4 a)
{
    v4 result = v4_scale(a, 1.0f/v4_length(a));
    return result;
}

f32 v4_dot(v4 a, v4 b)
{
    f32 result = (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
    return result;
}

f32 v4_length_sqrt(v4 a)
{
    f32 result = v4_dot(a, a);
    return result;
}

f32 v4_length(v4 a)
{
    f32 result = sqrtf(v4_length_sqrt(a));
    return result;
}
