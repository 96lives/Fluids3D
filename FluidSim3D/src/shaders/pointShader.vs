#version 330 core

layout (location = 0) in vec3 position;

out vec3 worldSpacePos;

uniform mat4 camera;
uniform mat4 model;
uniform float pointSize;

void main() {
	gl_Position = camera * model * vec4(position, 1.0f);
	worldSpacePos = (model * vec4(position, 1.0f)).xyz;
	// cameraSpacePos = gl_Position.xyz / gl_Position.w;
	gl_PointSize = pointSize;
}