#pragma once
#include "Base.h"
#include "Events/Event.h"
#include "Timestep.h"

namespace DXR
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& evnet) {}
		virtual void OnImGuiRender() {}
		const std::string& GetName()const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}