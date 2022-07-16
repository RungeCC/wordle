#include "components/basic_wordle.h++"
#include "game_frameworks/qt_cli_single_game_framework.h++"
#include "single_games/qt_cli_single_wordle_template.h++"

#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <memory>

using namespace ::Runge::Components::BasicWordle;
using namespace ::Runge::GameFrameworks;
using namespace ::Runge::SingleGames;
using namespace ::Runge::Utilities;
using namespace ::Runge::Tools;

int main ( int argc, char* argv [] ) {
  try {
    auto file                   = QFile { R"(/home/runge/Documents/cpp-oop-final-project/assets/word5.txt)" };
    auto resource_holder        = std::make_shared< BasicWordleResourceHolder > ( file );
    auto generator              = std::make_shared< BasicWordleGenerator > ( resource_holder );
    auto parser                 = std::make_shared< BasicWordleParser > ( resource_holder );
    auto io_device              = std::make_shared< QtCLIDevice > ( );
    using BasicWordleSingleGame = QtCLISingleWordleTemplate< QtCLIDevice,
                                                             BasicWordleGenerator,
                                                             BasicWordleComparator,
                                                             BasicWordleFormatter,
                                                             BasicWordleParser >;

    auto single_game            = std::make_unique< BasicWordleSingleGame > (
        io_device,
        generator,
        parser,
        6,
        "basic wordle",
        QString { "这是基本 Wordle 游戏，你有 6 次机会猜测一个 5 字的英文单词\n"
                             "如果位置和字母完全正确你会得到一个 ^ 标记，如果位置错误但单词正确你会得到 ~ 标记，否则你会得到 x "
                             "标记。\n"
                             "祝你好运！" } );

    auto game = QtCLISingleGameFramework< BasicWordleSingleGame > ( std::move ( single_game ) );
    game.start ( );

  } catch ( std::exception& err ) {
    qDebug ( ) << err.what ( );
    return 1;
  }
  return 0;
}
