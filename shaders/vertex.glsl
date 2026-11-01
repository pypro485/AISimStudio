#version 330 core
layout (location = 0) in vec3 aPos; // Input locations ARE allowed in 3.30
layout (location = 1) in vec3 aCol;

out vec3 fragColor; // REMOVED layout(location = 0) - Matched by name instead!

void main()
{
    gl_Position = vec4(aPos, 1.0);
    fragColor = aCol;
}
