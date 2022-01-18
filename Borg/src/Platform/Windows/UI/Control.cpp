#include "Borg/UI/Control.h"
#include "Borg/Exception.h"
#include "Borg/UI/DpiHelper.h"
#include "../Windows.h"
#include "ControlImpl.h"

namespace Borg::UI
{
    Control::~Control()
    {
    }

    Control::Control() : Control(nullptr) {}

    Control::Control(const Ref<UI::IControl> &parent)
    {
        m_Impl = CreateRef<ControlImpl>();
        m_Impl->OnMessage += [this](auto &message)
        {
            onMessage(message);
        };
        m_Impl->m_InternalParent = parent;
    }

    UI::Handle Control::Handle() const
    {
        return m_Impl->Handle();
    }

    void Control::SetText(const String &text)
    {
        ::SetWindowTextW(m_Impl->Handle(), Encoding::Convert<WideCharBuffer>(text));
    }

    Ref<UI::IControl> Control::GetParent() const
    {
        return m_Impl->m_InternalParent.lock();
    }

    int Control::DeviceDpi() const
    {
        return -1;
        // Ref<UI::IControl> thisControl = std::const_pointer_cast<UI::IControl>(shared_from_this());
        // return DpiHelper::FromControl(thisControl).DeviceDpi();
    }

    void Control::BringToFront()
    {
        ::BringWindowToTop(m_Impl->Handle());
    }

    bool Control::IsEnabled() const
    {
        return ::IsWindowEnabled(m_Impl->Handle()) == TRUE;
    }

    void Control::SetEnabled(bool enabled)
    {
        ::EnableWindow(m_Impl->Handle(), enabled ? TRUE : FALSE);
    }

    bool Control::IsVisible() const
    {
        return ::IsWindowVisible(m_Impl->Handle()) == TRUE;
    }

    void Control::SetVisible(bool visible)
    {
        ::ShowWindow(m_Impl->Handle(), SW_SHOWDEFAULT);
    }

    void Control::SetBackColor(const Drawing::Color &color)
    {
        m_Impl->m_BackgroundColor = color;
        Invalidate();
    }

    Drawing::Color Control::GetBackColor() const
    {
        return m_Impl->m_BackgroundColor;
    }

    Drawing::Rectangle Control::GetBounds() const
    {
        RECT rc{0};
        if (::GetWindowRect(m_Impl->Handle(), &rc) != TRUE)
            throw InvalidOperationException("::GetWindowRect did not return TRUE.");

        return Drawing::Rectangle(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    }

    Drawing::Size Control::GetSize() const
    {
        return GetBounds().GetSize();
    }

    void Control::SetSize(const Drawing::Size &size)
    {
        ::SetWindowPos(m_Impl->Handle(), nullptr, 0, 0, size.Width, size.Height, SWP_NOMOVE | SWP_NOREPOSITION);
    }

    Drawing::Rectangle Control::GetClientRectangle() const
    {
        RECT rc{0};
        if (::GetClientRect(m_Impl->Handle(), &rc) != TRUE)
            throw InvalidOperationException("::GetClientRect did not return TRUE.");

        return Drawing::Rectangle(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    }

    Drawing::Size Control::GetClientSize() const
    {
        return GetClientRectangle().GetSize();
    }

    Drawing::Point Control::GetLocation() const
    {
        return GetBounds().GetLocation();
    }

    void Control::SetLocation(const Drawing::Point &point)
    {
        ::SetWindowPos(m_Impl->Handle(), nullptr, point.X, point.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }

    void Control::Invalidate()
    {
        if (IsVisible())
            ::RedrawWindow(m_Impl->Handle(), nullptr, nullptr, RDW_ERASE | RDW_INVALIDATE);
    }

    Ref<IControl> Control::CreateFrom(const UI::Handle &handle)
    {
        return nullptr;
        // Ref<Control> control = CreateRef<Control>();
        // control->m_Handle = handle;
        // return control;
    }

    void Control::onSizeChanged(EventArgs e)
    {
        // TODO: invoke EventHandler
        OutputDebugStringA("onSizeChanged\n");
    }

    void Control::onMessage(UI::Message &message)
    {
        switch (message.Msg)
        {
        case WM_ERASEBKGND:
        {
            auto hdc = (HDC)message.WParam;
            RECT rc;
            GetClientRect(m_Impl->Handle(), &rc);
            HBRUSH brush = ::CreateSolidBrush(GetBackColor().ToBgr());
            FillRect(hdc, &rc, brush);
            message.Result = 1;
            return;
        }
        case WM_ENTERSIZEMOVE:
            OutputDebugStringA("WM_ENTERSIZEMOVE\n");
            break;
        case WM_EXITSIZEMOVE:
            OutputDebugStringA("WM_EXITSIZEMOVE\n");
            break;
        case WM_SIZE:
        {
            switch (message.WParam)
            {
            case SIZE_MINIMIZED:
                OutputDebugStringA("Minimizing\n");
                break;
            case SIZE_MAXIMIZED:
                OutputDebugStringA("Maximizing\n");
                break;
            // case SIZE_RESTORED:
            //     OutputDebugStringA("Restoring\n");
            //     break;
            default:
                onSizeChanged({});
                break;
            }
        }
        break;
        }

        message.Result = DefWindowProcW(message.Handle, message.Msg, message.WParam, message.LParam);
    }
}