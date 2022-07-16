# project
cmake_minimum_required ( VERSION 3.13.0 )
project ( final_proj LANGUAGES CXX )

set ( CMAKE_INCLUDE_CURRENT_DIR ON )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

set ( CMAKE_AUTOUIC ON )
set ( CMAKE_AUTOMOC ON )
set ( CMAKE_AUTORCC ON )

set ( CMAKE_CXX_STANDARD 23 ) # 设置 c++ 版本 23
add_compile_options ( -O2 $<$<CXX_COMPILER_ID:CLANG>:-stdlib=libstdc++> )
set ( CMAKE_EXE_LINKER_FLAGS "-lstdc++" )

if ( Runge_Debug )
  add_compile_options ( -DRunge_Debug )
endif ()
find_package ( Qt6 COMPONENTS Core Widgets REQUIRED )


# 按照系统寻找必须的库：Boost，Catch2, fmt
if ( CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Darwin" )

  find_package ( Boost REQUIRED )
  find_package ( fmt REQUIRED )
  find_package ( Catch2 3 REQUIRED )

else ()

  message ( FATAL_ERROR "do not support other os." )

endif ()

include_directories ( ${Boost_INCLUDE_DIRS} )
include_directories ( ${fmt_INCLUDE_DIRS} )
include_directories ( ${Catch2_INCLUDE_DIRS} )
include_directories ( src/includes )

# matchit 库，按照源码包含
add_subdirectory ( packages/matchit/ )
include_directories ( ${matchit_SOURCE_DIR} )

# -----------------

add_library ( concepts INTERFACE
              src/concepts/concepts.hpp
              )

# -----------------

add_library ( interfaces INTERFACE
              src/interfaces/wordle_interfaces.hpp
              src/interfaces/qt_gui_interfaces.hpp )
target_link_libraries ( interfaces INTERFACE Qt6::Core Qt6::Widgets )

# -----------------

add_library ( macros INTERFACE
              src/utilities/macros.hpp
              src/utilities/macros/macro_auto_generate.hpp
              src/utilities/macros/macro_switch.hpp
              src/utilities/macros/macro_utilities.hpp
              src/utilities/macros/macro_auto_generate_predefined.hpp )

# -----------------

add_subdirectory ( src/utilities/colored_cli )

# -----------------

add_library ( utilities INTERFACE
              src/utilities/utilities.hpp
              src/utilities/stringizer.hpp
              src/utilities/io_device.hpp
              src/utilities/result_type.hpp
              src/utilities/debug_utilities.hpp )
target_link_libraries ( utilities INTERFACE matchit macros colored_cli )

# ----------------

add_library ( tools INTERFACE
              src/tools/tools.hpp
              src/tools/marks.hpp
              src/tools/commands.hpp
              src/tools/comparators.hpp
              src/tools/generators.hpp )
target_link_libraries ( tools INTERFACE matchit macros utilities )

# -----------------

add_library ( exceptions INTERFACE
              src/exceptions/bad_resource_exceptions.hpp
              src/exceptions/base_exceptions.hpp
              src/exceptions/no_such_method_exceptions.hpp
              src/exceptions/exceptions.hpp )
target_link_libraries ( exceptions INTERFACE utilities )

# -----------------

add_library ( qt_cli_single_game_framework INTERFACE
              src/game_frameworks/qt_cli_single_game_framework/qt_cli_game_framework.hpp )
target_link_libraries ( qt_cli_single_game_framework INTERFACE matchit )

# -----------------

add_library ( qt_cli_single_game_template INTERFACE
              src/single_games/qt_cli_single_wordle/qt_cli_single_wordle_template.hpp )

# static lib

# -----------------

add_library ( basic_wordle_components STATIC
              src/components/basic_wordle_components/basic_wordle_components.cpp
              src/components/basic_wordle_components/basic_wordle_components.hpp )
set_target_properties ( basic_wordle_components
                        PROPERTIES OUTPUT_NAME "basic_wordle_components" )
set_target_properties ( basic_wordle_components
                        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" )
target_link_libraries ( basic_wordle_components Qt6::Core concepts utilities )

# -----------------

add_library ( colored_wordle_components STATIC
              src/components/colored_basic_wordle_components/colored_basic_wordle.hpp
              src/components/colored_basic_wordle_components/colored_basic_wordle.cpp )
set_target_properties ( colored_wordle_components
                        PROPERTIES OUTPUT_NAME "colored_wordle_components" )
set_target_properties ( colored_wordle_components
                        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" )
target_link_libraries ( colored_wordle_components Qt6::Core colored_cli utilities concepts )

# -----------------

add_library ( handle_components STATIC
              src/components/handle_components/handle_components.cpp
              src/components/handle_components/handle_components.hpp )
set_target_properties ( handle_components
                        PROPERTIES OUTPUT_NAME "handle_components" )
set_target_properties ( handle_components
                        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" )
target_link_libraries ( handle_components Qt6::Core colored_cli utilities concepts )

# -----------------


add_library ( qt_gui_game_framework STATIC
              src/game_frameworks/qt_gui_single_game_framework/qt_gui_game_framework.cpp
              src/game_frameworks/qt_gui_single_game_framework/qt_gui_game_framework.hpp )
set_target_properties ( qt_gui_game_framework
                        PROPERTIES OUTPUT_NAME "qt_gui_game_framework" )
set_target_properties ( qt_gui_game_framework
                        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" )
target_link_libraries ( qt_gui_game_framework Qt6::Core Qt6::Widgets
                        concepts interfaces basic_wordle_components utilities )

# -----------------

add_library ( qt_gui_single_basic_wordle STATIC
              src/single_games/qt_gui_single_wordle/qt_gui_single_basic_wordle/qt_basic_gui_game.hpp
              src/single_games/qt_gui_single_wordle/qt_gui_single_basic_wordle/qt_basic_gui_game.cpp )
set_target_properties ( qt_gui_single_basic_wordle
                        PROPERTIES OUTPUT_NAME "qt_gui_single_basic_wordle" )
set_target_properties ( qt_gui_single_basic_wordle
                        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" )
target_link_libraries ( qt_gui_single_basic_wordle
                        Qt6::Core Qt6::Widgets
                        concepts interfaces basic_wordle_components utilities )

# --------------

add_subdirectory ( src/guards )

# --------------

add_library ( basic_wordle_gui_components STATIC
              src/components/basic_wordle_gui_components/basic_wordle_qt_button.cpp
              src/components/basic_wordle_gui_components/basic_wordle_qt_button.cpp
              src/components/basic_wordle_gui_components/basic_wordle_qt_button_group.cpp
              src/components/basic_wordle_gui_components/basic_wordle_qt_button_group.hpp
              src/components/basic_wordle_gui_components/basic_wordle_qt_button_grid.cpp
              src/components/basic_wordle_gui_components/basic_wordle_qt_button_grid.hpp )
set_target_properties ( basic_wordle_gui_components
                        PROPERTIES OUTPUT_NAME "basic_wordle_gui_components" )
set_target_properties ( basic_wordle_gui_components
                        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "lib" )
target_link_libraries ( basic_wordle_gui_components
                        Qt6::Core Qt6::Widgets concepts
                        interfaces basic_wordle_components utilities )

# test -----------------

add_library ( test_bases INTERFACE
              test/test_bases/test_utilities.hpp )
# ----------------------

add_executable ( concepts_basic_wordle_test
                 test/concepts_test/basic_wordle_test.cpp )
set_target_properties ( concepts_basic_wordle_test
                        PROPERTIES OUTPUT_NAME "concepts_basic_wordle_test" )
set_target_properties ( concepts_basic_wordle_test
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test" )
target_link_libraries ( concepts_basic_wordle_test Qt6::Core basic_wordle_components concepts Catch2::Catch2 )

# --------------

add_executable ( handle_components_test
                 test/components_test/cli_components/test_handle.cpp )
set_target_properties ( handle_components_test
                        PROPERTIES OUTPUT_NAME "handle_components_test" )
set_target_properties ( handle_components_test
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test" )
target_link_libraries ( handle_components_test Qt6::Core handle_components utilities tools Catch2::Catch2 )

# --------------

add_executable ( utilities_marks_test
                 test/utilities_test/utilities_marks_test.cpp
                 )
set_target_properties ( utilities_marks_test
                        PROPERTIES OUTPUT_NAME "utilities_marks_test" )
set_target_properties ( utilities_marks_test
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test" )
target_link_libraries ( utilities_marks_test utilities matchit Qt6::Core Catch2::Catch2 )

# --------------

add_executable ( utilities_commands_test
                 test/utilities_test/utilities_commands_test.cpp
                 )
set_target_properties ( utilities_commands_test
                        PROPERTIES OUTPUT_NAME "utilities_commands_test" )
set_target_properties ( utilities_commands_test
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test" )
target_link_libraries ( utilities_commands_test utilities matchit Catch2::Catch2 Qt6::Core )

# --------------

add_executable ( utilities_macros_test
                 test/utilities_test/utilities_macros_test.cpp
                 )
set_target_properties ( utilities_macros_test
                        PROPERTIES OUTPUT_NAME "utilities_macros_test" )
set_target_properties ( utilities_commands_test
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test" )
target_link_libraries ( utilities_macros_test utilities Catch2::Catch2 Qt6::Core )


# --------------

add_executable ( utilities_colored_cli_test
                 test/utilities_test/utilities_colored_cli_test.cpp
                 )
set_target_properties ( utilities_colored_cli_test
                        PROPERTIES OUTPUT_NAME "utilities_colored_cli_test" )
set_target_properties ( utilities_colored_cli_test
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "test" )
target_link_libraries ( utilities_colored_cli_test utilities Catch2::Catch2 Qt6::Core colored_cli )


# examples  -----------------

add_executable ( basic_gui_example
                 src/examples/basic_gui_example/basic_gui_example.cpp )
set_target_properties ( basic_gui_example
                        PROPERTIES OUTPUT_NAME "basic_gui_example" )
set_target_properties ( basic_gui_example
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin" )
target_link_libraries ( basic_gui_example Qt6::Core Qt6::Widgets basic_wordle_components
                        concepts utilities interfaces qt_gui_game_framework qt_gui_single_basic_wordle
                        basic_wordle_gui_components )
qt_add_resources ( basic_gui_example "words1"
                   PREFIX "/"
                   FILES
                   assets/word5.txt
                   assets/word5p.txt
                   )

# ----------------

add_executable ( basic_cli_example
                 src/examples/basic_cli_example/basic_cli_example.cpp )
set_target_properties ( basic_cli_example
                        PROPERTIES OUTPUT_NAME "basic_cli_example" )
set_target_properties ( basic_cli_example
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin" )
target_link_libraries ( basic_cli_example Qt6::Core basic_wordle_components concepts utilities
                        interfaces matchit qt_cli_single_game_framework qt_cli_single_game_template
                        colored_cli colored_wordle_components )
qt_add_resources ( basic_cli_example "words2"
                   PREFIX "/"
                   FILES
                   assets/word5.txt
                   assets/word5p.txt
                   )


# ----------------

add_executable ( colored_cli_example
                 src/examples/colored_cli_example/colored_cli_example.cpp )
set_target_properties ( colored_cli_example
                        PROPERTIES OUTPUT_NAME "colored_cli_example" )
set_target_properties ( colored_cli_example
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin" )
target_link_libraries ( colored_cli_example
                        Qt6::Core basic_wordle_components concepts utilities
                        interfaces matchit qt_cli_single_game_framework
                        qt_cli_single_game_template colored_cli colored_wordle_components )
qt_add_resources ( colored_cli_example "words3"
                   PREFIX "/"
                   FILES
                   assets/word5.txt
                   assets/word5p.txt
                   )


# ----------------

add_executable ( handle_cli_example
                 src/examples/handle_cli_example/handle_cli_example.cpp )
set_target_properties ( handle_cli_example
                        PROPERTIES OUTPUT_NAME "handle_cli_example" )
set_target_properties ( handle_cli_example
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin" )
target_link_libraries ( handle_cli_example
                        Qt6::Core basic_wordle_components concepts utilities
                        interfaces matchit qt_cli_single_game_framework
                        qt_cli_single_game_template colored_cli colored_wordle_components )
qt_add_resources ( handle_cli_example "words4"
                   PREFIX "/"
                   FILES
                   assets/idiomsp.txt
                   assets/idioms.txt
                   )

