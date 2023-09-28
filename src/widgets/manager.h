#pragma once

#include <stddef.h>
#include <string>
#include <tuple>
#include <vector>

namespace blueberry
{
    struct Widget
    {
        virtual ~Widget() {}
        virtual void Draw() = 0;
        virtual bool &Open() = 0;
        virtual std::string &Label() = 0;
    };

    class Manager
    {
    public:
        static Manager &Create();
        static Manager &Get();
        static Manager &GetOrCreate();
        static void Destroy();

    private:
        static Manager *__instance;

    private:
        Manager() {}
        ~Manager()
        {
            for (auto widget : m_Widgets)
                delete widget;
        }

    public:
        Manager &AddWidget(Widget *widget);
        Widget *GetWidget(size_t index);
        size_t GetWidgetCount() const;
        Manager &Draw();

    private:
        std::vector<Widget *> m_Widgets;
    };
}