#include "cdpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include "Candle/Application.h"

namespace Candle
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		//IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	  // Enable Gamepad Controls
		io.DisplaySize = ImVec2(1200, 720);

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)&Application::Get().GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		float time = (float)glfwGetTime();
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		Application& app = Application::Get();
		io.DisplaySize = ImVec2(1200, 720);

		static bool showDemoWindow = true;
		ImGui::ShowDemoWindow(&showDemoWindow);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
	}
}