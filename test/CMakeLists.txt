add_executable( value-test value-test.cpp )
add_executable( constructor-test constructor-test.cpp )
add_executable( is_set-test is_set-test.cpp )
add_executable( set-test set-test.cpp )
add_executable( subscript-operator-test subscript-operator-test.cpp )
add_executable( sub-test sub-test.cpp )

target_link_libraries( value-test PRIVATE fsconfig )
target_link_libraries( constructor-test PRIVATE fsconfig )
target_link_libraries( is_set-test PRIVATE fsconfig )
target_link_libraries( set-test PRIVATE fsconfig )
target_link_libraries( subscript-operator-test PRIVATE fsconfig )
target_link_libraries( sub-test PRIVATE fsconfig )

add_test( NAME value-test COMMAND value-test -s )
add_test( NAME constructor-test COMMAND constructor-test -s )
add_test( NAME is_set-test COMMAND is_set-test -s )
add_test( NAME set-test COMMAND set-test -s )
add_test( NAME subscript-operator-test COMMAND subscript-operator-test -s )
add_test( NAME sub-test COMMAND sub-test -s )

file( COPY car DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )