struct PSin
{
	float4 pos : SV_Position;
	float4 color : Color;
	int id : ID;
};

struct PSOut
{
    float4 color : SV_Target0;
	int id : SV_Target1;
};


PSOut main(PSin pin)
{
	PSOut pso;	
	pso.color = pin.color;
	pso.id = pin.id;
    return pso;
}