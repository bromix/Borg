#pragma once
#include "ArrayBuffer.h"
#include "IStringBuffer.h"
#include <string_view>

namespace Borg
{
    template <typename T>
    class AbstractStringBuffer : public IStringBuffer, protected ArrayBuffer<T>
    {
    public:
        /**
         * @brief Empty default constructor.
         */
        AbstractStringBuffer() : ArrayBuffer<T>() {}

        AbstractStringBuffer(const AbstractStringBuffer<T> &input) : ArrayBuffer<T>(input) {}

        AbstractStringBuffer(AbstractStringBuffer<T> &&input) : ArrayBuffer<T>(std::move(input)) {}

        /**
         * @brief Creates a StringBuffer with the given length of "characters".
         * @remark The length will be calculated into ByteLength for the internal buffer.
         *
         * @param length
         */
        AbstractStringBuffer(std::size_t length) : ArrayBuffer<T>((length + 1) * sizeof(T))
        {
            m_Ptr[length] = '\0';
        }

        AbstractStringBuffer(std::basic_string_view<T> input, bool createCopy = false)
            : ArrayBuffer<T>()
        {
            // we add +1 because of the null-termination.
            m_ByteLength = (input.length() + 1) * sizeof(T);

            if (createCopy)
            {
                m_IsDetached = false;
                m_Ptr = new T[m_ByteLength];
                m_Ptr[input.length()] = '\0'; // we must add the null-termination while copying.
                memcpy_s(m_Ptr, m_ByteLength, input.data(), input.length() * sizeof(T));
            }
            else
            {
                m_IsDetached = true;
                m_Ptr = const_cast<T *>(input.data());
            }
        }

        bool IsEmpty() const override
        {
            return Length() == 0;
        }

        /**
         * @brief Returns the length of the StringBuffer without the null-termination.
         *
         * @return std::size_t
         */
        std::size_t Length() const override
        {
            auto length = ArrayBuffer<T>::Length();
            return length > 0 ? length - 1 : 0;
        }

        std::size_t ByteLength() const override
        {
            return ArrayBuffer<T>::ByteLength();
        }

        operator std::basic_string_view<T>() const
        {
            return m_Ptr;
        }

        operator T *() const
        {
            return m_Ptr;
        }

        T *Data() const
        {
            return m_Ptr;
        }

        /**
         * @brief Detaches the StringBuffer from the underlying Buffer.
         * @remark This will not free resources after the ArrayBuffer is out of scope or deleted.
         * @remark The caller must free the resource.
         *
         * @return StringBuffer<T>&
         */
        AbstractStringBuffer<T> &Detach()
        {
            ArrayBuffer<T>::Detach();
            return *this;
        }

        T &operator[](std::size_t index)
        {
            // TODO: check index
            return m_Ptr[index];
        }

        virtual Ref<IStringBuffer> ToLower() const override
        {
            throw NotSupportException();
        }

        virtual Ref<IStringBuffer> ToUpper() const override
        {
            throw NotSupportException();
        }

        virtual Ref<IStringBuffer> Insert(int startIndex, const Ref<IStringBuffer> &value) const  override
        {
            throw NotSupportException();
        }

        virtual Ref<IStringBuffer> Insert(int startIndex, std::string_view value) const  override
        {
            throw NotSupportException();
        }

        virtual Ref<IStringBuffer> Insert(int startIndex, std::wstring_view value) const  override
        {
            throw NotSupportException();
        }

        virtual bool StartsWith(const Ref<IStringBuffer> &text) const  override
        {
            throw NotSupportException();
        }

        virtual bool StartsWith(std::string_view text) const  override
        {
            throw NotSupportException();
        }

        virtual bool StartsWith(std::wstring_view text) const  override
        {
            throw NotSupportException();
        }
        
        virtual bool EndsWith(const Ref<IStringBuffer> &text) const  override
        {
            throw NotSupportException();
        }

        virtual bool EndsWith(std::string_view text) const  override
        {
            throw NotSupportException();
        }

        virtual bool EndsWith(std::wstring_view text) const  override
        {
            throw NotSupportException();
        }

        virtual int CompareTo(const Ref<IStringBuffer> &rhs) const  override
        {
            throw NotSupportException();
        }

        virtual int CompareTo(std::string_view rhs) const  override
        {
            throw NotSupportException();
        }

        virtual int CompareTo(std::wstring_view rhs) const  override
        {
            throw NotSupportException();
        }

        virtual operator std::string() const  override
        {
            throw NotSupportException();
        }

        virtual operator std::wstring() const  override
        {
            throw NotSupportException();
        }

        virtual Ref<IStringBuffer> Clone() const  override
        {
            throw NotSupportException();
        }
        
        AbstractStringBuffer<T> &operator=(const AbstractStringBuffer<T> &input)
        {
            ArrayBuffer<T>::operator=(input);
            return *this;
        }

        AbstractStringBuffer<T> &operator=(AbstractStringBuffer<T> &&input)
        {
            ArrayBuffer<T>::operator=(std::move(input));
            return *this;
        }
    };
}