#pragma once

#include "imgui/imgui.h"

#include "manager.h"

#include <string>

namespace blueberry
{
    class Terminal : public Widget
    {
    public:
        Terminal(const char *ros_topic = nullptr, size_t id = 0);
        ~Terminal();

        void ClearLog();
        void AddLog(const char *fmt, ...) IM_FMTARGS(2);
        void Draw();
        bool &Open();
        std::string &Label();

    private:
        // Portable helpers //
        static int Stricmp(const char *s1, const char *s2);
        static int Strnicmp(const char *s1, const char *s2, int n);
        static char *Strdup(const char *s);
        static void Strtrim(char *s);

    private:
        char m_InputBuf[256];
        ImVector<char *> m_Items;
        ImGuiTextFilter m_Filter;
        bool m_AutoScroll;
        bool m_ScrollToBottom;

        std::string m_Label;
        bool m_Open = true;
    };
}