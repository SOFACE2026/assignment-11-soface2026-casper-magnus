#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "dict.hpp"
#include <string>

using Catch::Matchers::UnorderedEquals;

TEST_CASE("Test Dict")
{
    // Implement your own tests. You can use below as a reference.
    // When implementing tests, think of the edge cases where you
    // suspect the program is likely to fail.
    // For example inserting the 'same' person twice or removing an
    // non existent person from the dictionary.
    Dict<std::string, int> name_to_age;

    REQUIRE(name_to_age.len() == 0);

    name_to_age.set("Jane", 20);
    REQUIRE(name_to_age.len() == 1);
    REQUIRE(name_to_age.has("Jane"));
    REQUIRE(name_to_age.get("Jane").has_value());
    REQUIRE(name_to_age.get("Jane").value() == 20);
    REQUIRE_THAT(name_to_age.keys(), UnorderedEquals(std::vector<std::string>{"Jane"}));
    REQUIRE_THAT(name_to_age.values(), UnorderedEquals(std::vector<int>{20}));

    name_to_age.set("Tarzan", 25);
    REQUIRE(name_to_age.len() == 2);
    REQUIRE(name_to_age.has("Tarzan"));
    REQUIRE(name_to_age.get("Tarzan").has_value());
    REQUIRE(name_to_age.get("Tarzan").value() == 25);
    REQUIRE_THAT(name_to_age.keys(), UnorderedEquals(std::vector<std::string>{"Jane", "Tarzan"}));
    REQUIRE_THAT(name_to_age.values(), UnorderedEquals(std::vector<int>{20, 25}));

    // Test overwrite existing key
    name_to_age.set("Jane", 21);
    REQUIRE(name_to_age.len() == 2);
    REQUIRE(name_to_age.get("Jane").value() == 21);

    // Test get non-existent key
    REQUIRE_FALSE(name_to_age.get("Batman").has_value());

    // Test has non-existent key
    REQUIRE_FALSE(name_to_age.has("Batman"));

    // Test delete existing key
    name_to_age.del("Jane");
    REQUIRE(name_to_age.len() == 1);
    REQUIRE_FALSE(name_to_age.has("Jane"));

    // Test delete non-existent key
    name_to_age.del("Batman");
    REQUIRE(name_to_age.len() == 1);
}