struct VertexInput
{
    float3 a_Position : a_Position;
    float3 a_Normal : a_Normal;
    float2 a_TexCoord : a_TexCoord;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float3 Normal : Nor;
    float2 TexCoord : Tex;
    float4 Ambient : Amb;
};

cbuffer Camera : register(b0)
{
    float4x4 u_Model;
    float4x4 u_ViewProjection;
    
    // DirectionalLight
    float4 u_Ambient;
    float3 u_Direction;
};

VertexOutput main(VertexInput Input)
{
    VertexOutput Output;
    Output.Position = mul(float4(Input.a_Position, 1.0f), u_Model);
    Output.Position = mul(Output.Position, u_ViewProjection);
    Output.Normal = Input.a_Normal;
    Output.TexCoord = Input.a_TexCoord;
    Output.Ambient = u_Ambient;
    return Output;
}