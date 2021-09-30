#version 460
in  vec3 vertDir;
out vec4 fragColor;

uniform sampler3D noiseTexture;
uniform vec3 offset;

void main() { 
	vec4 color1 = vec4(0.8,0.7,0.0,0.0);
	vec4 color2 = vec4(0.6,0.1,0.0,0.0);

	vec4 noiseVec = texture(noiseTexture,vertDir * 1.2);

	float intensity = abs(noiseVec.r - 0.25) +
					  abs(noiseVec.g - 0.125) +
					  abs(noiseVec.b - 0.0625) +
					  abs(noiseVec.a - 0.03125);

	intensity = clamp(intensity * 6.0, 0.0,1.0);
	fragColor = mix(color1,color2,intensity);
} 

