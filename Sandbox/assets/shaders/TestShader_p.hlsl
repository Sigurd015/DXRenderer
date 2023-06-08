struct PSin
{
    float4 pos : SV_Position;
    float3 nor : Normal;
    float2 tex : Texcoord;
    float4 col : Color;
};

struct PSOut
{
    float4 color : SV_Target0;
};

PSOut main(PSin pin)
{
    PSOut pso;
    pso.color = pin.col;
    return pso;
}