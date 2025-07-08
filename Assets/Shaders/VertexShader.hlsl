struct VS_INPUT
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 vert_color : COLOR0;
    //float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float3 camera_direction : TEXCOOR2;
    float3 fragPos : TEXCOORD3;
    float3 vert_color : COLOR0;
    //float3 color1 : COLOR1;
};

struct LightData
{
    float ambient_intensity;
    float3 ambient_color;
    float diffuse_intensity;
    float3 diffuse_color;
    float spec_intensity;
    float3 spec_color;
    float spec_phong;
};

struct DirectionalLight
{
    LightData lightdata;
    float3 direction;
};

struct PointLight
{
    LightData lightdata;
    float3 position;
};

struct SpotLight
{
    PointLight baseLight;
    float3 direction;
    float innerCutoff;
    float outerCutoff;
};

static const int NumberOfDirLights = 2;
cbuffer lightBuffer : register(b0)
{
    DirectionalLight dirLight[NumberOfDirLights];
    SpotLight spotlight;
    PointLight pointlight;
};

cbuffer cameraBuffer : register(b1)
{
    column_major float4x4 viewMat;
    column_major float4x4 projectionMat;
    float4 camPosition;
};

cbuffer perObjectBuffer : register(b2)
{
    column_major float4x4 transformMat;
    float3 materialTint;
    bool hasTexture;
}

VS_OUTPUT vsmain( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
 
    output.position = input.position;
    
    // To World Space
    output.position = mul(output.position, transformMat);
    output.fragPos = output.position;
    output.camera_direction = normalize(output.position.xyz - camPosition.xyz);
    
    // To View Space
    output.position = mul(output.position, viewMat);
    
    // To Screen Space
    output.position = mul(output.position, projectionMat);
    
    
    output.texcoord = input.texcoord;
    output.vert_color = input.vert_color;
    //output.color1 = input.color1;
    output.normal = input.normal;
	return output;
}