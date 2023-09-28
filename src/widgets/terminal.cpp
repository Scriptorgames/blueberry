#include "terminal.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>

blueberry::Terminal::Terminal(const char *ros_topic, size_t id)
{
    (void)ros_topic;

    m_Label = "Terminal##widget_terminal_" + std::to_string(id);

    ClearLog();
    memset(m_InputBuf, 0, sizeof(m_InputBuf));

    m_AutoScroll = true;
    m_ScrollToBottom = false;
    AddLog("Welcome to Dear ImGui!");
}

blueberry::Terminal::~Terminal()
{
    ClearLog();
}

void blueberry::Terminal::ClearLog()
{
    for (int i = 0; i < m_Items.Size; i++)
        free(m_Items[i]);
    m_Items.clear();
}

void blueberry::Terminal::AddLog(const char *fmt, ...)
{
    // FIXME-OPT
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);
    m_Items.push_back(Strdup(buf));
}

void blueberry::Terminal::Draw()
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(m_Label.c_str(), &m_Open))
    {
        ImGui::End();
        return;
    }

    // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
    // So e.g. IsItemHovered() will return true when hovering the title bar.
    // Here we create a context menu only available from the title bar.
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Close Terminal"))
            m_Open = false;

        ImGui::EndPopup();
    }

    if (ImGui::SmallButton("Clear"))
    {
        ClearLog();
    }
    ImGui::SameLine();
    bool copy_to_clipboard = ImGui::SmallButton("Copy");

    ImGui::Separator();

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &m_AutoScroll);
        ImGui::EndPopup();
    }

    // Options, Filter
    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
    m_Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
    ImGui::Separator();

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear"))
                ClearLog();
            ImGui::EndPopup();
        }

        // Display every line as a separate entry so we can change their color or add custom widgets.
        // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
        // to only process visible items. The clipper will automatically measure the height of your first item and then
        // "seek" to display only items in the visible area.
        // To use the clipper we can replace your standard loop:
        //      for (int i = 0; i < Items.Size; i++)
        //   With:
        //      ImGuiListClipper clipper;
        //      clipper.Begin(Items.Size);
        //      while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // - That your items are evenly spaced (same height)
        // - That you have cheap random access to your elements (you can access them given their index,
        //   without processing all the ones before)
        // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
        // We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
        // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
        // to improve this example code!
        // If your items are of variable height:
        // - Split them into same height items would be simpler and facilitate random-seeking into your list.
        // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        for (int i = 0; i < m_Items.Size; i++)
        {
            const char *item = m_Items[i];
            if (!m_Filter.PassFilter(item))
                continue;

            // Normally you would store more information in your item than just a string.
            // (e.g. make Items[] an array of structure, store color/type etc.)
            ImVec4 color;
            bool has_color = false;
            if (strstr(item, "[error]"))
            {
                color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
                has_color = true;
            }
            else if (strncmp(item, "# ", 2) == 0)
            {
                color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);
                has_color = true;
            }
            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item);
            if (has_color)
                ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if (m_ScrollToBottom || (m_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        m_ScrollToBottom = false;

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();
    ImGui::Separator();

    // Command-line
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll;
    if (ImGui::InputTextWithHint("Input", "type anything", m_InputBuf, IM_ARRAYSIZE(m_InputBuf), input_text_flags))
    {
        char *s = m_InputBuf;
        Strtrim(s);
        if (s[0])
            AddLog(s, nullptr);
        strcpy(s, "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    ImGui::End();
}

bool &blueberry::Terminal::Open()
{
    return m_Open;
}

std::string &blueberry::Terminal::Label()
{
    return m_Label;
}

// Portable helpers //

int blueberry::Terminal::Stricmp(const char *s1, const char *s2)
{
    int d;
    while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
    {
        s1++;
        s2++;
    }
    return d;
}

int blueberry::Terminal::Strnicmp(const char *s1, const char *s2, int n)
{
    int d = 0;
    while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
    {
        s1++;
        s2++;
        n--;
    }
    return d;
}

char *blueberry::Terminal::Strdup(const char *s)
{
    IM_ASSERT(s);
    size_t len = strlen(s) + 1;
    void *buf = malloc(len);
    IM_ASSERT(buf);
    return (char *)memcpy(buf, (const void *)s, len);
}

void blueberry::Terminal::Strtrim(char *s)
{
    char *str_end = s + strlen(s);
    while (str_end > s && str_end[-1] == ' ')
        str_end--;
    *str_end = 0;
}