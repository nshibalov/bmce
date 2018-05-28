#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

in vec3 normal;
in vec3 position;
in vec2 uv_coord;

out vec3 c_normal;
out vec2 c_uv_coord;

void main(void)
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
	c_normal = normal;
	c_uv_coord = uv_coord;
}

