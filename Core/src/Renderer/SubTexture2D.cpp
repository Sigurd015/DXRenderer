#include "pch.h"
#include "Renderer/SubTexture2D.h"

namespace DXR
{
	SubTexture2D::SubTexture2D(Ref<Texture2D> texture, DirectX::XMFLOAT2& min, DirectX::XMFLOAT2& max) :m_Texture(texture)
	{
		m_TexCoords[0] = { min.x,min.y };
		m_TexCoords[1] = { max.x,min.y };
		m_TexCoords[2] = { max.x,max.y };
		m_TexCoords[3] = { min.x,max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(Ref<Texture2D> texture,
		DirectX::XMFLOAT2& coords, DirectX::XMFLOAT2& cellSize, DirectX::XMFLOAT2& spriteSize)
	{
		DirectX::XMFLOAT2 min = DirectX::XMFLOAT2((coords.x * cellSize.x) / texture->GetWidth(), (coords.y * cellSize.y) / texture->GetHeight());
		DirectX::XMFLOAT2 max = DirectX::XMFLOAT2(((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(),
			((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight());
		return CreateRef<SubTexture2D>(texture, min, max);
	}
}