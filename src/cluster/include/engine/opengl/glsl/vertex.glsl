#version 330

layout(location=0)in vec4 in_Position;
layout(location=1)in vec2 in_TexCoord;
out vec2 ex_TexCoord;

void main()
{
    gl_Position = in_Position;
    ex_TexCoord = in_TexCoord;
};
