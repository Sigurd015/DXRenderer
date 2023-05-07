#type:vertex
struct VSIn
{
    float3 pos : Position;
    float4 color : Color;
};
struct VSOut
{
	float4 pos : SV_Position;
	float4 color : Color;
};

cbuffer ConstantBuffer : register(b0)
{
    matrix World; 
    matrix View;  
    matrix Proj;  
}

VSOut main(VSIn vsi)
{
	VSOut vso;
	vso.pos = mul(float4(vsi.pos,1.0f),World);
	vso.pos = mul(vso.pos,View);
	vso.pos = mul(vso.pos,Proj);
	vso.color = vsi.color;
	return vso;
}

#type:pixel

struct VSOut
{
	float4 pos : SV_Position;
	float4 color : Color;
};

float4 main(VSOut pin) : SV_Target
{
    return pin.color;
}