#ifndef FINAL_PROJ_COLORED_BASIC_WORDLE_HPP_
#define FINAL_PROJ_COLORED_BASIC_WORDLE_HPP_

#include "../basic_wordle_components/basic_wordle_components.hpp"
#include "tools.h++"
#include "utilities.h++"

#include <QMap>
#include <concepts>

namespace Runge::Components::ColoredWordle::privateDetails {
  using namespace ::Runge::Utilities;
  using namespace ::Runge::Tools;
  using namespace ::Runge::Components::BasicWordle;
  using namespace ::Runge::Concepts;
  using namespace ::std;

  template < class Scheme >
  class ColoredWordleFormatter {
  public:
    using wordle          = class BasicWordle;
    using compared_wordle = BasicComparedWordle;
    using color           = Color;
    using io_device       = QtCLIDevice;

  public:
    Runge_Generate_Abstract ( ColoredWordleFormatter )

  public:
    static QTextStream& print ( QTextStream& stream, class BasicWordle const& wordle ) {
      stream << wordle.data ( ) << Qt::flush;
      return stream;
    }
    static QTextStream& print ( QTextStream& stream, BasicComparedWordle const& wordle ) {
      auto    data            = wordle.data ( );
      auto    code            = wordle.code ( );
      QString str             = "";
      auto    single_colorize = [] ( QChar const& ch, Color color ) -> QString {
        return ColorWrapper::wrap ( Scheme::foreground, color ) ( QString ( " %1 " ).arg ( ch ) );
      };
      for ( qsizetype i = 0; i < data.length ( ); ++i ) {
        switch ( code [ i ] ) {
          case ComparedMark::Correct: str += single_colorize ( data [ i ], Scheme::correct ); break;
          case ComparedMark::Wrong: str += single_colorize ( data [ i ], Scheme::wrong ); break;
          case ComparedMark::Misplaced: str += single_colorize ( data [ i ], Scheme::misplaced ); break;
          default: str += "<?>"; break;
        }
      }
      stream << str << Qt::flush;
      return stream;
    }
  };

}; // namespace Runge::Components::ColoredWordle::privateDetails

namespace Runge::Components::ColoredWordle {
  using privateDetails::ColoredWordleFormatter;
  using DefaultColoredWordleFormatter = privateDetails::ColoredWordleFormatter< Marks::DefaultColorScheme >;
}; // namespace Runge::Components::ColoredWordle

#endif
