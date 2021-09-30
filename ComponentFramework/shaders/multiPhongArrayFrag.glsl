#version 460
in  vec3 vertNormal;
///in  int  numberOfLights;
in  vec3 lightDir[2];
///in  vec4 lightDiffuse[2];
///in  vec4 lightSpecular[2];
in  vec3 eyeDir;
out vec4 fragColor;

void main() { 
	vec4 ks0 = vec4(0.3, 0.3, 0.3, 0.0);
	vec4 kd0 = vec4(0.6, 0.1, 0.1, 0.0); 
	vec4 ks1 = vec4(0.3, 0.3, 0.3, 0.0);
	vec4 kd1 = vec4(0.1, 0.1, 0.6, 0.0);

	vec4 ka =  vec4(0.1, 0.1, 0.1, 0.0); 
	fragColor =  ka;


	/// Reflection is based on the incedent light source which means it is 
	/// a vector FROM the light source not the direction TO the light source

	for(int i = 0; i < 2; i++){
		float diff = max(dot(vertNormal, lightDir[i]), 0.0);
		vec3 reflection = normalize(reflect(-lightDir[i], vertNormal));
		float spec = max(dot(eyeDir, reflection), 0.0);
		if(diff > 0.0){
			spec = pow(spec,14.0);
		}

		///fragColor +=  (diff * lightDiffuse[i]) + (spec * lightSpecular[i]);
		if(i == 0){
			fragColor +=  (diff * kd0) + (spec * ks0);
		}
		if(i == 1){
			fragColor +=  (diff * kd1) + (spec * ks1);
		}
		
	}
} 

