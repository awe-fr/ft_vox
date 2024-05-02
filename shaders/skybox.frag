#version 430 core

in vec3 texCoords;

out vec4 FragColor;
out vec4 test;


uniform samplerCube skybox;

void main() {
    // test = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    FragColor = texture(skybox, texCoords);
}