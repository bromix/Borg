#include "Borg/Borg.h"
#include <gtest/gtest.h>

using namespace Borg;

class IAnimal
{
public:
    virtual std::string Name() const = 0;
};

class Shark : public IAnimal
{
public:
    virtual std::string Name() const { return "Shark"; };
};

class IShape
{
public:
    virtual std::string Name() const = 0;
};

class Circle : public IShape
{
public:
    virtual std::string Name() const { return "Circle"; };
};

TEST(Ref, RefAsNotNull)
{
    Ref<IAnimal> animal = CreateRef<Shark>();
    Ref<Shark> shark = RefAs<Shark>(animal);
    ASSERT_NE(nullptr, shark);
}

TEST(Ref, RefAsIsNull)
{
    Ref<IAnimal> animal = CreateRef<Shark>();
    Ref<Circle> circle = RefAs<Circle>(animal);
    ASSERT_EQ(nullptr, circle);
}

TEST(Ref, RefCastThrow)
{
    auto call = []
    {
        try
        {
            Ref<IAnimal> animal = CreateRef<Shark>();
            Ref<Circle> circle = RefCast<Circle>(animal);
        }
        catch (const InvalidCastException &e)
        {
            // and this tests that it has the correct message
            EXPECT_STREQ("Failed to cast TSource to TTarget", e.what() );
            throw;
        }
    };

    EXPECT_THROW(call(), InvalidCastException);
}