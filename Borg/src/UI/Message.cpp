#include "Borg/UI/Message.h"

namespace Borg::UI
{
#ifdef _WIN32
    Message::Message(const UI::Handle &handle, UINT msg, WPARAM wParam, LPARAM lParam)
        : Handle(handle), Msg(msg), WParam(wParam), LParam(lParam)
    {
    }
#endif
}