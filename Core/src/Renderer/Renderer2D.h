#pragma once
#include "Renderer/Camera.h"
#include "Renderer/Texture.h"
#include "Renderer/SubTexture2D.h"

#include <DirectXMath.h>

namespace DXR
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(const Camera& camera, const DirectX::XMMATRIX& transform);
		static void EndScene();
		static void Flush();
		static void DrawCircle(const DirectX::XMMATRIX& transform, const DirectX::XMFLOAT4& color,
			float thickness = 1.0f, float fade = 0.005f, int entityID = -1);
		static void DrawQuad(const DirectX::XMMATRIX& transform, const DirectX::XMFLOAT4& color, int entityID = -1);
		static void DrawQuad(const DirectX::XMMATRIX& transform, const Ref<Texture2D>& texture,
			const DirectX::XMFLOAT4& tintColor = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f), float tilingFactor = 1.0f, int entityID = -1);
		static void DrawQuad(const DirectX::XMMATRIX& transform, const Ref<SubTexture2D>& subTexture,
			const DirectX::XMFLOAT4& tintColor = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), float tilingFactor = 1.0f, int entityID = -1);
		static void DrawLine(const DirectX::XMFLOAT3& p0, DirectX::XMFLOAT3& p1, const DirectX::XMFLOAT4& color, int entityID = -1);
		static void DrawRect(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT2& size, const DirectX::XMFLOAT4& color, int entityID = -1);
		static void DrawRect(const DirectX::XMMATRIX& transform, const DirectX::XMFLOAT4& color, int entityID = -1);
		static float GetLineWidth();
		static void SetLineWidth(float width);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();
	private:
		static float GetTextureID(const Ref<Texture2D>& texture);
		static void SetQuadVertex(const DirectX::XMMATRIX& transform, const DirectX::XMFLOAT4& color,
			int entityID, const DirectX::XMFLOAT2* texCoord, float texIndex, float tilingFactor);
		static void StartBatch();
		static void NextBatch();
	};
}