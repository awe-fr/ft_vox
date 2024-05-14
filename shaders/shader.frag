#version 430 core

in vec2 TexCoor;

out vec4 Pixel;

uniform sampler2D Tex;
uniform float trans;

void main(){
  Pixel = texture(Tex, TexCoor);
  Pixel.a *= trans;
}