#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 mvp;
uniform vec3 lightPos;  

out vec3 Normal;
out vec3 FragPos; 
out vec4 lightPosTran;

void main()
{	
	lightPosTran = mvp * vec4(lightPos, 1.0);
    gl_Position = mvp * vec4(aPos, 1.0);
	FragPos = aPos;
	Normal = aNormal;
}