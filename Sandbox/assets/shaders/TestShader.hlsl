#type:vertex
struct VSIn
{
    float3 pos : Position;
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
	float4 Color; 
}

VSOut main(VSIn vsi)
{
	VSOut vso;
	vso.pos = mul(float4(vsi.pos,1.0f),World);
	vso.pos = mul(vso.pos,View);
	vso.pos = mul(vso.pos,Proj);
	vso.color = Color;
	return vso;
}

#type:pixel

struct VSOut
{
	float4 pos : SV_Position;
	float4 color : Color;
};

struct PSOut
{
    float4 color : SV_Target0; // 输出颜色到索引为 0 的渲染目标视图
	float4 id : SV_Target1;
};


PSOut main(VSOut pin)
{
	PSOut pso;
	pso.color=pin.color;
	pso.id=float4(-1.0f,1.0f,1.0f,1.0f);
    return pso;
}