#include "components/handle.h++"
#include "utilities.h++"
// #include "test/test_bases/test_utilities.hpp"

#include <QDebug>
#include <QTextStream>

using namespace Runge::Components::Handle;
using namespace Runge::Components::Handle::privateDetails;
using namespace Runge::Utilities;

int main ( ) {
  auto syllable = SyllableParser::parse ( "dang3" );
  qDebug ( ) << Stringizer::convert ( syllable );
  qDebug ( ) << Stringizer::convert ( syllable.initial );
  qDebug ( ) << Stringizer::convert ( syllable.final );
  qDebug ( ) << Stringizer::convert ( syllable.tone );

  Handle      h { "阿党相为 e1 dang3 xiang1 wei2" };
  Handle      h2 { "安分知足 an1 fen4 zhi1 zu2" };
  auto        res = HandleComparator::compare ( h, h2 );
  QTextStream out { stdout };
  DefaultColoredHandleFormatter::print ( out, h );
  DefaultColoredHandleFormatter::print ( out, res );
}