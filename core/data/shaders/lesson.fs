#version 330 core

uniform sampler2D texture0; 

in vec3 c_normal;
in vec2 c_uv_coord;

out vec4 color;

void main(void)
{
        vec3 lightDir = vec3(0.0, 1.0, 1.0);
        // vec4 diffuse = vec4(c_normal.xyz, 1.0);
        // vec4 diffuse = vec4(c_uv_coord, 0.0, 1.0);
        vec4 diffuse = texture(texture0, c_uv_coord);
        float nDotL = clamp(dot(c_normal, lightDir), 0.2, 1);
        color = nDotL * diffuse;
}

