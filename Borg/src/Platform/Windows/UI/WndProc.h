#pragma once
#include "Borg/Types.h"
#include "Borg/UI/Message.h"
#include "../Windows.h"

namespace Borg::UI
{
    class WndProxy
    {
    public:
        WndProxy(const Func<LRESULT, const UI::Message &> &wndProc) : m_wndProc(wndProc)
        {
        }

        LRESULT operator()(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            return m_wndProc({hWnd, message, wParam, lParam});
        }

    private:
        Func<LRESULT, const UI::Message &> m_wndProc;
    };

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        WndProxy *wndProxy = nullptr;

        if (message == WM_NCCREATE)
        {
            LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
            wndProxy = static_cast<WndProxy *>(lpcs->lpCreateParams);
            ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wndProxy));
        }
        else
            wndProxy = reinterpret_cast<WndProxy *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

        if (wndProxy)
            return (*wndProxy)(hWnd, message, wParam, lParam);

        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
}