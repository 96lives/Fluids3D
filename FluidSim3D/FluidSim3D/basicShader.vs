#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 normal0;

uniform mat4 camera;
uniform mat4 model; 

void main() {
	gl_Position = camera * model * vec4(position, 1.0);
	normal0 = (model * vec4(normal, 0.0)).xyz;
}