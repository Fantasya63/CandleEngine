#pragma once

#include "Core.h"
#include "Window.h"
#include "Candle/LayerStack.h"
#include "Candle/Events/Event.h"
#include "Candle/Events/ApplicationEvent.h"

namespace Candle {
	class CANDLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in client
	Application* CreateApplication();
}

