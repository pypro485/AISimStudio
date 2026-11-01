#version 330 core

in vec3 fragColor; // REMOVED layout(location = 0) - Must exactly match the vertex out name

out vec4 FinalColor; // Fragment outputs don't need locations in 3.30 either

void main()
{
    FinalColor = vec4(fragColor, 1.0);
}
