#pragma once

#include "Core.h"
#include "Window.h"
#include "Candle/LayerStack.h"
#include "Candle/Events/Event.h"
#include "Candle/Events/ApplicationEvent.h"

#include "Candle/imgui/ImGuiLayer.h"

//Temporary
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

namespace Candle {
	class Application
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

		unsigned int m_VertexArray;

		//temp
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;


	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

