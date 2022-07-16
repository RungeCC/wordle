#include "colored_cli.hpp"

#include <QString>

namespace Runge::ColoredCLI::privateDetails {

  QTextStream& ColoredSetter::set ( QTextStream& stream, Color foreground, Color background ) {
    QString str_temp = "\x1b[%1;%2m";
    auto    str = str_temp.arg ( QString::number ( int ( foreground ) ), QString::number ( int ( background ) + 10 ) );
    stream << str << Qt::flush;
    return stream;
  }

  QTextStream& ColoredSetter::reset ( QTextStream& stream ) {
    stream << "\x1b[0m" << Qt::flush;
    return stream;
  }

  std::function< QString ( QString const& ) > ColorWrapper::wrap ( Color foreground, Color background ) {
    auto lmd = [ foreground, background ] ( QString const& str ) {
      return QString ( "\x1b[%1;%2m%3\x1b[0m" )
          .arg ( QString::number ( int ( foreground ) ), QString::number ( int ( background ) + 10 ), str );
    };
    return std::function< QString ( QString const& ) > { lmd };
  }
};  //  name