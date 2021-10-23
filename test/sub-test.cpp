#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fsconfig/fsconfig.hpp>

TEST_CASE( "sub-test" , "fsconfig::sub()" )
{
    fsconfig::config config { "car" };
    auto engine_config = config.sub( "engine" );

    REQUIRE( engine_config.value( "capacity" ) == "3.0L" );
    REQUIRE( engine_config.value( "type" ) == "gasoline" );
}