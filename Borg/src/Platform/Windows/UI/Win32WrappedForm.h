#include "Borg/UI/IForm.h"

namespace Borg::UI
{
    class Win32WrappedForm : public IForm
    {
    public:
        Win32WrappedForm(const UI::Handle &handle);

        // Form
    public:
        Ref<IForm> GetOwner() const override;
        void SetOpacity(double opacity) override;
        double GetOpacity() const override;
        void SetFormBorderStyle(FormBorderStyle style) override;
        UI::FormBorderStyle GetFormBorderStyle() const override;
        void CenterToParent() override;
        void CenterToScreen() override;
        void SetShowInTaskbar(bool show) override;
        bool GetShowInTaskbar() const override;
        void Close() override;
        void Show() override;
        UI::DialogResult ShowDialog() override;
        void SetDialogResult(UI::DialogResult dialogResult) override;
        UI::DialogResult GetDialogResult() const override;
#ifdef _WIN32
        void DragMove() override;
#endif

        static Ref<UI::IForm> CreateFrom(const UI::Handle &handle);

    protected:
        UI::DialogResult m_DialogResult{DialogResult::None};
        void onClosed(const UI::FormClosedEventArgs &e) override;

        // Control
    public:
        UI::Handle Handle() const override;
        void SetText(const String &text) override;
        Borg::Ref<UI::IControl> GetParent() const override;
        int DeviceDpi() const override;
        void BringToFront() override;
        bool IsEnabled() const override;
        void SetEnabled(bool enabled) override;
        bool IsVisible() const override;
        void SetVisible(bool visible) override;
        void SetBackColor(const Drawing::Color &color) override;
        Drawing::Color GetBackColor() const override;
        Drawing::Rectangle GetBounds() const override;
        Drawing::Size GetSize() const override;
        void SetSize(const Drawing::Size &size) override;
        Drawing::Rectangle GetClientRectangle() const override;
        Drawing::Size GetClientSize() const override;
        Drawing::Point GetLocation() const override;
        void SetLocation(const Drawing::Point &point) override;
        void Invalidate() override;

    protected:
        class ControlImpl;
        Ref<ControlImpl> m_Impl;
        void onSizeChanged(EventArgs e) override;
        void onMessage(UI::Message &message) override;

    protected:
        UI::Handle m_Handle;
    };
}