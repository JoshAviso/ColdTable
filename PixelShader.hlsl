struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    column_major float4x4 m_world;
    column_major float4x4 m_view;
    column_major float4x4 m_projection;
    unsigned int m_time;
};

float4 psmain( PS_INPUT input ) : SV_TARGET
{
    return float4(input.color, 1.0f);
}