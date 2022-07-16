#ifndef FINAL_PROJ_TEST_UTILITIES_HPP_
#define FINAL_PROJ_TEST_UTILITIES_HPP_

#include <QChar>
#include <QString>
#include <boost/preprocessor.hpp>
#include <catch2/catch_all.hpp>

#ifdef CATCH_CONFIG_RUNNER
#  define Runge_Catch2_Test_Main_Show_All                                                                              \
    int main ( int argc, char* argv [] ) {                                                                             \
      auto session = Catch::Session ( );                                                                               \
      return session.run ( argc, argv );                                                                               \
    }

//  对 Qt 的类型特化 StringMaker
namespace Catch {
  template <>
  struct StringMaker< QString > {
    static std::string convert ( QString const& value ) {
      return QString ( "\"%1\"" ).arg ( value ).toLocal8Bit ( ).toStdString ( );
    }
  };
  template <>
  struct StringMaker< QChar > {
    static std::string convert ( QChar const& value ) {
      return QString ( "'%1'" ).arg ( value ).toLocal8Bit ( ).toStdString ( );
    }
  };
}  //  namespace Catch
#else

BOOST_PP_ASSERT_MSG ( 0, "you may forgot to define macro CATCH_CONFIG_RUNNER!" );

#endif
#endif
