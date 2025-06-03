
ByteAddressBuffer Buffer0 : register(t0);
RWByteAddressBuffer BufferOut : register(u0);

cbuffer constant : register(b0)
{
    unsigned int m_time;
};

[numthreads(12, 1, 1)]
void CSMain( uint3 DTid : SV_DispatchThreadID )
{
    float vertX = asfloat(Buffer0.Load(DTid.x*12));
    float vertY = asfloat(Buffer0.Load(DTid.x * 12 + 4));
    
    vertX += (sin(m_time / 1000.0f) / 10.0f);
    vertY += (cos(m_time / 1000.0f) / 10.0f);
    
    BufferOut.Store(DTid.x * 12, asuint(vertX));
    BufferOut.Store(DTid.x * 12 + 4, asuint(vertY));
}

