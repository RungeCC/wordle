cmake_minimum_required ( VERSION 3.13.0 )
project ( colored_cli LANGUAGES CXX )

add_library ( colored_cli STATIC
              colored_cli.cpp
              colored_cli.hpp )
set_target_properties ( colored_cli
                        PROPERTIES OUTPUT_NAME "colored_cli" )
set_target_properties ( colored_cli
                        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" )
target_link_libraries ( colored_cli Qt6::Core )

