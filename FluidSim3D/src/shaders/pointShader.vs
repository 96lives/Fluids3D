#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;


uniform mat4 camera;
uniform mat4 model;

uniform float pointSize;

void main() {
	gl_Position = camera * model * vec4(position, 1.0);
	gl_PointSize = pointSize;
}