#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 TextureCoor;
layout(location = 2) in vec3 aNormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 TexCoor;
out vec3 FragPos;
out vec3 Normal;

void main(){
    mat4 MVP = Projection * View * Model;
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1.0);
    TexCoor = TextureCoor;
    FragPos = vec3(Model * vec4(vertexPosition_modelspace, 1.0));
    Normal = aNormal;
}