#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

//uniform vec4 ourColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
