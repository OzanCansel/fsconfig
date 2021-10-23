#pragma once

#include <string>
#include <string_view>
#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <optional>

namespace fsconfig
{
    struct root_path_does_not_exist : ::std::invalid_argument
    {
        root_path_does_not_exist( const ::std::string& path )
            :   ::std::invalid_argument
                {
                    path + ::std::string { " does not exist." } 
                }
        {   }
    };

    struct root_is_not_directory : ::std::invalid_argument
    {
        root_is_not_directory( const ::std::string& path )
            :   ::std::invalid_argument
                {
                    path + ::std::string { " is not a directory." }
                }
        {   }
    };

    struct field_does_not_exist : ::std::runtime_error
    {
        field_does_not_exist( const ::std::string& field )
            :   ::std::runtime_error
                {
                    field + ::std::string { " key does not exist." }
                }
        {   }
    };

    struct is_not_a_field : ::std::runtime_error
    {
        is_not_a_field( const ::std::string& field )
            :   ::std::runtime_error
                {
                    field + ::std::string { " is not a field." }
                }
        {   }
    };

    struct could_not_read_content : ::std::runtime_error
    {
        could_not_read_content( const ::std::string& field )
            :   ::std::runtime_error 
                {
                    field + ::std::string { " could not be read." }
                }
        {   }
    };

    struct key_cannot_opened_or_created : ::std::runtime_error
    {
        key_cannot_opened_or_created( const ::std::string& field )
            :   ::std::runtime_error
                {
                    field + ::std::string { " cannot be opened or created." }
                }
        {   }
    };

    class config
    {
        public:

            class field_reference
            {
                public:

                    field_reference( config& c , ::std::string_view field )
                        :   m_config { c }
                        ,   m_field { field }
                    {   }

                    void operator=( ::std::string_view value )
                    {
                        m_config.set( m_field , value );
                    }

                    ::std::string value()
                    {
                        return m_config.value( m_field );
                    }

                    operator ::std::string()
                    {
                        return value();
                    }

                private:

                    config& m_config;
                    ::std::string m_field;
            };

            inline config( ::std::filesystem::path root );
            inline ::std::string value(
                std::string_view field ,
                ::std::optional<::std::string_view> = ::std::nullopt
            );
            inline void set(
                ::std::string_view field ,
                ::std::string_view value = ::std::string_view {}
            );
            inline bool is_set( ::std::string_view field );
            inline config sub( ::std::string_view );

            inline field_reference operator[]( ::std::string_view field );

        private:

            ::std::filesystem::path m_root;
    };

    config::config( ::std::filesystem::path root )
    {
        if ( !::std::filesystem::exists( root ) )
            throw root_path_does_not_exist { root };

        if ( !::std::filesystem::is_directory( root ) )
            throw root_is_not_directory { root };

        m_root = std::move( root );
    }

    ::std::string config::value( ::std::string_view field , ::std::optional<::std::string_view> default_value )
    {
        auto key_path = ::std::filesystem::path( m_root ) / field;

        if ( !::std::filesystem::exists( key_path ) )
        {
            if ( default_value.has_value() )
                return std::string { *default_value };

            throw field_does_not_exist { ::std::string { field } };
        }

        if ( ::std::filesystem::is_directory( key_path ) )
        {
            if ( default_value.has_value() )
                return std::string { *default_value };

            throw is_not_a_field { ::std::string { field } };
        }

        ::std::ifstream ifs {
            key_path.generic_string() ,
            ::std::ios::in | ::std::ios::ate
        };

        auto size = ifs.tellg();

        ::std::string content ( size , '\0' );
        ifs.seekg( 0 );

        ifs.read( &( content[ 0 ] ) , size );

        if ( ifs.bad() || ifs.fail() )
        {
            if ( default_value.has_value() )
                return std::string { *default_value };

            throw could_not_read_content { std::string { field } };
        }
        
        return content;
    }

    void config::set( ::std::string_view field , ::std::string_view value )
    {
        auto field_path = ::std::filesystem::absolute(
            ::std::filesystem::path { m_root }.append( field )
        );

        ::std::filesystem::create_directories(
            field_path.parent_path()
        );

        ::std::ofstream ofs { field_path.generic_string() };

        if ( ofs.fail() || ofs.bad() )
            throw key_cannot_opened_or_created { ::std::string { field } };

        if ( value.empty() )
            return;
        
        ofs.write( std::begin( value ) , value.size() );
    }

    bool config::is_set( ::std::string_view field )
    {
        return ::std::filesystem::exists(
            ::std::filesystem::path { m_root }.append( field )
        );
    }

    config config::sub( ::std::string_view relative )
    {
        return config { ::std::filesystem::path{ m_root }.append( relative ) };
    }

    config::field_reference config::operator[]( ::std::string_view field )
    {
        return config::field_reference { *this ,  std::move( field ) };
    }
}