#include <gtest/gtest.h>
#include <Windows.h>

enum class CarState : std::uint8_t {
    engine_on = 0b00000001,
    lights_on = 0b00000010,
    wipers_on = 0b00000100,
    // ...
};

CarState operator|(CarState lhs, CarState rhs) {
    return static_cast<CarState>(
        static_cast<std::underlying_type_t<CarState>>(lhs) |
        static_cast<std::underlying_type_t<CarState>>(rhs)
    );
}

CarState operator&(CarState lhs, CarState rhs) {
    return static_cast<CarState>(
        static_cast<std::underlying_type_t<CarState>>(lhs) &
        static_cast<std::underlying_type_t<CarState>>(rhs)
    );
}

template <typename EnumT>
class Flags {
    static_assert(std::is_enum_v<EnumT>, "Flags can only be specialized for enum types");

    using UnderlyingT = typename std::underlying_type_t<EnumT>;

public:
    Flags(EnumT flags) : flags(flags) {}

    bool has(EnumT flag) const {
        return (underlying(this->flags) & underlying(flag)) != 0;
    }

    Flags& operator|=(EnumT flag) {
        this->flags = ToFlag(underlying(this->flags) | underlying(flag));
        return *this;
    }

private:
    static constexpr UnderlyingT underlying(EnumT e) {
        return static_cast<UnderlyingT>(e);
    }

    static constexpr EnumT ToFlag(UnderlyingT e) {
        return static_cast<EnumT>(e);
    }

private:
    EnumT flags;
};

using CarStates = Flags<CarState>;

enum class RegistryView
{
    Default = 0, // 0x0000 operate on the default registry view
    Registry64 = KEY_WOW64_64KEY,
    Registry32 = KEY_WOW64_32KEY
};
using RegistryViewFlags = Flags<RegistryView>;

TEST(EnumFlag, RegistryViewTest)
{
    RegistryViewFlags view = RegistryView::Default;
    view |= RegistryView::Registry64;
    EXPECT_TRUE(view.has(RegistryView::Registry64));
    EXPECT_FALSE(view.has(RegistryView::Registry32));
}

TEST(EnumFlag, Blub)
{
    CarStates current = CarState::engine_on | CarState::lights_on;

    if (current.has(CarState::engine_on)) {
        std::cout << "We are ready to go!" << std::endl;
    }

    if (current.has(CarState::wipers_on)) {
        std::cout << "Oh, it's raining!" << std::endl;
    }

    current |= CarState::wipers_on;
    if (current.has(CarState::wipers_on)) {
        std::cout << "Oh, it's raining!" << std::endl;
    }
}