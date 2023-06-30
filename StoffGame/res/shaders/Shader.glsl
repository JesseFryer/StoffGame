#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in float aTexIndex;
layout(location = 3) in vec4 aColour;

out vec2 TexCoord;
out float TexIndex;
out vec4 Colour;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoord = aTexCoord;
	TexIndex = aTexIndex;
	Colour = aColour;
    gl_Position = projection * view * vec4(aPos.x, aPos.y, 0.0f, 1.0f);
}
#version 330 core
out vec4 FragColour;

in vec2 TexCoord;
in float TexIndex;
in vec4 Colour;

uniform sampler2D u_Textures[32];

void main()
{
    int index = int(TexIndex);
    if (index == -1)
    {
        FragColour = Colour;
    }
    else 
    {
        FragColour = texture(u_Textures[index], TexCoord);
    }
    if (FragColour == 0) discard;
}