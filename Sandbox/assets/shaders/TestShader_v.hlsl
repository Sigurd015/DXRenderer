struct VSIn
{
    float3 pos : Position;
	int id : Id;
};
struct VSOut
{
	float4 pos : SV_Position;
	float4 color : Color;
	int id : ID;
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
	vso.pos = mul(float4(vsi.pos,1.0f),World);
    vso.pos = mul(vso.pos, ViewProj);
	//vso.pos = mul(vso.pos,Proj);
	vso.color = Color;
	vso.id = vsi.id;
	return vso;
}