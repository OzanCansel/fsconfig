#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fsconfig/fsconfig.hpp>

auto conf()
{
    return fsconfig::config { "car" };
}

TEST_CASE( "If field exists should return true" , "fsconfig::is_set" )
{
    auto config = conf();

    REQUIRE( config.is_set( "name" ) );
}

TEST_CASE( "If field is nested and exists should return true" , "fsconfig::is_set" )
{
    auto config = conf();

    REQUIRE( config.is_set( "engine/capacity" ) );
}

TEST_CASE( "If field doesn't exist should return false" , "fsconfig::is_set" )
{
    auto config = conf();

    REQUIRE( !config.is_set( "unexistent_field" ) );
}