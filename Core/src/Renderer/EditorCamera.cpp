#include "pch.h"
#include "Renderer/EditorCamera.h"
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

namespace DXR
{
	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip),
		Camera(DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}

	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	void EditorCamera::UpdateView()
	{
		// m_Yaw = m_Pitch = 0.0f; // Lock the camera's rotation
		m_Position = CalculatePosition();

		DirectX::XMVECTOR orientation = GetOrientation();
		DirectX::XMFLOAT3 temp;
		DirectX::XMStoreFloat3(&temp, m_Position);
		m_ViewMatrix = DirectX::XMMatrixRotationQuaternion(orientation) * DirectX::XMMatrixTranslation(temp.x, temp.y, temp.z); // Notice: DirectXMath is row major
		m_ViewMatrix = DirectX::XMMatrixInverse(nullptr, m_ViewMatrix);
	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = m_ViewportWidth / 1000.0f < 2.4f ? m_ViewportWidth / 1000.0f : 2.4f; // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = m_ViewportHeight / 1000.0f < 2.4f ? m_ViewportHeight / 1000.0f : 2.4f; // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;

		distance = distance > 0.0f ? distance : 0.0f;;
		float speed = distance * distance;
		speed = speed < 100.0f ? speed : 100.0f; // max speed = 100
		return speed;
	}

	void EditorCamera::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::Alt))
		{
			const DirectX::XMFLOAT2& mouse = Input::GetMousePosition();
			DirectX::XMFLOAT2 delta;
			DirectX::XMStoreFloat2(&delta, DirectX::XMVectorScale(
				DirectX::XMVectorSubtract(DirectX::XMLoadFloat2(&mouse), m_InitialMousePosition), 0.003f));
			m_InitialMousePosition = DirectX::XMLoadFloat2(&mouse);

			if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
				MousePan(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
				MouseRotate(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
				MouseZoom(delta.y);
		}

		UpdateView();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(DXR_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float delta = e.GetYOffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}

	void EditorCamera::MousePan(const DirectX::XMFLOAT2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();

		m_FocalPoint = DirectX::XMVectorAdd(m_FocalPoint, DirectX::XMVectorScale(DirectX::XMVectorScale(
			DirectX::XMVectorScale(DirectX::XMVectorScale(GetRightDirection(), -1), delta.x), xSpeed), m_Distance));

		m_FocalPoint = DirectX::XMVectorAdd(m_FocalPoint, DirectX::XMVectorScale(DirectX::XMVectorScale(
			DirectX::XMVectorScale(GetUpDirection(), delta.y), ySpeed), m_Distance));
	}

	void EditorCamera::MouseRotate(const DirectX::XMFLOAT2& delta)
	{
		DirectX::XMFLOAT3 temp;
		DirectX::XMStoreFloat3(&temp, GetUpDirection());
		float yawSign = temp.y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * m_RotationSpeed;
		m_Pitch += delta.y * m_RotationSpeed;
	}

	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint = DirectX::XMVectorAdd(m_FocalPoint, GetForwardDirection());
			m_Distance = 1.0f;
		}
	}

	DirectX::XMVECTOR EditorCamera::GetUpDirection() const
	{
		return DirectX::XMVector3Rotate(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), GetOrientation());
	}

	DirectX::XMVECTOR EditorCamera::GetRightDirection() const
	{
		return DirectX::XMVector3Rotate(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), GetOrientation());
	}

	DirectX::XMVECTOR EditorCamera::GetForwardDirection() const
	{
		return DirectX::XMVector3Rotate(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), GetOrientation());
	}

	DirectX::XMVECTOR EditorCamera::CalculatePosition() const
	{
		return DirectX::XMVectorSubtract(m_FocalPoint,
			DirectX::XMVectorScale(GetForwardDirection(), m_Distance));
	}

	DirectX::XMVECTOR  EditorCamera::GetOrientation() const
	{
		DirectX::XMFLOAT3 euler(m_Pitch, m_Yaw, 0.0f);
		return DirectX::XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&euler));
	}
}