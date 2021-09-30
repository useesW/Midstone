#version 460
in  vec3 vertNormal;
in  vec3 vertDir;
out vec4 fragColor;

uniform samplerCube skyboxTexture;

void main() { 
	///vec3 reflection = refract(vertDir,vertNormal,1.0/1.5);
	vec3 reflection = reflect(vertDir,vertNormal);
	reflection *= -1.0;
	fragColor =  texture(skyboxTexture, reflection);
} 

