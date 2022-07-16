#include "basic_wordle_components.hpp"

#include "src/tools/comparators.hpp"
#include "tools.h++"
#include "utilities.h++"

#include <QDebug>
#include <QIODevice>
#include <algorithm>


namespace Runge::Components::BasicWordle {
  using namespace ::std;
  using namespace ::Runge::Tools;
  using namespace ::Runge::Utilities;

  BasicComparedWordle::BasicComparedWordle ( QString const& data, QVector< ComparedMark >& code ) {
    data_ = data;
    code_ = code;
  }

  BasicComparedWordle::operator bool ( ) const noexcept { return this->is_correct ( ); }
  bool                 BasicComparedWordle::is_correct ( ) const noexcept {
                    return all_of ( begin ( code_ ), end ( code_ ), [] ( ComparedMark const& mark ) {
      return mark == ComparedMark::Correct;
    } );
  }

  BasicComparedWordle BasicWordleComparator::compare ( BasicWordle const& answer, BasicWordle const& guess ) {
    auto data = guess.data ( );
    auto code = BasicStringComparator::compare< QString > ( answer.data ( ), guess.data ( ) );
    return BasicComparedWordle { data, code };
  }

  BasicWordleResourceHolder::BasicWordleResourceHolder ( QFile& file ) {
    file.open ( QIODevice::ReadOnly | QIODevice::Text );
    QTextStream stream { &file };
    if ( stream.atEnd ( ) || stream.status ( ) != QTextStream::Ok ) {
      Runge_debug_Message ( "Resource Loading", "Can not find file " + file.fileName ( ) );
      exit ( 1 );
      // error!
    }
    while ( ! stream.atEnd ( ) ) this->wordles_.push_back ( BasicWordle { stream.readLine ( ).remove ( '\n' ) } );
    Runge_debug_Message ( "Resource Loading",
                          QString ( "Loading finished, find %1 wordles." ).arg ( this->wordles_.size ( ) ) );
    file.close ( );
  }

  QTextStream& BasicWordleFormatter::print ( QTextStream& stream, BasicWordle const& wordle ) {
    stream << wordle.data ( );
    stream << Qt::flush;
    return stream;
  }

  QTextStream& BasicWordleFormatter::print ( QTextStream& stream, BasicComparedWordle const& wordle ) {
    stream << wordle.data ( ) << Qt::endl;
    for ( auto const c : wordle.code ( ) ) {
      switch ( c ) {
        case ComparedMark::Correct: stream << '^'; break;
        case ComparedMark::Wrong: stream << 'x'; break;
        case ComparedMark::Misplaced: stream << '~'; break;
        default: break;
      }
    }
    stream << Qt::flush;
    return stream;
  }

  BasicWordleParser::BasicWordleParser ( shared_ptr< BasicWordleResourceHolder > ptr ) : res_ptr_ { ptr } { }

  Result< BasicWordle, BasicWordleParserError > BasicWordleParser::parse ( QString const& str ) {
    if ( str.size ( ) != 5 ) return BasicWordleParserError::InvalidWordle;
    auto wordle = BasicWordle { str.trimmed ( ) };
    if ( any_of ( begin ( res_ptr_->data ( ) ), end ( res_ptr_->data ( ) ), [ &wordle ] ( BasicWordle const& wordle0 ) {
           return bool ( BasicWordleComparator::compare ( wordle, wordle0 ) );
         } ) )
      return wordle;
    return BasicWordleParserError::InvalidWordle;
  }

}; // namespace Runge::Components::BasicWordle