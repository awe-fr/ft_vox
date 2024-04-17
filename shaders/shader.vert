#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 ColorVertex;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 color;

void main(){
    mat4 MVP = Projection * View * Model;
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
    color = ColorVertex;
}