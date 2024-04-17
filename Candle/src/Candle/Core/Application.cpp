#include "cdpch.h"

#include "Application.h"

#include "Candle/Core/Log.h"
#include "Candle/Core/Platform.h"
#include "Candle/Renderer/Renderer.h"


namespace Candle
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		CD_PROFILE_FUNCTION();

		CD_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		CD_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::OnEvent(Event& e)
	{


		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run()
	{
		CD_PROFILE_FUNCTION();

		while (m_Running)
		{
			float time = Time::GetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_WindowMinimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(ts);
				}
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		//Set event As Handled
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		CD_PROFILE_FUNCTION();

		uint32_t width, height;
		width = e.GetWidth();
		height = e.GetHeight();

		if (width == 0 || height == 0)
		{
			m_WindowMinimized = true;
			return false;
		}

		m_WindowMinimized = false;

		// Notify the Renderer
		Renderer::OnWindowResized(width, height);

		return false;
	}
}