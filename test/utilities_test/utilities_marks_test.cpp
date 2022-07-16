#define CATCH_CONFIG_RUNNER
#include "src/tools/marks.hpp"
#include "test/test_bases/test_utilities.hpp"

#include <QDebug>
#include <cassert>
#include <matchit.h>
#include <string_view>

using namespace ::matchit;
using namespace ::Runge::Marks;
using namespace ::std;
using namespace ::std::literals;

auto test_match ( GameStateMark const& value ) {
  auto val = GameStateMark::type ( value );
  return match ( val ) (
      pattern | as< GameOverType > ( state< GameOverState::Win > )  = expr ( "win" ),
      pattern | as< GameOverType > ( state< GameOverState::Lose > ) = expr ( "lose" ),
      pattern | as< RunningType > ( _ )                             = expr ( "running" ),
      pattern | as< PausedType > ( _ )                              = expr ( "paused" ),
      pattern | _                                                   = [] ( ) {
        assert ( false );
        return ""sv;
      } );
}
TEST_CASE ( "test_game_over_basic_match" ) {
  CHECK ( test_match ( Win ) == "win"sv );
  CHECK ( test_match ( Lose ) == "lose"sv );
  CHECK ( test_match ( Paused ) == "paused"sv );
  CHECK ( test_match ( Running ) == "running"sv );
};

Runge_Catch2_Test_Main_Show_All
