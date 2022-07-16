cmake_minimum_required ( VERSION 3.13.0 )
project ( qt_guards LANGUAGES CXX )

set ( CMAKE_INCLUDE_CURRENT_DIR ON )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

set ( CMAKE_AUTOUIC ON )
set ( CMAKE_AUTOMOC ON )
set ( CMAKE_AUTORCC ON )

set ( CMAKE_CXX_STANDARD 20 ) # 设置 c++ 版本 20
set ( CMAKE_CXX_FLAGS "-Wall -O3" )

find_package ( Qt6 COMPONENTS Core Widgets REQUIRED )


if ( CMAKE_SYSTEM_NAME MATCHES "Linux" )

  set ( BOOST_INCLUDEDIR /usr/include/boost )
  set ( BOOST_LIBRARYDIR /usr/lib/ )

  find_package ( Boost 1.75.0 REQUIRED )
  find_package ( fmt )

else ()

  set ( BOOST_ROOT "C:/boost/" )
  set ( fmt_DIR "C:/msys64/mingw64/lib/cmake/fmt" )
  set ( Catch2_DIR "C:/msys64/mingw64/lib/cmake/Catch2" )

  find_package ( Boost REQUIRED )
  find_package ( fmt REQUIRED )
  find_package ( Catch2 REQUIRED )

endif ()

include_directories ( ${Boost_INCLUDE_DIRS} )
include_directories ( ${fmt_INCLUDE_DIRS} )
include_directories ( ${Catch2_INCLUDE_DIRS} )

add_library ( qobj_traits INTERFACE
              qobj_concepts/qobj_concepts.hpp )

add_library ( qt_guards INTERFACE
              qt_guards.hpp )
target_link_libraries ( qt_guards INTERFACE qobj_traits )