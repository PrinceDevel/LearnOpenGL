#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

out vec3 vPos;
out vec3 vNormal;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vPos = vec3(transform * vec4(aPosition, 1.0));
    vNormal = mat3(transpose(inverse(transform))) * aNormal;  
    
    gl_Position = projection * view * vec4(vPos, 1.0);
}

