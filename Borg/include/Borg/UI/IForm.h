#pragma once
#include "Borg/Ref.h"
#include "DialogResult.h"
#include "IControl.h"

namespace Borg::UI
{
    class IForm : public IControl
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
         * @brief Shows the form as a modal dialog box.
         * 
         * @return DialogResult 
         */
        virtual DialogResult ShowDialog() = 0;

        /**
         * @brief Wraps the given Handle into a new instance of IForm.
         * 
         * @param handle 
         * @return Ref<IForm> 
         */
        static Ref<IForm> CreateFrom(const UI::Handle& handle);
    };
}