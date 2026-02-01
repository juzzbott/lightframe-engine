//:vertex
#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 vColor;
out vec2 vTexCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    vColor = color;
    vTexCoord = texCoord;
    gl_Position = uProjection * uView * uModel * vec4(position, 1.0);
}

//:fragment
#version 450 core
        
in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main() {
    //FragColor = vec4(vColor, 1.0);
    FragColor = texture(uTexture1, vTexCoord);
    //FragColor = mix(texture(uTexture1, vTexCoord), texture(uTexture2, vTexCoord), 0.5);
}