#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <filesystem>
#include <fsconfig/fsconfig.hpp>

std::filesystem::path temp_dir_path = []{
    std::filesystem::path tmp_dir_path { 
        std::filesystem::temp_directory_path() /= std::tmpnam( nullptr )
    };

    std::filesystem::create_directories( tmp_dir_path );

    return tmp_dir_path;
}();

TEST_CASE( "set" , "fsconfig::set()" )
{
    fsconfig::config config { temp_dir_path };

    config.set( "grade" , "AA" );
    REQUIRE( config.value( "grade" ) == "AA" );

    config.set( "grade" , "BB" );
    REQUIRE( config.value( "grade" ) == "BB" );
}