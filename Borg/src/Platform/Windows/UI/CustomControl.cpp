#include "Borg/UI/CustomControl.h"
#include "ClassFactory.h"

namespace Borg::UI
{
    CustomControl::CustomControl(const UI::IControl& parent, const String &className)
    {
        UI::Handle hParent = parent.Handle() ? parent.Handle() : nullptr;

        CREATESTRUCTW cs{0};
        cs.lpszClass = Encoding::Convert<WideCharBuffer>(className);
        cs.style = CS_DBLCLKS | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
        cs.dwExStyle = WS_EX_LEFT;
        cs.hwndParent = hParent;
        cs.x = 50;
        cs.y = 50;
        cs.cx = 100;
        cs.cy = 100;
        m_Handle = ClassFactory::Create(cs, [this](const UI::Message &message)
                                        { return this->onMessage(message); });
    }
}