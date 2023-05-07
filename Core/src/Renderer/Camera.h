#pragma once
#include <DirectXMath.h>

namespace DXR
{
	class Camera
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;
		Camera(const const DirectX::XMMATRIX& projection) : m_Projection(projection) {}
		const const DirectX::XMMATRIX& GetProjection() const { return m_Projection; }
	protected:
		const DirectX::XMMATRIX m_Projection = DirectX::XMMatrixIdentity();
	};
}