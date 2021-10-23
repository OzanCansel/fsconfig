#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fsconfig/fsconfig.hpp>

constexpr auto NONEXISTENT_FIELD = "max_speed";

auto conf()
{
    return fsconfig::config { "car" };
}

TEST_CASE( "If field doesn't exist value() should throw field_does_not_exist" , "fsconfig::value()" )
{
    auto config = conf();

    REQUIRE_THROWS_AS( config.value( NONEXISTENT_FIELD ) , fsconfig::field_does_not_exist );
}

TEST_CASE( "If path exist but not a field should throw is_not_a_field" , "fsconfig::value()" )
{
    auto config = conf();

    REQUIRE_THROWS_AS( config.value( "engine" ) , fsconfig::is_not_a_field );
}

TEST_CASE( "If field exist value() should return the value" , "fsconfig::value()" )
{
    auto config = conf();

    REQUIRE( config.value( "name" ) == "volvo" );
}

TEST_CASE( "value() should return nested fields" , "fsconfig::value()" )
{
    auto config = conf();

    REQUIRE( config.value( "engine/hp" ) == "122" );
}

TEST_CASE( "If key doesn't exist but default is specified should return default_value" , "fsconfig::value()" )
{
    auto config = conf();

    REQUIRE( config.value( NONEXISTENT_FIELD , "300" ) == "300" );
}