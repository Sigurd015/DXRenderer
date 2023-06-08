struct VSIn
{
    float3 pos : Position;
    float3 nor : Normal;
    float2 tex : Texcoord;
};
struct VSOut
{
    float4 pos : SV_Position;
    float3 nor : Normal;
    float2 tex : Texcoord;
    float4 col : Color;
};

cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix ViewProj;
    float4 Color;
}

VSOut main(VSIn vsi)
{
    VSOut vso;
    vso.pos = mul(float4(vsi.pos, 1.0f), World);
    vso.pos = mul(vso.pos, ViewProj);
    vso.nor = vsi.nor;
    vso.tex = vsi.tex;
    vso.col = Color;
    return vso;
}