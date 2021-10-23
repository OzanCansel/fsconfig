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

auto conf()
{
    return fsconfig::config { "car" };
}

auto temp_conf()
{
    return fsconfig::config { temp_dir_path };
}

TEST_CASE( "Read a field" , "fsconfig::operator[]" )
{   
    auto config = conf();

    REQUIRE( config[ "name" ].value() == "volvo" );
}

TEST_CASE( "Read a nested field" , "fsconfig::operator[]" )
{
    auto config = conf();

    REQUIRE( config[ "engine/type" ].value() == "gasoline" );
}

TEST_CASE( "Read a field when config is const" , "fsconfig::operator[]" )
{
    const auto& config = conf();

    REQUIRE( config[ "engine/type" ] == "gasoline" );
}

TEST_CASE( "Set a field" , "fsconfig::operator[]" )
{
    auto config = temp_conf();

    config[ "color" ] = "green";
    REQUIRE( config[ "color" ].value() == "green" );

    config[ "color" ] = "yellow";
    REQUIRE( config[ "color" ].value() == "yellow" );
}

TEST_CASE( "Set a nested field" , "fsconfig::operator[]" )
{
    auto config = temp_conf();

    config[ "person/identity" ] = "2343333";
    REQUIRE( config[ "person/identity" ].value() == "2343333" );

    config[ "person/identity" ] = "1353843";
    REQUIRE( config[ "person/identity" ].value() == "1353843" );
}