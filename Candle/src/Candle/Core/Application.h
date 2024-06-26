#pragma once

#include "Window.h"
#include "Candle/Core/LayerStack.h"
#include "Candle/Events/ApplicationEvent.h"
#include "Candle/Events/Event.h"
#include "Candle/imgui/ImGuiLayer.h"
#include "Candle/Core/Timestep.h"

namespace Candle {
	class Application
	{
	public:
		Application(const std::string& name = "Candle App");
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();
		void Close() { m_Running = false; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_WindowMinimized = false;

		LayerStack m_LayerStack;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

