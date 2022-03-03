#pragma once
#include "Borg/UI/Handle.h"
#include "Borg/UI/Message.h"
#include "Borg/Events.h"
#include "CreateParams.h"

namespace Borg::UI::Windows
{
    class NativeWindow
    {
    public:
        ~NativeWindow();
        UI::Handle Handle() const;

        void WrapHandle(const UI::Handle &handle);
        void CreateHandle(const CreateParams &cp);
        LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        Borg::Event<Message &> OnMessage;
    private:
        void registerWindowClass(const CreateParams &cp);
        void destroyHandle();
        void releaseHandle();
        
        bool m_IsWrapped{ false };
        UINT_PTR m_SubClassWndProcId;
        UI::Handle m_Handle = nullptr;
    };
}