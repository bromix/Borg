#include "Borg/UI/CustomControl.h"
#include "ClassFactory.h"

namespace Borg::UI
{
    CustomControl::CustomControl(const String &className)
    {
        //UI::Handle hOwner = owner ? owner->Handle() : nullptr;
        UI::Handle hOwner = nullptr;

        CREATESTRUCTW cs{0};
        cs.lpszClass = Encoding::Convert<WideCharBuffer>(className);
        cs.style = CS_HREDRAW | CS_VREDRAW | WS_OVERLAPPED;
        cs.dwExStyle = WS_EX_LEFT;
        cs.hwndParent = hOwner;
        cs.x = CW_USEDEFAULT;
        cs.y = CW_USEDEFAULT;
        cs.cx = CW_USEDEFAULT;
        cs.cy = CW_USEDEFAULT;
        m_Handle = ClassFactory::Create(cs, [this](const UI::Message &message)
                                        { return this->onMessage(message); });
    }
}