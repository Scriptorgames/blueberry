#pragma once

#include <string>

namespace blueberry
{
    namespace widgets
    {
        struct Widget
        {
            Widget();
            virtual ~Widget() {}

            virtual bool Render() = 0;

            std::string RosTopic;
        };

        struct Image : Widget
        {
            bool Render() override;

            float Width, Height;
            void *Id;
        };

        struct Log : Widget
        {
            bool Render() override;
        };

        struct Diagram : Widget
        {
            bool Render() override;
        };

        struct Terminal : Widget
        {
            bool Render() override;
        };

        namespace joysticks
        {
            struct KnobAndSpeedSlider : Widget
            {
                bool Render() override;
            };

            struct TwoSliders : Widget
            {
                bool Render() override;
            };

            struct TouchField : Widget
            {
                bool Render() override;
            };
        }

        namespace values
        {
            struct Value : Widget
            {
                bool Render() override;
            };

            struct Scale : Widget
            {
                bool Render() override;
            };
        }
    }
}
