#version 330 core
out vec4 FragColor;

uniform vec4 color;
uniform mat4 camera;
uniform mat4 model;

void main() {
	vec3 N;
	N.xy = gl_PointCoord * 2.0 - vec2(1.0);
	float magnitude = dot(N.xy, N.xy);

	if (magnitude > 1.0f)
        discard;
	else {
        N.z = -sqrt(1.0 - magnitude);
        FragColor = color ;
	}
}