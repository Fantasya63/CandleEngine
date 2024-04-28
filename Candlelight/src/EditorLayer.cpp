#include "EditorLayer.h"

namespace Candle {

    EditorLayer::EditorLayer()
        : Layer("Editor Layer")
    {
        m_SquareTexture = Texture2D::Create("Assets/textures/2_Close_Up.png");
        
        FramebufferSpecification framebufferSpec;
        framebufferSpec.Width = 1280;
        framebufferSpec.Height = 720;
        framebufferSpec.Attachments = {
            FramebufferTextureSpecification(FramebufferTextureFormat::RGBA8),
        };

        m_Framebuffer = Framebuffer::Create(framebufferSpec);
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        // Viewport
        if (m_ViewportPanelResized)
        {
            m_Framebuffer->Resize((uint32_t)m_LastViewportPanelSize.x, (uint32_t)m_LastViewportPanelSize.y);
            m_Camera2D.ResizeBounds(m_LastViewportPanelSize.x, m_LastViewportPanelSize.y);

            m_ViewportPanelResized = false;
        }

        // Update
        
        if (m_ViewportFocused)
        {
            m_Camera2D.Update(ts);
        }
        

        m_Rotation += glm::radians(m_RotationSpeed) * ts.GetSeconds();

        // Renderer
        {
            CD_PROFILE_SCOPE("Renderer Prep");
            
            m_Framebuffer->Bind();

            RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
            RenderCommand::Clear();
        }

        Renderer2D::BeginScene(m_Camera2D);
        {
            Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Color);
            Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, m_SquareTexture, m_TextureTiling, m_Color);
            Renderer2D::DrawRotatedQuad({ 2.0f, 0.0f }, { 1.0f, 1.0f }, m_Rotation, m_Color);
            Renderer2D::DrawRotatedQuad({ 2.0f, 1.0f }, { 1.0f, 1.0f }, -m_Rotation, m_SquareTexture, m_TextureTiling, m_Color);
        
           
        }
        Renderer2D::EndScene();
        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        // If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
        // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
        // In this specific demo, we are not using DockSpaceOverViewport() because:
        // - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
        // - we allow the host window to have padding (when opt_padding == true)
        // - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
        // TL;DR; this demo is more complicated than what you would normally use.
        // If we removed all the options we are showcasing, this demo would become:
        //     void ShowExampleAppDockSpace()
        //     {
        //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        //     }

        // Candle
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_peristant = true;


        static bool opt_fullscreen = opt_fullscreen_peristant;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.

                // Candle
                /*ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();*/

                if (ImGui::MenuItem("Exit", NULL, false, true))
                {
                    Application::Get().Close();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }


        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
        ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 360.0f);
        ImGui::InputFloat2("Tiling Input", glm::value_ptr(m_TextureTiling), "%.1f");
        ImGui::End();

        // Viewport
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Scene Viewport");
        

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->AllowEvents(m_ViewportHovered);


        // Get Viewport size
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        
        // Check if we have resized the viewport
        if (m_LastViewportPanelSize != *(glm::vec2*)&viewportPanelSize)
        {
            m_ViewportPanelResized = true;
            m_LastViewportPanelSize = { viewportPanelSize.x, viewportPanelSize.y };
        }

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID(0);
        ImGui::Image((void*)textureID, viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
        
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }
}