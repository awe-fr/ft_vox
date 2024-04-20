#version 430 core

in vec3 color;

out vec3 pixel;

void main(){
  // pixel = vec3(1.0f, 1.0f, 0.0f);
  pixel = color;
}