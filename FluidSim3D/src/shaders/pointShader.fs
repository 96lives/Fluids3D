#version 330 core
in vec3 worldSpacePos;

out vec4 FragColor;

uniform vec4 color;
uniform mat4 camera;
uniform mat4 model;
uniform float pointSize;
uniform float mode;

uniform struct Light {
	vec3 position;
	vec3 intensities; //a.k.a the color of the light
	float attenuation;
	float ambientCoefficient;
} light;


float near = 0.0001;
float far  = 0.1;

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}


void main() {
    float epsilon = 0.0;
	vec3 normal;
	normal.xy = gl_PointCoord * 2.0 - vec2(1.0);
	// normal.xy = vec2(0.0f, 0.0f);
	float magnitude = dot(normal.xy, normal.xy);

	if (magnitude > 1.0f + epsilon)
        discard;
	else {
        normal.z = sqrt(1.0 - magnitude);

        // calculate depth
        // float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
        // FragColor = vec4(vec3(depth), 1.0);

        vec3 surface2Light = normalize(light.position - worldSpacePos);
        float diffuse = max(0.0f, dot(normal, surface2Light));

        if (mode < 0.5f)
            FragColor = vec4(normal, 1.0f);
        else if (mode > 0.5f)
            FragColor = diffuse * color;
	}
}