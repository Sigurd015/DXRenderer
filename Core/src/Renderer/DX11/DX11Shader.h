#pragma once
#include "Renderer/Shader.h"

#include <string>
#include <d3d11.h>
#include <wrl.h>

namespace DXR
{
	enum ShaderType
	{
		UNKNOWN = 0, VERTEX_SHADER, PIXEL_SHADER
	};

	class DX11Shader :public Shader
	{
	public:
		DX11Shader(const std::string& name);
		~DX11Shader();
		void Bind() const override;
		void Unbind() const override;
		const std::string& GetName() const override { return m_Name; }
		LPVOID GetVertextBufferPointer() { return m_VertexShaderBlob->GetBufferPointer(); }
		SIZE_T GetVertextBufferSize() { return m_VertexShaderBlob->GetBufferSize(); }
	private:
		std::string m_Name;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> m_VertexShaderBlob;
	};
}