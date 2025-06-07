struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant: register(b0)
{
    column_major float4x4 m_world;
    column_major float4x4 m_view;
    column_major float4x4 m_projection;
    unsigned int m_time;
};

VS_OUTPUT vsmain( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
 
    output.position = input.position;
    
    // To World Space
    output.position = mul(output.position, m_world);
    
    // To View Space
    output.position = mul(output.position, m_view);
    
    // To Screen Space
    output.position = mul(output.position, m_projection);
    
    
    output.color = input.color;
    output.color1 = input.color1;
    
	return output;
}