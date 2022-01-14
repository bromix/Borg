#pragma once
#include "Borg/Ref.h"
#include "DialogResult.h"
#include "IControl.h"

namespace Borg::UI
{
    enum class FormBorderStyle
    {
        /**
         * @brief A fixed, three-dimensional border.
         */
        Fixed3D = 2,

        /**
         * @brief A thick, fixed dialog-style border.
         */
        FixedDialog = 3,

        /**
         * @brief A fixed, single-line border.
         */
        FixedSingle = 1,

        /**
         * @brief A tool window border that is not resizable. A tool window does not appear in the taskbar or in the window that appears when the user presses ALT+TAB. Although forms that specify FixedToolWindow typically are not shown in the taskbar, you must also ensure that the ShowInTaskbar property is set to false, since its default value is true.
         */
        FixedToolWindow = 5,

        /**
         * @brief No border.
         */
        None = 0,

        /**
         * @brief A resizable border.
         */
        Sizable = 4,

        /**
         * @brief A resizable tool window border. A tool window does not appear in the taskbar or in the window that appears when the user presses ALT+TAB.
         */
        SizableToolWindow = 6
    };

    class IForm : public virtual IControl
    {
    public:
        virtual ~IForm() = default;

        /**
         * @brief Gets the form that owns this form.
         *
         * @return Ref<IForm>
         */
        virtual Ref<IForm> GetOwner() const = 0;

        /**
         * @brief Sets the opacity level of the form.
         *
         * @param opacity The level of opacity for the form. The default is 1.00.
         */
        virtual void SetOpacity(double opacity) = 0;

        /**
         * @brief Gets the opacity level of the form.
         *
         * @return double The level of opacity for the form. The default is 1.00.
         */
        virtual double GetOpacity() const = 0;

        /**
         * @brief Sets the border style of the form.
         *
         * @param style
         */
        virtual void SetFormBorderStyle(UI::FormBorderStyle style) = 0;

        /**
         * @brief Gets the border style of the form.
         * 
         * @return FormBorderStyle 
         */
        virtual UI::FormBorderStyle GetFormBorderStyle() const = 0;

        /**
         * @brief Centers the position of the form within the bounds of the parent form.
         */
        virtual void CenterToParent() = 0;

        /**
         * @brief Centers the form on the current screen.
         */
        virtual void CenterToScreen() = 0;

        /**
         * @brief Sets a value indicating whether the form is displayed in the Windows taskbar.
         * 
         * @param show 
         */
        virtual void SetShowInTaskbar(bool show) = 0;

        /**
         * @brief Gets a value indicating whether the form is displayed in the Windows taskbar.
         * 
         * @return true 
         * @return false 
         */
        virtual bool GetShowInTaskbar() const = 0;

        /**
         * @brief Shows the form as a modal dialog box.
         *
         * @return DialogResult
         */
        virtual DialogResult ShowDialog() = 0;
    };
}