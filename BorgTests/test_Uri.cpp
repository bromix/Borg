#include "Borg/Uri.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(Uri, DefaultConstructor)
{
    auto url = Uri("http://localhost:4000/graphql");
    ASSERT_EQ(L"http", url.Scheme());
    ASSERT_EQ("localhost", url.Host());
    ASSERT_EQ(4000, url.Port());
    ASSERT_EQ("/graphql", url.Path());
    ASSERT_TRUE(url.Query().IsNull());
}

TEST(Uri, IsScheme)
{
    auto url = Uri("http://localhost:4000/graphql");
    ASSERT_TRUE(url.IsScheme("http"));
    ASSERT_TRUE(url.IsScheme("HTTP"));
    ASSERT_FALSE(url.IsScheme("file"));
}

TEST(Uri, FileUriToString)
{
    auto url = Uri("file://C:\\Program Files (x86)\\Company\\Product\\skins\\index.html");
    auto result = url.ToString();
    ASSERT_TRUE(result);
}

TEST(Uri, query)
{
    auto url = Uri("https://some.host.com/andApath/?agent=john&arch=x86&darkmode=1&lang=de-DE");
    ASSERT_EQ("?agent=john&arch=x86&darkmode=1&lang=de-DE", url.Query());
}

TEST(Uri, OriginalString)
{
    Uri url("HTTP://www.ConToso.com:80//thick%20and%20thin.htm");

    ASSERT_EQ("HTTP://www.ConToso.com:80//thick%20and%20thin.htm", url.OriginalString());
}

TEST(Uri, ToString)
{
    Uri url("HTTP://www.ConToso.com:80//thick%20and%20thin.htm");

    //ASSERT_EQ("http://www.contoso.com//thick and thin.htm", url.ToString());
    ASSERT_EQ("http://www.contoso.com:80//thick%20and%20thin.htm", url.ToString());
}
