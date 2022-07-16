#ifndef FINAL_PROJ_COLORED_CLI_HPP_
#define FINAL_PROJ_COLORED_CLI_HPP_

#include <QString>
#include <QTextStream>
#include <functional>


namespace Runge::ColoredCLI::privateDetails {
  enum class Color {
    Black [[maybe_unused]]         = 30,
    Red [[maybe_unused]]           = 31,
    Green [[maybe_unused]]         = 32,
    Yellow [[maybe_unused]]        = 33,
    Blue [[maybe_unused]]          = 34,
    Magenta [[maybe_unused]]       = 35,
    Cyan [[maybe_unused]]          = 36,
    White [[maybe_unused]]         = 37,
    BrightBlack [[maybe_unused]]   = 90,
    BrightRed [[maybe_unused]]     = 91,
    BrightGreen [[maybe_unused]]   = 92,
    BrightYellow [[maybe_unused]]  = 93,
    BrightBlue [[maybe_unused]]    = 94,
    BrightMagenta [[maybe_unused]] = 95,
    BrightCyan [[maybe_unused]]    = 96,
    BrightWhite [[maybe_unused]]   = 97,
  };

  struct RGBColor {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    RGBColor ( uint8_t red_, uint8_t green_, uint8_t blue_ ) : red ( red_ ), green ( green_ ), blue ( blue_ ) { }
    friend bool operator== ( RGBColor const& lhs, RGBColor const& rhs ) = default;
  };

  class ColoredSetter {
  public:
    static QTextStream& set ( QTextStream& stream, Color foreground, Color background );
    static QTextStream& reset ( QTextStream& stream );
  };


  class ColorWrapper {
  public:
    static std::function< QString ( QString const& ) > wrap ( Color foreground, Color background );
  };
}; // namespace Runge::ColoredCLI::privateDetails

namespace Runge::ColoredCLI {
  using privateDetails::Color;
  using privateDetails::ColoredSetter;
  using privateDetails::ColorWrapper;
  using privateDetails::RGBColor;
}; // namespace Runge::ColoredCLI


#endif
