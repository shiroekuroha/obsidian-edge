#version 330

uniform mat4 g_MVP;

layout(location=0)in vec4 in_Position;
layout(location=1)in vec4 in_TintColor;
layout(location=2)in vec2 in_TexCoord;

out vec4 ex_TintColor;
out vec2 ex_TexCoord;

void main()
{
    gl_Position = g_MVP * in_Position;
    ex_TintColor = in_TintColor;
    ex_TexCoord = in_TexCoord;
};
