// Copyright 2023, Jefferson Science Associates, LLC.
// Subject to the terms in the LICENSE file found in the top-level directory.

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <NestedVectorEasy.hpp>



TEST_CASE("NestedVector_BasicExample") {

    NestedVectorEasy v(2);
    REQUIRE(v.depth() == 2);

    // Test reserving and appending

    v.reserve(0, 3); // Reserve space for three items at the outer level
    v.reserve(1, 3); // Reserve space for three items at the next slot in the inner level

    v.append(7.7); 
    v.append(1.9);
    v.append(8);

    v.reserve(1,2); // Reserve space for two items at the next slot in the inner level

    v.append(100.1);
    v.append(0.8);

    v.reserve(1,1); // Reserve space for one item at the next slot in the inner level
    v.append(3.141592);


    // Test that our NestedVector understands its own sizes

    REQUIRE(v.size({}) == 3);

    REQUIRE(v.size({0}) == 3);
    REQUIRE(v.size({1}) == 2);
    REQUIRE(v.size({2}) == 1);

    // Test that we can correctly retrieve data

    REQUIRE(v.get({0,0}) == 7.7);
    REQUIRE(v.get({1,1}) == 0.8);
    REQUIRE(v.get({2,0}) == 3.141592);

}

TEST_CASE("NestedVector_AnotherExample") {

}


