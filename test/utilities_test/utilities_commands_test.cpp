#define CATCH_CONFIG_RUNNER
#include "src/tools/commands.hpp"
#include "test/test_bases/test_utilities.hpp"

#include <QDebug>
#include <matchit.h>
#include <optional>
#include <string_view>

using namespace std;
using namespace std::literals;
using namespace matchit;
using namespace Runge::Commands;

auto test_match ( NullableCommand const& value ) {
  return match ( value ) ( pattern | some ( NewGame )    = expr ( "new" ),
                           pattern | some ( PauseGame )  = expr ( "pause" ),
                           pattern | some ( ResumeGame ) = expr ( "resume" ),
                           pattern | some ( GetHelp )    = expr ( "help" ),
                           pattern | some ( GetName )    = expr ( "name" ),
                           pattern | some ( QuitGame )   = expr ( "quit" ),
                           pattern | some ( _ )          = expr ( "unknown" ),
                           pattern | none                = expr ( "no command" ) );
}

TEST_CASE ( "test match" ) {
  SECTION ( "test basic match" ) {
    CHECK ( test_match ( NewGame ) == "new"sv );
    CHECK ( test_match ( PauseGame ) == "pause"sv );
    CHECK ( test_match ( ResumeGame ) == "resume"sv );
    CHECK ( test_match ( GetHelp ) == "help"sv );
    CHECK ( test_match ( GetName ) == "name"sv );
    CHECK ( test_match ( QuitGame ) == "quit"sv );
    CHECK ( test_match ( Command ( QString ( "fuck" ) ) ) == "unknown"sv );
    CHECK ( test_match ( NoCommand ) == "no command"sv );
  }

  SECTION ( "test maker" ) {
    QString val = ".help   \n";
    CHECK ( CommandParser::parse ( val ) == NullableCommand ( GetHelp ) );
    val = "nothing";
    CHECK ( CommandParser::parse ( val ) == NoCommand );
  }

  SECTION ( "test helper" ) { CHECK ( ( CommandHelper::get_help ( NewGame ), true ) ); }
}

Runge_Catch2_Test_Main_Show_All
