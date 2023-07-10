#include "pch.h"
#include "DX11Shader.h"
#include "DX11Context.h"
#include "Platform/DXCommon.h"

#include <fstream>
#include <d3dcompiler.h>

namespace DXC
{
	DX11Shader::DX11Shader(const std::string& name) : m_Name(name)
	{
		std::string vs = "assets/shaders/cache/" + name + "_v.cso";
		std::string ps = "assets/shaders/cache/" + name + "_p.cso";
		std::wstring vertexShader(vs.begin(), vs.end());
		std::wstring pixelShader(ps.begin(), ps.end());
		DX_CHECK_RESULT(D3DReadFileToBlob(vertexShader.c_str(), m_VertexShaderBlob.GetAddressOf()));
		DX_CHECK_RESULT(DX11Context::GetDevice()->CreateVertexShader(m_VertexShaderBlob->GetBufferPointer(),
			m_VertexShaderBlob->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf()));

		Microsoft::WRL::ComPtr<ID3DBlob> blob;
		DX_CHECK_RESULT(D3DReadFileToBlob(pixelShader.c_str(), blob.GetAddressOf()));
		DX_CHECK_RESULT(DX11Context::GetDevice()->CreatePixelShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, m_PixelShader.GetAddressOf()));
	}

	void DX11Shader::Bind() const
	{
		DX11Context::GetDeviceContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		DX11Context::GetDeviceContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}

	void DX11Shader::Unbind() const
	{
		DX11Context::GetDeviceContext()->VSSetShader(nullptr, nullptr, 0);
		DX11Context::GetDeviceContext()->PSSetShader(nullptr, nullptr, 0);
	}

	DX11Shader::~DX11Shader()
	{
		m_VertexShader.Reset();
		m_PixelShader.Reset();
	}
}