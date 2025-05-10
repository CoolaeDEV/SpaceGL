#version 330 core

in vec3 normal;
in vec3 fragPos;
out vec4 FragColor;

uniform vec4 resolution;
uniform float time;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ObjectColor;
uniform vec3 viewPos;
uniform float lightBrightness;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main() {

   vec3 ambient = lightColor * material.ambient;

   vec3 norma = normalize(normal);
   vec3 lightDir = normalize(lightPos - fragPos);
   float diff = max(dot(norma, lightDir), 0.0);
   vec3 diffuse = diff * lightColor * material.diffuse;

   vec3 viewDir = normalize(viewPos - fragPos);
   vec3 reflectDir = reflect(-lightDir, norma);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);


   vec3 specular;

   if(lightBrightness == 0.0){
      specular = spec * material.specular;
   }else{
      specular = spec * (lightColor * lightBrightness) * material.specular;
   }
   vec3 result = ((ambient + diffuse + specular) * ObjectColor) * lightBrightness;
   FragColor = vec4(result, 1.0);
}