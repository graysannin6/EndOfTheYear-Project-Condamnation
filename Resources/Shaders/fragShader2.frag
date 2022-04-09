#version 450 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec3 o_normal;
in vec3 o_pos;
in mat4 ModelMat;
in vec2 TexCoords;

struct LightSource
{
    float intensity;
    bool isDirectionnal;
    vec3 LightPos;
    vec3 LightColor;
};

uniform LightSource pointLights[8];
uniform vec3 viewPos;
uniform vec3 objColor;
uniform float objShininess;
uniform sampler2D objectTexture;

int radius = 8;

void main()
{
    vec3 resultFinal = vec3(0, 0, 0);

    vec3 viewDir = normalize(viewPos - o_pos);
    // ambient lighting
    float ambientStrength = 0.05;
    float diffuseCoeff = 0.8;
    vec3 ambient = ambientStrength * objColor;

    for(int i = 0; i < 8; i++)
    {
        vec3 lightPosition = pointLights[i].LightPos;
        vec3 lightColor = pointLights[i].LightColor;
        // diffuse lighting
        vec3 norm = o_normal;
        vec3 lightDir;
        if(!pointLights[i].isDirectionnal)
        {
            lightDir = normalize(lightPosition - o_pos);
        }
        else
        {
            lightDir = vec3(1, 1, 0);
        }

        float checkSide = dot(viewDir, norm);
        if(checkSide < 0.0)
            norm = -norm;

        vec3 surfaceTolight = normalize(pointLights[i].LightPos - o_pos);
        float diffuseCoeff = max(0.0, dot(norm, surfaceTolight));
        vec3 diffuse = diffuseCoeff * pointLights[i].LightColor * pointLights[i].intensity;

        vec3 reflectDir = reflect(-lightDir, norm);  
        float cosAngle = max(0.0, dot(viewDir, reflectDir));
        float specCoeff = pow(cosAngle, 100);
        vec3 specular = specCoeff * normalize(objColor + pointLights[i].LightColor) * objShininess;  

        float dist = distance(o_pos, lightPosition);
        float attenuation = 1.0 / (1.0 + 0.5 * pow(dist, 2));

        vec3 result;
         if(!pointLights[i].isDirectionnal)
         {
            result = (ambient + attenuation * diffuse + specular);
         }
         else
         {
            result = (ambient + diffuse + specular) * pointLights[i].intensity * objColor;
         }
        resultFinal += result;
    }
    FragColor = texture(objectTexture, TexCoords) * vec4(resultFinal, 1.0);
} 