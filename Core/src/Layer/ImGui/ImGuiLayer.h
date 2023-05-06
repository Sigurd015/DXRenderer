#pragma once
#include "Layer/Layer.h"
#include "Events/Event.h"

namespace DXR
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& e) override;
		void Begin();
		void End();
		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
	};
}