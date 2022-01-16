#pragma once
#include <map>
#include "Borg/Types.h"
#include "Borg/UI/Message.h"
#include "Borg/String.h"
#include "Borg/UI/Handle.h"

namespace Borg::UI
{
    class ClassFactory final
    {
    public:
        static UI::Handle Create(CREATESTRUCTW &cs, UINT classStyle, Func<LRESULT, const UI::Message&>&& onMessage);

    private:
        ClassFactory() = default;
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static UI::Handle createClass(CREATESTRUCTW &cs, Func<LRESULT, const UI::Message&>&& onMessage);
        static bool isRegistered(const String &className);
        static void registerClass(CREATESTRUCTW &cs, UINT classStyle);

        inline static std::map<String, ATOM> m_RegisteredClasses;
    };
}