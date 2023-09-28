#include "creator.h"

void blueberry::Creator::Render(const char *id, bool *p_open)
{
    Manager &manager = Manager::GetOrCreate();

    if (ImGui::Begin("Widget Creator", p_open))
    {
        ImGui::InputTextWithHint("##ros topic", "ros topic", m_RosTopic, 100);

        if (ImGui::BeginTabBar(id, ImGuiTabBarFlags_FittingPolicyScroll))
        {
            if (ImGui::BeginTabItem("Virtual Joystick"))
            {
                if (ImGui::BeginTabBar("##virtual joystick types"))
                {
                    if (ImGui::BeginTabItem("One Knob + Speed Slider"))
                    {
                        if (ImGui::Button("Create"))
                        {
                        }

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Two Sliders"))
                    {
                        if (ImGui::Button("Create"))
                        {
                        }

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Touch Field"))
                    {
                        ImGui::Checkbox("Circle", &m_VirtualJoystickTouchFieldCircle);

                        if (ImGui::Button("Create"))
                        {
                        }

                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Camera | Image View"))
            {
                if (ImGui::Button("Create"))
                {
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Value Display"))
            {
                if (ImGui::BeginTabBar("##value display types"))
                {
                    if (ImGui::BeginTabItem("One Value"))
                    {
                        if (ImGui::Button("Create"))
                        {
                        }

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Point Cloud"))
                    {
                        ImGui::Checkbox("Line Connections", &m_ValueDisplayPointCloudLines);
                        ImGui::Checkbox("3D Cloud", &m_ValueDisplayPointCloud3D);

                        if (ImGui::Button("Create"))
                        {
                        }

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Scale"))
                    {
                        static const char *scale_types[] = {
                            "Horizontal Bar",
                            "Vertical Bar",
                            "Half Circle",
                            "Full Circle",
                        };

                        if (ImGui::BeginCombo("##scale type", scale_types[m_ValueDisplayScaleSelected]))
                        {
                            for (size_t i = 0; i < IM_ARRAYSIZE(scale_types); i++)
                            {
                                if (ImGui::Selectable(scale_types[i], m_ValueDisplayScaleSelected == i))
                                    m_ValueDisplayScaleSelected = i;
                                else
                                    ImGui::SetItemDefaultFocus();
                            }

                            ImGui::EndCombo();
                        }

                        if (ImGui::Button("Create"))
                        {
                        }

                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Log View"))
            {
                if (ImGui::Button("Create"))
                {
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Diagram"))
            {
                if (ImGui::Button("Create"))
                {
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Ray Display"))
            {
                if (ImGui::Button("Create"))
                {
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Input Terminal"))
            {
                if (ImGui::Button("Create"))
                {
                    manager.AddWidget(new blueberry::Terminal(m_RosTopic, Manager::Get().GetWidgetCount()));
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Object View"))
            {
                if (ImGui::Button("Create"))
                {
                }

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
    ImGui::End();
}