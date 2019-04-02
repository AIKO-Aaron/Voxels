#define SPECULAR_CONSTANT 0.5f

struct lightSource {
    vec4 position; // If w = 1 then pos, else (w = 0) then direction
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 attenuation;
    
    float brightness;
};

struct material {
    int isTextured;
    vec4 color;
    float shininess;
    
    sampler2D tex;
    sampler2D ambientTex;
    sampler2D diffuseTex;
    sampler2D specularTex;
};

vec4 getColor(material m, vec2 uv) { return m.isTextured == 1 ? texture(m.tex, uv) : m.color; }
vec3 getAmbientColor(material m, vec2 uv) { return m.isTextured == 1 ? texture(m.ambientTex, uv).rgb : m.color.rgb; }
vec3 getDiffuseColor(material m, vec2 uv) { return m.isTextured == 1 ? texture(m.diffuseTex, uv).rgb : m.color.rgb; }
vec3 getSpecularColor(material m, vec2 uv) { return m.isTextured == 1 ? texture(m.specularTex, uv).rgb : m.color.rgb; }

vec3 calcLight(material m, lightSource src, vec3 viewPos, vec3 pos, vec3 normalVec, vec2 uv, mat4 view) {
    // Some intermediate values
    vec3 lightDir;
    if(src.position.w == 0) lightDir = normalize(src.position.xyz); // Only dir
    else lightDir = normalize(pos - src.position.xyz); // Position --> dir is from our pos to this pos
    
    vec3 viewDir = normalize(pos - viewPos);
    vec3 reflectDir = reflect(lightDir, normalize(normalVec));
    
    // Calculate our lights
    vec3 amb = src.ambientColor ;
    vec3 diff = src.diffuseColor * max(dot(normalize(normalVec), lightDir), 0.0);
    vec3 spec = SPECULAR_CONSTANT * src.specularColor * pow(max(dot(viewDir, reflectDir), 0.0), m.shininess);

    if(src.position.w != 0) { // Not directional light
        float d = distance(src.position.xyz, pos);
        float attenuation = 1.0f / dot(vec3(1.0f, d, d * 3), src.attenuation);
        
        amb *= attenuation;
        diff *= attenuation;
        spec *= attenuation;
    }
    
    // Add up all our light values multiplied with the "color" (factor for each color channel) of that light multiplied with the color value at that position
    return src.brightness * (amb * getAmbientColor(m, uv) + diff * getDiffuseColor(m, uv) + spec * getSpecularColor(m, uv)) * getColor(m, uv).rgb;
}
