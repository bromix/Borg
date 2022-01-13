#pragma once
#include "Borg/Color.h"
#include "Borg/Ref.h"
#include "DialogResult.h"
#include "IControl.h"

namespace Borg::UI
{
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
         * @brief Sets the form that owns this form.
         *
         * @param owner
         */
        virtual void SetOwner(const Ref<IForm> &owner) = 0;

        /**
         * @brief Centers the position of the form within the bounds of the parent form.
         */
        virtual void CenterToParent() = 0;

        /**
         * @brief Centers the form on the current screen.
         */
        virtual void CenterToScreen() = 0;

        /**
         * @brief Shows the form as a modal dialog box.
         *
         * @return DialogResult
         */
        virtual DialogResult ShowDialog() = 0;

        /**
         * @brief Sets the background color for the control.
         *
         * @param color
         */
        virtual void SetBackColor(const Color &color) = 0;

        /**
         * @brief Gets the background color for the control.
         *
         * @return Color
         */
        virtual Color GetBackColor() const = 0;
    };
}