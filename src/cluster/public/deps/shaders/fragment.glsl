#version 330

uniform sampler2D g_Sampler;

in vec4 ex_TintColor;
in vec2 ex_TexCoord;

out vec4 out_Color;

void main()
{
    out_Color = ex_TintColor * texture(g_Sampler, ex_TexCoord);
};
