#include "base/math.h"

// NOTE: common math funtions
f32 to_rad(f32 angle)
{
    f32 result = (angle * NUM_PI) / 180.0f;
    return result;
}

f32 f32_cos(f32 angle)
{
    f32 result = cosf(angle);
    return result;
}

f32 f32_sin(f32 angle)
{
    f32 result = sinf(angle);
    return result;
}

f32 f32_tan(f32 angle)
{
    f32 result = tanf(angle);
    return result;
}

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

// NOTE: matrix 4 funtions 

m4 m4_mult(m4 a, m4 b)
{
    m4 result = {0};
    for(i32 j = 0; j < 4; ++j)
    {
        for(i32 i = 0; i < 4; ++i)
        {
            result.m[j][i] = a.m[j][0] * b.m[0][i] +
                             a.m[j][1] * b.m[1][i] +
                             a.m[j][2] * b.m[2][i] +
                             a.m[j][3] * b.m[3][i];
        }
    }
    return result;
}

m4 m4_identity(void)
{
    m4 result = {0};
    result.m[0][0] = 1.0f;
    result.m[1][1] = 1.0f;
    result.m[2][2] = 1.0f;
    result.m[3][3] = 1.0f;
    return result;
}

m4 m4_scale(f32 scale)
{
    m4 result = m4_identity();
    result.m[0][0] = scale;
    result.m[1][1] = scale;
    result.m[2][2] = scale;
    return result;
}

m4 m4_translate(v3 translate)
{
    m4 result = m4_identity();
    result.m[0][3] = translate.x;
    result.m[1][3] = translate.y;
    result.m[2][3] = translate.z;
    return result;
}

m4 m4_rotate_x(f32 angle)
{
    m4 result = m4_identity();
    f32 rad_angle = to_rad(angle);
    f32 sin_a = f32_sin(rad_angle);
    f32 cos_a = f32_cos(rad_angle);
    result.m[1][1] =  cos_a;
    result.m[1][2] = -sin_a;
    result.m[2][1] =  sin_a;
    result.m[2][2] =  cos_a;
    return result;
}

m4 m4_rotate_y(f32 angle)
{
    m4 result = m4_identity();
    f32 rad_angle = to_rad(angle);
    f32 sin_a = f32_sin(rad_angle);
    f32 cos_a = f32_cos(rad_angle);
    result.m[0][0] =  cos_a;
    result.m[0][2] =  sin_a;
    result.m[2][0] = -sin_a;
    result.m[2][2] =  cos_a;
    return result;
}

m4 m4_rotate_z(f32 angle)
{
    m4 result = m4_identity();
    f32 rad_angle = to_rad(angle);
    f32 sin_a = f32_sin(rad_angle);
    f32 cos_a = f32_cos(rad_angle);
    result.m[0][0] =  cos_a;
    result.m[0][1] = -sin_a;
    result.m[1][0] =  sin_a;
    result.m[1][1] =  cos_a;
    return result;
}

m4 m4_orthographic(f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far)
{
    m4 result = m4_identity();
    result.m[0][0] = 2 / (right - left); 
    result.m[1][1] = 2 / (top - bottom); 
    result.m[2][2] = -2 / (far - near); 
    result.m[0][3] = -((right + left)/(right - left)); 
    result.m[1][3] = -((top + bottom)/(top - bottom)); 
    result.m[2][3] = -((far + near)/(far - near)); 
    return result;
}

m4 m4_perspective(f32 fov, f32 aspect, f32 near, f32 far)
{
    f32 tan_half_fov = f32_tan(to_rad(fov*0.5f));
    f32 range = (far - near);
    m4 result = {0};
    result.m[0][0] = 1.0f / (aspect*tan_half_fov);
    result.m[1][1] = 1.0f / tan_half_fov;
    result.m[2][2] = far / range;
    result.m[2][3] = (-far*near) / range;
    result.m[3][2] = 1.0f;
    return result;
}

v4 m4_mult_v4(m4 matrix, v4 v)
{
    v4 result = {0};
    result.x = ((matrix.m[0][0] * v.x) + (matrix.m[0][1] * v.y) + 
                (matrix.m[0][2] * v.z) + (matrix.m[0][3] * v.w));
    
    result.y = ((matrix.m[1][0] * v.x) + (matrix.m[1][1] * v.y) + 
                (matrix.m[1][2] * v.z) + (matrix.m[1][3] * v.w));
    
    result.z = ((matrix.m[2][0] * v.x) + (matrix.m[2][1] * v.y) + 
                (matrix.m[2][2] * v.z) + (matrix.m[2][3] * v.w));
    
    result.w = ((matrix.m[3][0] * v.x) + (matrix.m[3][1] * v.y) + 
                (matrix.m[3][2] * v.z) + (matrix.m[3][3] * v.w));
    return result;
}
