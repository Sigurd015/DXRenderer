struct PixelInput
{
    float4 Position : SV_Position;
    float3 Normal : Nor;
    float2 TexCoord : Tex;
    float Ambient : Amb;
};

struct PixelOutput
{
    float4 Color : SV_Target0;
};

Texture2D u_Diffuse : register(t0);
SamplerState u_DiffuseSamplerState : register(s0);

Texture2D u_Specular : register(t1);
SamplerState u_SpecularSamplerState : register(s1);

PixelOutput main(PixelInput Input)
{
    PixelOutput Output;
    float4 diffuseColor = u_Diffuse.Sample(u_DiffuseSamplerState, Input.TexCoord);
    float4 specularColor = u_Diffuse.Sample(u_DiffuseSamplerState, Input.TexCoord);
    Output.Color = Input.Ambient * (diffuseColor + specularColor);
    return Output;
}