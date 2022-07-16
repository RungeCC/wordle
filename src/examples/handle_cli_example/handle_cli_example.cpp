#include "components/handle.h++"
#include "game_frameworks/qt_cli_single_game_framework.h++"
#include "single_games/qt_cli_single_wordle_template.h++"

#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <memory>

using namespace ::Runge::Components::Handle;
using namespace ::Runge::GameFrameworks;
using namespace ::Runge::SingleGames;
using namespace ::Runge::Utilities;
using namespace ::Runge::Tools;

int main ( int argc, char* argv [] ) {
  try {
    auto file              = QFile { R"(/home/runge/Documents/cpp-oop-final-project/assets/idioms.txt)" };
    auto resource_holder   = std::make_shared< HandleResourceHolder > ( file );
    auto generator         = std::make_shared< HandleGenerator > ( resource_holder );
    auto parser            = std::make_shared< HandleParser > ( resource_holder );
    auto io_device         = std::make_shared< QtCLIDevice > ( );
    using HandleSingleGame = QtCLISingleWordleTemplate< QtCLIDevice,
                                                        HandleGenerator,
                                                        HandleComparator,
                                                        DefaultColoredHandleFormatter,
                                                        HandleParser >;

    auto single_game       = std::make_unique< HandleSingleGame > (
        io_device,
        generator,
        parser,
        10,
        "handle",
        QString { "这是基于成语的 Handle 游戏，你有 10 次机会猜测一个 4 字的中文成语\n"
                        "完全类似与你所熟知的 Wordle，但是现在对于每个字符的声母、韵母和声调你将获得单独的提示\n"
                        "如果汉字完全正确汉字也将着色为绿色，当心汉语中的零声母和轻声调！\n"
                        "祝你好运！" } );

    auto game = QtCLISingleGameFramework< HandleSingleGame > ( std::move ( single_game ) );
    game.start ( );

  } catch ( std::exception& err ) {
    qDebug ( ) << err.what ( );
    return 1;
  }
  return 0;
}
