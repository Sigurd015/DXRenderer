#pragma once
#include "Base.h"
#include "Renderer/Texture.h"

#include <DirectXMath.h>

namespace DXR
{
	class SubTexture2D
	{
	public:
		SubTexture2D(Ref<Texture2D> texture, DirectX::XMFLOAT2& min, DirectX::XMFLOAT2& max);
		const Ref<Texture2D> GetTexture() { return m_Texture; }
		const DirectX::XMFLOAT2* GetTexCoords() { return m_TexCoords; }
		static Ref<SubTexture2D> CreateFromCoords(Ref<Texture2D> texture, 
			DirectX::XMFLOAT2& coords, DirectX::XMFLOAT2& cellSize, DirectX::XMFLOAT2& spriteSize = DirectX::XMFLOAT2(1.0f,1.0f));
	private:
		Ref<Texture2D> m_Texture;
		DirectX::XMFLOAT2 m_TexCoords[4];
	};
}