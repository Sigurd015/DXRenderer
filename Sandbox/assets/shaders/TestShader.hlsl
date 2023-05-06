#type:vertex
struct VSOut
{
	float2 tex : TexCoord;
	float4 pos : SV_Position;
};

cbuffer CBuf
{
	float4x4 transform;
}

VSOut main( float2 pos : Position, float2 tex : TexCoord)
{
	VSOut vso;
	vso.pos = mul(float4(pos.x,pos.y,0.0f,1.0f),transform);
	vso.tex = tex;
	return vso;
}

#type:pixel
Texture2D tex;
SamplerState samplerState;

float4 main(float2 texCoord : TexCoord) : SV_Target
{
    return tex.Sample(samplerState, texCoord);
}