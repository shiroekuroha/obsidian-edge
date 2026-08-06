#version 330

uniform sampler2D g_Sampler;
uniform vec4 g_TintColor;

in vec2 ex_TexCoord;
out vec4 out_Color;

void main()
{
    out_Color = g_TintColor * texture(g_Sampler, ex_TexCoord);
};
