#pragma once

#include "Core.h"
#include "Window.h"
#include "Candle/LayerStack.h"
#include "Candle/Events/Event.h"
#include "Candle/Events/ApplicationEvent.h"

#include "Candle/imgui/ImGuiLayer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

