#pragma once

#include "Candle/Core/Layer.h"
#include "Candle/Events/ApplicationEvent.h"
#include "Candle/Events/MouseEvent.h"
#include "Candle/Events/KeyEvent.h"



namespace Candle
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& e) override;

        void Begin();
        void End();

        void AllowEvents(bool value) { m_AllowEvents = value; }
    private:
        bool m_AllowEvents = false;

        float m_Time = 0.0f;
    };
}
