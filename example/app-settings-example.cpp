#include <iostream>
#include <filesystem>
#include <fsconfig/fsconfig.hpp>
#include <iomanip>

int main()
{
    ::std::filesystem::create_directory( "settings" );

    fsconfig::config config { "settings" };

    config[ "last_logged_date" ]           = "25/10/2021";
    config[ "opened_project" ]             = "/home/ozanc/repo/fsconfig";
    config[ "app/theme" ]                  = "dark";
    config[ "app/sidebar" ]                = "1";
    config[ "app/version" ]                = "v1.2.34+04abc25bf7";
    config[ "app/author" ]                 = "arnes";
    config[ "editor/is_auto_complete_on" ] = "1";
    config[ "editor/last_opened_file" ]    = "include/fsconfig/fsconfig.hpp";
    config[ "editor/font" ]                = "Ubuntu Mono";
    config[ "editor/autosave" ]            = "0";

    auto editor_settings = config.sub( "editor" );
    auto app_settings    = config.sub( "app" );

    std::cout << std::setw( 25 ) << "is_auto_complete_on : " << editor_settings[ "is_auto_complete_on" ].value() << std::endl
              << std::setw( 25 ) << "last_opened_file : "    << editor_settings.value( "last_opened_file" )      << std::endl
              << std::setw( 25 ) << "font : "                << editor_settings.value( "font" )                  << std::endl
              << std::setw( 25 ) << "font_size : "           << editor_settings.value( "font_size" , "12" )      << std::endl
              << std::setw( 25 ) << "version : "             << config[ "app/version" ].value()                  << std::endl
              << std::setw( 25 ) << "author : "              << app_settings.value( "author" )                   << std::endl;
}