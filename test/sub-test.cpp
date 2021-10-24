#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fsconfig/fsconfig.hpp>

std::filesystem::path temp_dir_path = []{
    std::filesystem::path tmp_dir_path {
        std::filesystem::temp_directory_path() /= std::tmpnam( nullptr )
    };

    std::filesystem::create_directories( tmp_dir_path );

    return tmp_dir_path;
}();

TEST_CASE( "sub-test" , "fsconfig::sub()" )
{
    fsconfig::config config { "car" };
    auto engine_config = config.sub( "engine" );

    REQUIRE( engine_config.value( "capacity" ) == "3.0L" );
    REQUIRE( engine_config.value( "type" ) == "gasoline" );
}

TEST_CASE( "If group doesn't[1 level nested] exist should create the directories" , "fsconfig::sub()" )
{
    fsconfig::config config { temp_dir_path };

    REQUIRE_NOTHROW( config.sub( "cpu" ) );
}

TEST_CASE( "If group doesn't exist[2 level nested] should create the directories" , "fsconfig::sub()" )
{
    fsconfig::config config { temp_dir_path };

    REQUIRE_NOTHROW( config.sub( "net/enp1s0" ) );
}