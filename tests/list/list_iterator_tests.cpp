#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>

#include "list.h"

namespace 
{
    using namespace std::string_literals;

    class EmptyLists : public ::testing::Test {
    protected:
    void SetUp() override {
    }

    saxion::list<std::string> str_list{};
    saxion::list<std::string> non_empty_str_list{"Hello", "World"};
    
    };

    class ListWithTwoElements : public ::testing::Test {
    protected:
    void SetUp() override {
        for (auto&& el: words) {
            str_list.push_back(el);
        }
    }

    saxion::list<std::string> str_list{};
    std::vector<std::string> words{"Hello"s, "Iterators"s};

    };

    class Modifying : public ::testing::Test {
    protected:
        void SetUp() override {
            for (auto&& el: words) {
                str_list.push_back(el);
            }
        }

        saxion::list<std::string> str_list{};
        std::vector<std::string> words{"Hello"s, "Welcome"s, "Iterators"s, "Tests"s};
    };

    class Accessing : public ::testing::Test {
    protected:
        struct Person {
            std::string name;
            int age;
        };

        void SetUp() override {
            for (auto&& el: persons) {
                str_list.push_back(el);
            }
        }

        saxion::list<Person> str_list{};
        std::vector<Person> persons{{"Alice"s, 20}, {"Bob"s, 21}, {"Cindy"s, 22}, {"Derek"s, 23}};
    };

    TEST_F(EmptyLists, Begin)
    {
        EXPECT_EQ(str_list.begin(), str_list.end()) << "Begin and end should be equal";
    }

    TEST_F(EmptyLists, IncrementBegin)
    {
        EXPECT_EQ(++str_list.begin(), str_list.end()) << "Incrementing the begin of an empty list should be equal to end";
    }

    TEST_F(EmptyLists, DecrementEnd)
    {
        EXPECT_EQ(--str_list.end(), str_list.begin()) << "Decrementing the end of an empty list should be equal to begin";
    }

    TEST_F(EmptyLists, ClearedListBegin)
    {
        non_empty_str_list.clear();
        EXPECT_EQ(str_list.begin(), str_list.end()) << "Begin and end should be equal";
    }

    TEST_F(EmptyLists, ClearedListIncrementBegin)
    {
        non_empty_str_list.clear();
        EXPECT_EQ(++str_list.begin(), str_list.end()) << "Incrementing the begin of an empty list should be equal to end";
    }

    TEST_F(EmptyLists, ClearedListDecrementEnd)
    {
        non_empty_str_list.clear();
        EXPECT_EQ(--str_list.end(), str_list.begin()) << "Decrementing the end of an empty list should be equal to begin";
    }

    TEST_F(ListWithTwoElements, Begin)
    {
        EXPECT_EQ(*str_list.begin(), words[0]) << "Begin should be equal to the first element";
    }

    TEST_F(ListWithTwoElements, BeginFront)
    {
        EXPECT_EQ(str_list.front(), *str_list.begin()) << "Front should be equal to the element pointed by begin";
    }

    TEST_F(ListWithTwoElements, BeginFrontPointers)
    {
        EXPECT_EQ(&str_list.front(), &(*str_list.begin())) << "Front and begin should point to the same element";
    }

    TEST_F(ListWithTwoElements, IncrementBegin)
    {
        EXPECT_EQ(*(++str_list.begin()), words[1]) << "Incrementing the begin should be equal to the second element";
    }

    TEST_F(ListWithTwoElements, DecrementEnd)
    {
        EXPECT_EQ(*(--str_list.end()), words[1]) << "Decrementing the end should be equal to the last element";
    }

    TEST_F(ListWithTwoElements, BeginEnd)
    {
        EXPECT_NE(str_list.begin(), str_list.end()) << "Begin and end should not be equal";
    }

    TEST_F(ListWithTwoElements, BeginIncrementEnd)
    {
        EXPECT_EQ(++str_list.begin(), --str_list.end()) << "Incrementing the begin and decrementing the end should be equal";
    }

    TEST_F(ListWithTwoElements, BeginIncrementedTwiceEnd)
    {
        auto iter = str_list.begin();
        ++iter;
        ++iter;
        EXPECT_EQ(iter, str_list.end()) << "Incrementing the begin twice should be equal to end";
    }


    TEST_F(Modifying, Insert)
    {
        auto iter = str_list.begin();
        ++iter;
        auto added = str_list.insert(iter, "Inserted");

        EXPECT_EQ(str_list.size(), 5) << "Size should be 5";
        EXPECT_EQ(*added, "Inserted") << "Added iterator should point to Inserted";
        EXPECT_EQ(*iter, "Welcome") << "The insertion node should point to Welcome";
        EXPECT_EQ(--iter, added) << "The added iterator should come just after the insertion point";
        
        ++added;
        ++added;
        ++added;
        ++added;
        EXPECT_EQ(added, str_list.end()) << "The added iterator should come just before the last element";
    }

    TEST_F(Modifying, Erase)
    {
        auto iter = str_list.begin();
        ++iter;
        auto erased = str_list.erase(iter);

        EXPECT_EQ(str_list.size(), 3) << "Size should be 3";
        EXPECT_EQ(*erased, "Iterators") << "Erased iterator should point to Iterators";
                
        ++erased;
        ++erased;
        EXPECT_EQ(erased, str_list.end()) << "The erased iterator should come just before the last element";
    }

    TEST_F(Accessing, Dereference)
    {
        auto iter = str_list.begin();
        EXPECT_EQ((*iter).name, "Alice") << "Dereferencing begin should return the first element";

        ++iter;

        EXPECT_EQ((*iter).name, "Bob") << "Dereferencing incremented begin should return the second element";

        (*iter).name = "Bobby";
        (*iter).age = 42;

        auto bobby = str_list.begin();
        ++bobby;

        EXPECT_THAT(*bobby, ::testing::FieldsAre("Bobby"s, 42)) << "Dereferencing iterator should allow for modification";
    
        EXPECT_THAT(str_list[1], ::testing::FieldsAre("Bobby"s, 42)) << "Dereferencing iterator should allow for modification";

    
    }

    TEST_F(Accessing, MemberAccess)
    {
        auto iter = str_list.begin();
        EXPECT_EQ(iter->name, "Alice") << "Dereferencing begin should return the first element";

        ++iter;

        EXPECT_EQ(iter->name, "Bob") << "Dereferencing incremented begin should return the second element";

        iter->name = "Bobby";
        iter->age = 42;

        auto bobby = str_list.begin();
        ++bobby;

        EXPECT_THAT(*bobby, ::testing::FieldsAre("Bobby"s, 42)) << "Accessing iterator should allow for modification";
        EXPECT_THAT(str_list[1], ::testing::FieldsAre("Bobby"s, 42)) << "Accessing iterator should allow for modification";

    }

}