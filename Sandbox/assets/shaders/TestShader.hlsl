#type:vertex
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
    matrix View;  
    matrix Proj; 
	float4 Color; 
}

VSOut main(VSIn vsi)
{
	VSOut vso;
	vso.pos = mul(float4(vsi.pos,1.0f),World);
	vso.pos = mul(vso.pos,View);
	vso.pos = mul(vso.pos,Proj);
	vso.color = Color;
	vso.id = vsi.id;
	return vso;
}

#type:pixel

struct PSin
{
	float4 pos : SV_Position;
	float4 color : Color;
	int id : ID;
};

struct PSOut
{
    float4 color : SV_Target0; // 输出颜色到索引为 0 的渲染目标视图
	int id : SV_Target1;
};


PSOut main(PSin pin)
{
	PSOut pso;
	pso.color = pin.color;
	pso.id = pin.id;
    return pso;
}