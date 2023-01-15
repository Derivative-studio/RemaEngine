#ifndef REMA_WINDOWSINPUT_H
#define REMA_WINDOWSINPUT_H

#include <RemaEngine/IO/Input.h>

namespace RemaEngine
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int a_nKeyCode) override;

        virtual bool IsMouseButtonPressedImpl(int a_nMouseButton) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}

#endif // !REMA_WINDOWSINPUT_H
