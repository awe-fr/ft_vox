#version 430 core

in vec2 TexCoor;
in vec3 FragPos;
in vec3 Normal;

out vec4 Pixel;

uniform sampler2D Tex;
uniform float trans;
uniform vec3 lightPos;

void main(){
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse3 = diff * vec3(1.0f, 1.0f, 1.0f);
  vec4 diffuse = vec4(diffuse3, 1.0f);
  diffuse /= 3;

  float ambientStrength = 0.7;
  vec3 ambient3 = ambientStrength * vec3(1.0f, 1.0f, 1.0f);
  vec4 ambient = vec4(ambient3, 1.0f);

  Pixel = texture(Tex, TexCoor);

  Pixel.a *= trans;
  Pixel *= (ambient + diffuse);
}