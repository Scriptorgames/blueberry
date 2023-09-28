#include "manager.h"

#include <imgui/imgui.h>

#include <string>

blueberry::Manager *blueberry::Manager::__instance = nullptr;

blueberry::Manager &blueberry::Manager::Create()
{
    if (!__instance)
        return *(__instance = new Manager());

    throw;
}

blueberry::Manager &blueberry::Manager::Get()
{
    if (__instance)
        return *__instance;

    throw;
}

blueberry::Manager &blueberry::Manager::GetOrCreate()
{
    if (__instance)
        return Get();

    return Create();
}

void blueberry::Manager::Destroy()
{
    if (__instance)
    {
        delete __instance;
        __instance = nullptr;
        return;
    }

    throw;
}

blueberry::Manager &blueberry::Manager::AddWidget(Widget *widget)
{
    m_Widgets.push_back(widget);

    return *this;
}

blueberry::Widget *blueberry::Manager::GetWidget(size_t index)
{
    return m_Widgets[index];
}

size_t blueberry::Manager::GetWidgetCount() const
{
    return m_Widgets.size();
}

blueberry::Manager &blueberry::Manager::Draw()
{
    if (ImGui::Begin("Widget Manager"))
    {
        ImGui::Text("Widget Count: %ld", GetWidgetCount());
        if (ImGui::CollapsingHeader("Widgets"))
        {
            for (size_t i = 0; i < m_Widgets.size(); i++)
            {
                Widget *widget = m_Widgets[i];

                std::string id = widget->Label() + "_open";
                ImGui::Checkbox(id.c_str(), &widget->Open());
                ImGui::SameLine();

                id = "Destroy##destroy_" + std::to_string(i);
                if (ImGui::Button(id.c_str()))
                {
                    m_Widgets.erase(m_Widgets.begin() + i);
                    if (i != 0)
                        i--;
                }
            }
        }
    }
    ImGui::End();

    for (size_t i = 0; i < m_Widgets.size(); i++)
    {
        if (!m_Widgets[i]->Open())
            continue;

        m_Widgets[i]->Draw();
    }

    return *this;
}