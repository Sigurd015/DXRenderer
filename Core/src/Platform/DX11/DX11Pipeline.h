#pragma once
#include "Renderer/Pipeline.h"
#include "Renderer/IndexBuffer.h"

#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>

namespace DXR
{
	class DX11Pipeline : public Pipeline
	{
	public:
		DX11Pipeline(const PipelineSpecification& spec);
		~DX11Pipeline() = default;
		void Invalidate() override;
		void Bind() override;
		void SetConstantBuffer(const Ref<ConstantBuffer>& constantBuffer) override;
		Ref<ConstantBuffer> GetConstantBuffer(uint32_t binding) override;
		PipelineSpecification& GetSpecification() override;
		const PipelineSpecification& GetSpecification() const override;
	private:
		PipelineSpecification m_Specification;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
		std::vector<Ref<ConstantBuffer>> m_ConstantBuffers;
	};
}