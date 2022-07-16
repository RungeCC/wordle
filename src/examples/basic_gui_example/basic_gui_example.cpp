#include "components/basic_wordle.h++"
#include "game_frameworks/qt_gui_single_game_framework.h++"
#include "single_games/qt_gui_single_wordle.h++"

#include <QApplication>
#include <QFile>
#include <QString>
#include <memory>

using namespace ::Runge::Components::BasicWordle;
using namespace ::Runge::GameFrameworks;
using namespace ::Runge::SingleGames;
using namespace ::Runge::Utilities;
using namespace ::Runge::Tools;

int main ( int argc, char* argv [] ) {
  int val = 0;
  try {
    QApplication app ( argc, argv );

    // init single game
    auto         file            = QFile { R"(:/assets/word5.txt)" };
    auto         resource_holder = std::make_shared< BasicWordleResourceHolder > ( file );
    auto         generator       = std::make_shared< BasicWordleGenerator > ( resource_holder );
    auto         parser          = std::make_shared< BasicWordleParser > ( resource_holder );
    auto         single_game     = new BasicQtGUIGame ( generator, parser );
    auto         game            = QtGUIGameFramework ( single_game );
    game.start ( );
    val = QApplication::exec();
  } catch ( std::exception& err ) {
    qDebug ( ) << err.what ( );
    return 1;
  }
  return val;
}
