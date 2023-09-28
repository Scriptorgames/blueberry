#include "widgets.h"

#include "imgui/imgui.h"

blueberry::widgets::Widget::Widget()
{
}

bool blueberry::widgets::Image::Render()
{
    ImGui::Image((ImTextureID)Id, ImVec2(Width, Height));
    return true;
}
