#pragma once
#include "Engine/Base.h"

#include <unordered_map>
#include <string>

namespace DXR
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;
		virtual void SetUniform(const std::string& name, int value) = 0;
		virtual void SetUniform(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetUniform(const std::string& name, float value) = 0;
		static Ref<Shader> Create(const std::string& filepath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}