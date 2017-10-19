#include "catch.hpp"

#include "linkedlist.h"

LinkedList<int> initList(size_t count = 10) {
    LinkedList<int> numbers;
    for(size_t i = 0; i < count; i++) numbers.push_front(i);
    return numbers;
}

TEST_CASE("Testing first", "[first]") {
    SECTION("First on empty list should throw exception") {
        LinkedList<int> emptyList;
        REQUIRE_THROWS(emptyList.first());
    }
}

TEST_CASE("Testing count", "[count]") {
    SECTION("Empty list should have 0 elements") {
        LinkedList<int> emptyList;
        REQUIRE(emptyList.count() == 0);
    }
    SECTION("Non empty list should have more than 0 elements") {
        for(size_t count = 1; count <= 5; count++) {
            auto list = initList(count);
            REQUIRE(list.count() == count);
        }
    }
}

TEST_CASE("Testing push_front", "[push_front]") {
    LinkedList<int> list;
    SECTION("Adding one element to list") {
        list.push_front(0);
        REQUIRE(list.count() == 1);
        REQUIRE(list.first() == 0);
    }
    SECTION("All elements should have correct order") {
        list.push_front(0);
        list.push_front(1);
        REQUIRE(list.count() == 2);
        REQUIRE(list.first() == 1);
    }
}

TEST_CASE("Testing push_back", "[push_back]") {
    LinkedList<int> list;
    SECTION("Adding one element to list") {
        list.push_back(0);
        REQUIRE(list.count() == 1);
        REQUIRE(list.first() == 0);
    }
    SECTION("All elements should have correct order") {
        list.push_back(0);
        list.push_back(1);
        REQUIRE(list.count() == 2);
        REQUIRE(list.first() == 0);
    }
}
