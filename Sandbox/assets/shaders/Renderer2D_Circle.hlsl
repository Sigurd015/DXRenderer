// --------------------------
// Renderer2D Circle Shader
// --------------------------

#type:vertex
struct VertexInput
{
	float3 a_WorldPosition : POSITION0;
	float3 a_LocalPosition : POSITION1;
	float4 a_Color : COLOR0;
	float a_Thickness : TEXCOORD0;
	float a_Fade : TEXCOORD1;
	int a_EntityID : TEXCOORD2;
};

cbuffer Camera : register(b0)
{
	float4x4 u_ViewProjection;
};

struct VertexOutput
{
	float3 LocalPosition : TEXCOORD0;
	float4 Color : COLOR0;
	float Thickness : TEXCOORD1;
	float Fade : TEXCOORD2;
};

VertexOutput main(VertexInput Input)
{
	VertexOutput Output;
	Output.LocalPosition = Input.a_LocalPosition;
	Output.Color = Input.a_Color;
	Output.Thickness = Input.a_Thickness;
	Output.Fade = Input.a_Fade;

	Output.Color.a = 1.0f;

	Output.Color.rgb *= Input.a_Color.a;

	Output.Color.rgb /= Output.Color.a;
	Output.Color.a = saturate(1.0f - length(Output.LocalPosition));
	Output.Color.a *= smoothstep(Input.a_Thickness + Input.a_Fade, Input.a_Thickness, Output.Color.a);

	return Output;
}

#type:fragment
struct VertexOutput
{
	float3 LocalPosition : TEXCOORD0;
	float4 Color : COLOR0;
	float Thickness : TEXCOORD1;
	float Fade : TEXCOORD2;
};

float4 main(VertexOutput Input) : SV_Target
{
	if (Input.Color.a == 0.0f)
		discard;

	return Input.Color;
}
