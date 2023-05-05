#version 330 core
out vec4 rColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 vPos;
in vec3 vNormal;
  
uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    // ambient
    vec3 ambience = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(light.position - vPos);
    float diffuse = max(dot(normal, lightDir), 0.0);
    vec3 diffusion = light.diffuse * (diffuse * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - vPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float shine = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularity = light.specular * (shine * material.specular);  
        
    vec3 lightEffect = ambience + diffusion + specularity;
    rColor = vec4(lightEffect, 1.0);
} 

