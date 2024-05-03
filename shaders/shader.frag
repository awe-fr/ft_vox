#version 430 core

// in vec3 Color;
in vec2 TexCoor;

out vec4 Pixel;

uniform sampler2D Tex;

void main(){
  // pixel = vec3(1.0f, 1.0f, 0.0f);
  // Pixel = Color;
  Pixel = texture(Tex, TexCoor);
}