#version 330 core

in vec3 color;
in vec2 uvs;

layout(location = 0) out vec4 final_col;

uniform int use_texture; // 0 if not. 1 else
uniform sampler2D tex0;
uniform vec3 flatColor;

void main()
{
	final_col = vec4(flatColor,1.0);
	if (use_texture == 1) {
		final_col = texture(tex0,uvs);
	}
}
