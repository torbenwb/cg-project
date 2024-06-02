    #version 330 core
    uniform mat4 view;
    uniform sampler2D textureSampler;
    vec3 dirLight = vec3(0.5, 1, 0);
    vec3 dirLightColor = vec3(0.95, 0.95, 1.0);

    in vec3 fragPos; // world space position of point
    in vec3 fragNormal; // world space normal of point
    in vec2 fragUV; // UV

    out vec4 pColor;
    float ambient = 0.5f;
    float diffuse = 0.5f;
    void main() {
        vec3 objectColor = vec3(1, 1, 1); // White color for the object
        objectColor = texture(textureSampler, fragUV).xyz;
        vec3 result = objectColor;
        vec3 lightDir = normalize(dirLight);
        vec3 normal = normalize(fragNormal);
        vec3 backFaceNormal = normalize(-fragNormal);
        float d = dot(normal, lightDir);

        float intensity = ambient + diffuse * d;
        float r = objectColor.x * dirLightColor.x * intensity;
        float g = objectColor.y * dirLightColor.y * intensity;
        float b = objectColor.z * dirLightColor.z * intensity;
        pColor = vec4(r, g, b, 1.0);
    }