#pragma once

#include <stddef.h>

#include "imgui/imgui.h"

#include "manager.h"
#include "terminal.h"

namespace blueberry
{
    class Creator
    {
    public:
        void Render(const char *id, bool *p_open = nullptr);

    private:
        char m_RosTopic[100] = "";
        bool m_VirtualJoystickTouchFieldCircle = false;
        bool m_ValueDisplayPointCloudLines = false;
        bool m_ValueDisplayPointCloud3D = false;
        size_t m_ValueDisplayScaleSelected = 0;
    };
}