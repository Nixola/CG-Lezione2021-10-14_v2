#version 330 core
in vec4 ourColor;
in vec2 TexCoord;
out vec4 FragColor;  

uniform sampler2D ourTexture;
  
void main()
{
    FragColor = texture(ourTexture, TexCoord) * ourColor;
}