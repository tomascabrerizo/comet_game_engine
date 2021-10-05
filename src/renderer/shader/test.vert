#version 450 core

layout (location = 0) in vec2 pos;

uniform mat4 model;
uniform mat4 projection;

void main() 
{
    vec2 screen_pos = pos;
    screen_pos.x = (pos.x * 2)/800 - 1;
    screen_pos.y = (pos.y * 2)/600 - 1;
    gl_Position = projection * vec4(pos, 0, 1);
}
