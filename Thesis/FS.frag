#version 330 core
in vec3 Normal;  
in vec3 FragPos; 
in vec4 lightPosTran;
uniform vec4 color;
uniform vec3 lightColor;

uniform bool useLight; 

out vec4 FragColor;

void main()
{
	if(useLight){
		float ambientStrength = 0.3;
		vec3 ambient = ambientStrength * lightColor;

		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPosTran.xyz - FragPos);  

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor;


	
		FragColor = vec4(ambient + diffuse,1) * color;
	}
	else
	{
		FragColor = color;
	}
} 