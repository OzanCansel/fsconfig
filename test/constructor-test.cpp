#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fsconfig/fsconfig.hpp>

TEST_CASE( "If root directory doesn't exist should throw root_path_does_not_exist" , "fsconfig::fsconfig" )
{
    REQUIRE_THROWS_AS( fsconfig::config { "unexistent_directory" } , fsconfig::root_path_does_not_exist );
}

TEST_CASE( "If root path is not directory should throw root_is_not_directory" , "fsconfig::fsconfig" )
{
    REQUIRE_THROWS_AS( fsconfig::config { "car/name" } , fsconfig::root_is_not_directory );
}