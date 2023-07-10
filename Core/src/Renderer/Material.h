#pragma once
#include "Core/Base.h"
#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <string>

namespace DXC
{
	class Material
	{
	public:
		Material(const Ref<Shader>& shader);
		virtual ~Material();
		void Bind() const;
		void SetTexture(const Ref<Texture>& texture, uint32_t index);

		void SetTexture(const Ref<Texture2D>& texture, uint32_t index)
		{
			SetTexture((const Ref<Texture>&)texture, index);
		}

		static Ref<Material> Create(const Ref<Shader>& shader);
	private:
		void BindTextures() const;

		Ref<Shader> m_Shader;
		std::unordered_map<uint32_t, Ref<Texture>> m_Textures;
	};
}