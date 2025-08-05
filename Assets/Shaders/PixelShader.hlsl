Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float3 camera_direction : TEXCOOR2;
    float3 fragPos : TEXCOORD3;
    float3 vert_color : COLOR0;
};

struct LightData
{
    float3 ambient_color;
    float ambient_intensity;
    float3 diffuse_color;
    float diffuse_intensity;
    float3 spec_color;
    float spec_intensity;
    float3 direction; // For Directional and Spot lights
    float spec_phong;
    float3 position; // For Point and Spot lights
    float innerCutoff; // For Spotlights
    float outerCutoff; // For Spotlights
    int lightType; // 0: Directional, 1: Point, 2: Spot
    float3 padding;
};

static const int MaxNumberOfLights = 32;
cbuffer lightBuffer : register(b0)
{
    LightData lights[MaxNumberOfLights];
};

cbuffer cameraBuffer : register(b1)
{
    column_major float4x4   viewMat;
    column_major float4x4   projectionMat;
    float4                  camPosition;
};

cbuffer perObjectBuffer : register(b2)
{
    column_major float4x4   transformMat;
    float3                  materialTint;
    bool                    hasTexture;
}

float3 CalcAmbient(float intensity, float3 color);
float3 CalcDiffuse(float intensity, float3 color, float3 lightDir, float3 normal);
float3 CalcSpec(float intensity, float3 color, float specPhong, float3 lightDir, float3 camDir, float3 normal);

float3 CalcBaseLight(LightData light, float3 direction, float3 normal, float3 camDir);
float3 CalcDirLight(LightData light, float3 normal, float3 camDir);
float3 CalcPointLight(LightData light, float3 normal, float3 fragPos, float3 camDir);
float3 CalcSpotLight(LightData light, float3 normal, float3 fragPos, float3 camDir);

float4 psmain( PS_INPUT input ) : SV_TARGET
{
    // LIGHTING CALCULATIONS 
    float3 final_light = float3(0.0, 0.0, 0.0);
    for (int i = 0; i < MaxNumberOfLights; i++)
    {
        switch (lights[i].lightType)
        {   
            case 0: // Directional Light
                final_light += CalcDirLight(lights[i], input.normal, input.camera_direction);
                break;
            case 1: // Point Light
                final_light += CalcPointLight(lights[i], input.normal, input.fragPos, input.camera_direction);
                break;
            case 2: // Spot Light
                final_light += CalcSpotLight(lights[i], input.normal, input.fragPos, input.camera_direction);
                break;
            default:
                break;
        }
    }
    
    // TEXTURE CALCULATION
    float4 tex_color = float4(1.0, 1.0, 1.0, 1.0);
    if (hasTexture)
        tex_color = Texture.Sample(TextureSampler, input.texcoord);
    
    tex_color.xyz *= materialTint.xyz;
    
    float3 final_color = final_light * tex_color;
    return float4(final_color, 1.0);
}

float3 CalcBaseLight(LightData light, float3 direction, float3 normal, float3 camDir)
{
    return
        CalcAmbient(light.ambient_intensity, light.ambient_color) +
        CalcDiffuse(light.diffuse_intensity, light.diffuse_color, direction, normal) +
        CalcSpec(light.spec_intensity, light.spec_color, light.spec_phong, direction, camDir, normal);
}

float3 CalcDirLight(LightData light, float3 normal, float3 camDir)
{
    return CalcBaseLight(light, -light.direction, normal, camDir);
}

float3 CalcPointLight(LightData light, float3 normal, float3 fragPos, float3 camDir)
{
    float3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    
    float3 baseLighting = CalcBaseLight(light, lightDir, normal, camDir);
    baseLighting *= (1.0 / (distance * distance));
    
    return baseLighting;
}

float3 CalcSpotLight(LightData light, float3 normal, float3 fragPos, float3 camDir)
{
    float cosTheta = dot(normalize(light.position - fragPos), normalize(-light.direction));
    float cosInner = cos(light.innerCutoff);
    float cosOuter = cos(light.outerCutoff);
    float intensity = clamp((cosTheta - cosOuter) / (cosInner - cosOuter), 0.0, 1.0);
    
    float3 baseLighting = CalcPointLight(light, normal, fragPos, camDir);
    baseLighting *= intensity;

    return baseLighting;
}

float3 CalcAmbient(float intensity, float3 color)
{
    return intensity * color;
}

float3 CalcDiffuse(float intensity, float3 color, float3 lightDir, float3 normal)
{
    float lightAmount = max(0.0, dot(lightDir.xyz, normal));
    return intensity * lightAmount * color;
}

float3 CalcSpec(float intensity, float3 color, float specPhong, float3 lightDir, float3 camDir, float3 normal)
{
    float3 reflectedLight = normalize(reflect(lightDir.xyz, normal));
    float lightAmount = pow(max(0.0, dot(reflectedLight, camDir)), specPhong);
    return intensity * lightAmount * color;
}