#version 450

layout(binding = 1) uniform GlobalUniformBufferObject {
    vec3 sunLightDir;
	vec3 sunLightCol;
	vec3 moonLightDir;
	vec3 moonLightCol;
	vec3 eyePos;
	vec3 eyeDir;		// Used to render the torch and the pointer
	vec2 ambientParams;	// x: ambient light factor, y: whether the player is in water or not
} gubo;

layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragMaterial;	// x: minimum opacity, y: roughness, z: specularity

layout(location = 0) out vec4 outColor;

vec3 oren_nayar_diffuse(vec3 lightDir, vec3 normVect, vec3 viewDir, vec3 mainColor, float sigma) {	
	float theta_i = acos(dot(lightDir, normVect));
	float theta_r = acos(dot(viewDir, normVect));
	float alpha = max(theta_i, theta_r);
	float beta = min(theta_i, theta_r);

	float sigma_2 = pow(sigma, 2);
	float A = 1 - 0.5 * sigma_2 / (sigma_2 + 0.33);
	float B = 0.45 * sigma_2 / (sigma_2 + 0.09);

	vec3 v_i = normalize(lightDir - dot(lightDir, normVect) * normVect);
	vec3 v_r = normalize(viewDir - dot(viewDir, normVect) * normVect);
	float G = max(0, dot(v_i, v_r));
	vec3 L = mainColor * clamp(dot(lightDir, normVect), 0, 1);

	return L * (A + B * G * sin(alpha) * tan(beta));
}

vec3 phong_specular(vec3 lightDir, vec3 normVect, vec3 viewDir, vec3 mainColor, float gamma)  {
	vec3 reflectDir = -reflect(lightDir, normVect);
	return mainColor * pow(clamp(dot(viewDir, reflectDir), 0, 1), gamma);
}

vec3 spot_light_color(vec3 pos, vec3 lightDir, vec3 lightPos, vec3 lightCol, vec4 lightParams) {
	float cos_alpha = dot(normalize(lightPos - pos), lightDir);
	float cone = clamp((cos_alpha - lightParams.y) / (lightParams.x - lightParams.y), 0, 1);
	return pow(lightParams.w / length(lightPos - pos), lightParams.z) * lightCol * cone;
}

void main() {
	vec3 norm = normalize(fragNorm);
	vec3 eyeDir = normalize(gubo.eyePos - fragPos);	
	
	vec4 texel = texture(texSampler, fragTexCoord);
	if(texel.a == 0) discard;
	
	// Parameters
	vec3 waterColor = vec3(65, 105, 225) / 255;
	vec3 diffuseColor = texel.rgb * (1 - gubo.ambientParams.y) + 			// Normal color
						texel.rgb * waterColor * gubo.ambientParams.y;		// Underwater color

	vec3 specularColor = vec3(clamp(sign(fragMaterial.z), 0, 0.5));

	vec4 torchParams = vec4(cos(radians(15)), cos(radians(30)), 2.0, 1.4);
	vec3 torchColor = spot_light_color(fragPos, gubo.eyeDir, gubo.eyePos, vec3(255, 215, 0) / 255, torchParams);
	float torchOn = max(0, sign(gubo.moonLightDir.y));	// The torch is on only at night (when the moon is over the horizon)

	vec4 pointerParams = vec4(cos(0.002f), cos(0.005f), 1, 1);
	vec3 pointerColor = spot_light_color(fragPos, gubo.eyeDir, gubo.eyePos, vec3(1), pointerParams);

	// Diffuse light component
	vec3 diffuse = vec3(0);
	diffuse += oren_nayar_diffuse( gubo.sunLightDir, norm, eyeDir, diffuseColor, fragMaterial.y) * gubo.sunLightCol;
	diffuse += oren_nayar_diffuse(gubo.moonLightDir, norm, eyeDir, diffuseColor, fragMaterial.y) * gubo.moonLightCol;
	diffuse += oren_nayar_diffuse(			 eyeDir, norm, eyeDir, diffuseColor, fragMaterial.y) * torchColor * torchOn;
	
	// Specular light component
	vec3 specular = vec3(0);
	specular += phong_specular( gubo.sunLightDir, norm, eyeDir, specularColor, abs(fragMaterial.z)) * gubo.sunLightCol;
	specular += phong_specular(gubo.moonLightDir, norm, eyeDir, specularColor, abs(fragMaterial.z)) * gubo.moonLightCol;
	specular += phong_specular(			  eyeDir, norm, eyeDir, specularColor, abs(fragMaterial.z)) * torchColor * torchOn;

	// Ambient light component
	vec3 ambient = gubo.ambientParams.x * diffuseColor;	

	// Pointer "light" component
	vec3 pointer = 1000 * pointerColor;
	
	// Assemble the final color
	float alphaChannel = max(fragMaterial.x, texel.a);
	outColor = vec4(diffuse + specular + ambient + pointer, alphaChannel);
}