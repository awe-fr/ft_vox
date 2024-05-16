#version 430 core

in vec2 TexCoor;
in vec3 Normal;

out vec4 Pixel;

uniform sampler2D Tex;
uniform float trans;

void main(){
  float ambientStrength = 0.4;
  vec3 ambient3 = ambientStrength * vec3(1.0f, 1.0f, 1.0f);
  vec4 ambient = vec4(ambient3, 1.0f);

  Pixel = texture(Tex, TexCoor);

  Pixel.a *= trans;
  Pixel *= ambient;
}