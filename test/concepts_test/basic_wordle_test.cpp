#define CATCH_CONFIG_RUNNER
#include "components/basic_wordle.h++"
#include "concepts.h++"
#include "test/test_bases/test_utilities.hpp"

#include <QDebug>
#include <QString>
#include <QTextStream>
#include <string>

using namespace ::Runge::Concepts;
using namespace ::Runge::Components::BasicWordle;

TEST_CASE ( "BasicWordleComponents" ) {
  INFO ( "check if basic wordle satisfied the traits" );
  CHECK ( is_wordle< BasicWordle > );
  CHECK ( is_compared_wordle< BasicComparedWordle > );
  CHECK ( is_wordle_comparator< BasicWordleComparator > );
  CHECK ( is_wordle_generator< BasicWordleGenerator > );
  CHECK ( is_wordle_parser< BasicWordleParser > );
  CHECK ( is_wordle_formatter< BasicWordleFormatter > );
}

struct failure_wordle1 { // not semi-regular, since not default constructible
  failure_wordle1 ( int ) { }
  failure_wordle1 ( ) = delete;
};

struct failure_wordle2 { // not semi-regular, since not copy constructible
  failure_wordle2 ( )                        = default;
  failure_wordle2 ( failure_wordle2 const& ) = delete;
};

TEST_CASE ( "MustFailedTypes" ) {
  INFO ( "check if concepts requires failed in specific types" );
  CHECK_FALSE ( is_wordle< failure_wordle1 > );
  CHECK_FALSE ( is_wordle< failure_wordle2 > );
}

Runge_Catch2_Test_Main_Show_All
