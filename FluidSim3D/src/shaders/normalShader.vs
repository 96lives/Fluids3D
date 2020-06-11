#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 fragNormal;
out vec3 fragVert;

uniform mat4 model;
uniform mat4 camera; 

void main() {
	fragNormal = normal;
	fragVert = position;
	gl_Position = camera * model * vec4(position, 1.0);
}