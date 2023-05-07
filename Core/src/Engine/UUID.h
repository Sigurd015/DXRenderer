#pragma once
#include <random>
#include <unordered_map>

namespace DXR
{
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint32_t> s_UniformDistribution;

	class UUID
	{
	public:
		UUID() : m_UUID(s_UniformDistribution(s_Engine)) {}
		UUID(uint32_t uuid) : m_UUID(uuid) {}
		UUID(const UUID&) = default;

		operator uint32_t() const { return m_UUID; }
	private:
		uint32_t m_UUID;
	};
}
namespace std
{
	template<>
	struct hash<DXR::UUID>
	{
		std::size_t operator()(const DXR::UUID& uuid) const
		{
			return (uint32_t)uuid;
		}
	};

}