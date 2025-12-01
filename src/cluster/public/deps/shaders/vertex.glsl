#version 330

uniform mat4 u_Model;      // from your Node2D
uniform mat4 u_View;       // camera (optional)
uniform mat4 u_Proj;       // projection


layout(location=0)in vec4 in_Position;
layout(location=1)in vec4 in_TintColor;
layout(location=2)in vec2 in_TexCoord;

out vec4 ex_TintColor;
out vec2 ex_TexCoord;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * in_Position;
    
    ex_TintColor = in_TintColor;
    ex_TexCoord = in_TexCoord;
};
