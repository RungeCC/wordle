#define CATCH_CONFIG_RUNNER
#include "src/utilities/colored_cli/colored_cli.hpp"
#include "test/test_bases/test_utilities.hpp"

#include <QDebug>
#include <QString>
#include <QTextStream>

TEST_CASE ( "test_colored_cli" ) {
  using namespace Runge::ColoredCLI;
  SECTION ( "test color wrapper" ) {
    auto wrapper = ColorWrapper::wrap;
    CHECK ( wrapper ( Color::Red, Color::Blue ) ( "I love you." ) == QString ( "\x1b[31;44mI love you.\x1b[0m" ) );
  };

  SECTION ( "test color setter" ) {
    auto        set   = ColoredSetter::set;
    auto        reset = ColoredSetter::reset;
    QString     init  = "";
    QTextStream stream ( &init, QIODeviceBase::ReadWrite );
    set ( stream, Color::Red, Color::Blue );
    QString result;
    stream >> result;
    CHECK ( result == "\x1b[31;44m" );
    reset ( stream );
    stream >> result;
    CHECK ( result == "\x1b[0m" );
  };
};

Runge_Catch2_Test_Main_Show_All