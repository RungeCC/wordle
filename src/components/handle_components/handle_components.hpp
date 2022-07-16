#ifndef FINAL_PROJ_HANDLE_COMPONENTS_HPP_
#define FINAL_PROJ_HANDLE_COMPONENTS_HPP_

#include "tools.h++"
#include "utilities.h++"

#include <QChar>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <QVector>
#include <algorithm>
#include <matchit.h>
#include <memory>

namespace Runge::Components::Handle::privateDetails {
  using namespace ::Runge::Utilities;
  using namespace ::Runge::Tools;
  using namespace ::matchit;
  using namespace ::std;
  enum class Initial {
    B,
    P,
    M,
    F,
    D,
    T,
    N,
    L,
    G,
    K,
    H,
    J,
    Q,
    R,
    X,
    W,
    Y,
    ZH,
    CH,
    SH,
    Z,
    C,
    S,
    Zero // 零声母
  };
  enum class Final {
    A,
    AI,
    AN,
    ANG,
    AO,
    E,
    EI,
    EN,
    ENG,
    ER,
    I,
    IA,
    IAN,
    IANG,
    IAO,
    IE,
    IN,
    ING,
    IO,
    IONG,
    IU,
    O,
    ONG,
    OU,
    U,
    UA,
    UAI,
    UAN,
    UANG,
    UI,
    UN,
    UO,
    V,
    VAN,
    VE,
    VN
  };
  enum class Tone {
    Flat, // 阴平
    Raising,
    FallingRaising,
    Falling,
    Neutral
  };
  struct Syllable {
    Initial     initial;
    Final       final;
    Tone        tone;
    friend bool operator== ( Syllable const& lhs, Syllable const& rhs ) = default;
  };

  class SyllableParser {
  private:
    static Initial parse_initial ( QString const& str ) {
      auto res = match ( str ) ( pattern | "b"  = expr ( Initial::B ),
                                 pattern | "p"  = expr ( Initial::P ),
                                 pattern | "m"  = expr ( Initial::M ),
                                 pattern | "f"  = expr ( Initial::F ),
                                 pattern | "d"  = expr ( Initial::D ),
                                 pattern | "t"  = expr ( Initial::T ),
                                 pattern | "n"  = expr ( Initial::N ),
                                 pattern | "l"  = expr ( Initial::L ),
                                 pattern | "g"  = expr ( Initial::G ),
                                 pattern | "k"  = expr ( Initial::K ),
                                 pattern | "h"  = expr ( Initial::H ),
                                 pattern | "j"  = expr ( Initial::J ),
                                 pattern | "q"  = expr ( Initial::Q ),
                                 pattern | "r"  = expr ( Initial::R ),
                                 pattern | "x"  = expr ( Initial::X ),
                                 pattern | "w"  = expr ( Initial::W ),
                                 pattern | "y"  = expr ( Initial::Y ),
                                 pattern | "zh" = expr ( Initial::ZH ),
                                 pattern | "ch" = expr ( Initial::CH ),
                                 pattern | "sh" = expr ( Initial::SH ),
                                 pattern | "z"  = expr ( Initial::Z ),
                                 pattern | "c"  = expr ( Initial::C ),
                                 pattern | "s"  = expr ( Initial::S ),
                                 pattern | ""   = expr ( Initial::Zero ) );
      return res;
    }
    static Final parse_final ( QString const& str ) {
      auto res = match ( str ) ( pattern | "a"    = expr ( Final::A ),
                                 pattern | "ai"   = expr ( Final::AI ),
                                 pattern | "an"   = expr ( Final::AN ),
                                 pattern | "ang"  = expr ( Final::ANG ),
                                 pattern | "ao"   = expr ( Final::AO ),
                                 pattern | "e"    = expr ( Final::E ),
                                 pattern | "ei"   = expr ( Final::EI ),
                                 pattern | "en"   = expr ( Final::EN ),
                                 pattern | "eng"  = expr ( Final::ENG ),
                                 pattern | "er"   = expr ( Final::ER ),
                                 pattern | "i"    = expr ( Final::I ),
                                 pattern | "ia"   = expr ( Final::IA ),
                                 pattern | "ian"  = expr ( Final::IAN ),
                                 pattern | "iang" = expr ( Final::IANG ),
                                 pattern | "iao"  = expr ( Final::IAO ),
                                 pattern | "ie"   = expr ( Final::IE ),
                                 pattern | "in"   = expr ( Final::IN ),
                                 pattern | "ing"  = expr ( Final::ING ),
                                 pattern | "io"   = expr ( Final::IO ),
                                 pattern | "iong" = expr ( Final::IONG ),
                                 pattern | "iu"   = expr ( Final::IU ),
                                 pattern | "o"    = expr ( Final::O ),
                                 pattern | "ong"  = expr ( Final::ONG ),
                                 pattern | "on"   = expr ( Final::ONG ),
                                 pattern | "ou"   = expr ( Final::OU ),
                                 pattern | "u"    = expr ( Final::U ),
                                 pattern | "ua"   = expr ( Final::UA ),
                                 pattern | "uai"  = expr ( Final::UAI ),
                                 pattern | "uan"  = expr ( Final::UAN ),
                                 pattern | "uang" = expr ( Final::UANG ),
                                 pattern | "ui"   = expr ( Final::UI ),
                                 pattern | "un"   = expr ( Final::UN ),
                                 pattern | "uo"   = expr ( Final::UO ),
                                 pattern | "v"    = expr ( Final::V ),
                                 pattern | "van"  = expr ( Final::VAN ),
                                 pattern | "ve"   = expr ( Final::VE ),
                                 pattern | "ue"   = expr ( Final::VE ),
                                 pattern | "vn"   = expr ( Final::VN ) );
      return res;
    }
    static Tone parse_tone ( QString const& str ) {
      auto res = match ( str ) ( pattern | "1" = expr ( Tone::Flat ),
                                 pattern | "2" = expr ( Tone::Raising ),
                                 pattern | "3" = expr ( Tone::FallingRaising ),
                                 pattern | "4" = expr ( Tone::Falling ),
                                 pattern | ""  = expr ( Tone::Neutral ) );
      return res;
    }

  public:
    static Syllable parse ( QString const& str ) {
      Syllable result;
      if ( str.length ( ) == 0 ) {
        // error;
      }
      QVector< QChar > vowels = { 'a', 'e', 'i', 'o', 'u', 'v' };
      QVector< QChar > tones  = { '1', '2', '3', '4' };
      auto             it1
          = find_if ( str.begin ( ), str.end ( ), [ &vowels ] ( QChar const& c ) { return vowels.contains ( c ); } );
      auto pos1      = distance ( str.begin ( ), it1 );
      result.initial = parse_initial ( str.first ( pos1 ) );
      auto ends      = str.last ( str.size ( ) - pos1 );
      if ( tones.contains ( str.back ( ) ) ) {
        result.tone = parse_tone ( str.back ( ) );
        ends        = ends.left ( ends.size ( ) - 1 );
      } else {
        result.tone = Tone::Neutral;
      }
      result.final = parse_final ( ends );
      return result;
    }
  };

  struct SyllableMark {
    ComparedMark initial_mark;
    ComparedMark final_mark;
    ComparedMark tone_mark;
    friend bool  operator== ( SyllableMark const& lhs, SyllableMark const& rhs ) = default;
  };

  struct HanCharacter {
    QChar       word;
    Syllable    syllable;
    friend bool operator== ( HanCharacter const& lhs, HanCharacter const& rhs ) = default;
  };

  struct HanCharacterMark {
    ComparedMark word_mark;
    SyllableMark syllable_mark;
    friend bool  operator== ( HanCharacterMark const& lhs, HanCharacterMark const& rhs ) = default;
  };
}; // namespace Runge::Components::Handle::privateDetails

namespace Runge::StringUtilities::privateDetails {
  using namespace ::Runge::Components::Handle::privateDetails;
  template <>
  struct StringizerHelper< Initial > {
    static QString convert ( Initial const& val ) {
      switch ( val ) {
        case Initial::B: return "b";
        case Initial::P: return "p";
        case Initial::M: return "m";
        case Initial::F: return "f";
        case Initial::D: return "d";
        case Initial::T: return "t";
        case Initial::N: return "n";
        case Initial::L: return "l";
        case Initial::G: return "g";
        case Initial::K: return "k";
        case Initial::H: return "h";
        case Initial::J: return "j";
        case Initial::Q: return "q";
        case Initial::R: return "r";
        case Initial::X: return "x";
        case Initial::W: return "w";
        case Initial::Y: return "y";
        case Initial::ZH: return "zh";
        case Initial::CH: return "ch";
        case Initial::SH: return "sh";
        case Initial::Z: return "z";
        case Initial::C: return "c";
        case Initial::S: return "s";
        case Initial::Zero: return "";
      }
      return ""; // 不可达
    }
  };

  template <>
  struct StringizerHelper< Final > {
    static QString convert ( Final const& val ) {
      switch ( val ) {
        case Final::A: return "a";
        case Final::AI: return "ai";
        case Final::AN: return "an";
        case Final::ANG: return "ang";
        case Final::AO: return "ao";
        case Final::E: return "e";
        case Final::EI: return "ei";
        case Final::EN: return "en";
        case Final::ENG: return "eng";
        case Final::ER: return "er";
        case Final::I: return "i";
        case Final::IA: return "ia";
        case Final::IAN: return "ian";
        case Final::IANG: return "iang";
        case Final::IAO: return "iao";
        case Final::IE: return "ie";
        case Final::IN: return "in";
        case Final::ING: return "ing";
        case Final::IO: return "io";
        case Final::IONG: return "iong";
        case Final::IU: return "iu";
        case Final::O: return "o";
        case Final::ONG: return "ong";
        case Final::OU: return "ou";
        case Final::U: return "u";
        case Final::UA: return "ua";
        case Final::UAI: return "uai";
        case Final::UAN: return "uan";
        case Final::UANG: return "uang";
        case Final::UI: return "ui";
        case Final::UN: return "un";
        case Final::UO: return "uo";
        case Final::V: return "v";
        case Final::VAN: return "van";
        case Final::VE: return "ve";
        case Final::VN: return "vn";
        default: return ""; // 不可达
      }
    }
  };

  template <>
  struct StringizerHelper< Tone > {
    static QString convert ( Tone const& val ) {
      switch ( val ) {
        case Tone::Flat: return "1";
        case Tone::Raising: return "2";
        case Tone::FallingRaising: return "3";
        case Tone::Falling: return "4";
        case Tone::Neutral: return "";
        default: return ""; // 不可达
      }
    }
  };

  template <>
  struct StringizerHelper< Syllable > {
    static QString convert ( Syllable const& val ) {
      return Stringizer::convert ( val.initial ) + Stringizer::convert ( val.final ) + Stringizer::convert ( val.tone );
    }
  };
}; // namespace Runge::StringUtilities::privateDetails

namespace Runge::Components::Handle {
  using privateDetails::HanCharacter;
  using privateDetails::HanCharacterMark;
  class Handle {
  private:
    QVector< HanCharacter > words_;

  public:
    Runge_Generate_Regular ( Handle )

  public:
    Handle ( QString const& data ) { // 从数据行解析成语字段
      using privateDetails::Syllable;
      using privateDetails::SyllableMark;
      using privateDetails::SyllableParser;
      using namespace ::std;
      auto                str_list = data.split ( ' ' );
      auto                chars    = str_list [ 0 ];
      QVector< Syllable > syllables { 4 };
      transform ( begin ( str_list ) + 1, end ( str_list ), begin ( syllables ), [] ( QString const& str ) {
        return SyllableParser::parse ( str );
      } );
      HanCharacter han_char;
      for ( int i = 0; i < 4; ++i ) {
        han_char.word     = chars [ i ];
        han_char.syllable = syllables [ i ];
        words_.push_back ( han_char );
      }
    }

  public:
    [[nodiscard]] QVector< HanCharacter > const& words ( ) const noexcept { return words_; }
  };

  class ComparedHandle {
  public:
    using wordle        = Handle;
    using compared_mark = Runge::Tools::ComparedMark;

  private:
    QVector< HanCharacter >     words_;
    QVector< HanCharacterMark > marks_;

  public:
    Runge_Generate_Regular ( ComparedHandle )

  public:
    ComparedHandle ( QVector< HanCharacter > const& words, QVector< HanCharacterMark > const& marks )
      : words_ { words }
      , marks_ { marks } { }

  public:
    [[nodiscard]] QVector< HanCharacter > const&     word ( ) const noexcept { return words_; }
    [[nodiscard]] QVector< HanCharacterMark > const& code ( ) const noexcept { return marks_; }

  public:
    explicit operator bool ( ) const noexcept {
      return std::all_of ( std::begin ( marks_ ), std::end ( marks_ ), [] ( HanCharacterMark const& mark ) {
        return mark.word_mark == Marks::ComparedMark::Correct;
      } );
    }
    [[nodiscard]] bool is_correct ( ) const noexcept { return this->operator bool ( ); }
  };

  class HandleComparator {
  public:
    using wordle          = Handle;
    using compared_wordle = ComparedHandle;

  public:
    Runge_Generate_Abstract ( HandleComparator )

  public:
    static ComparedHandle compare ( Handle const& answer, Handle const& guess ) {
      using namespace Runge::Comparators;
      using privateDetails::Final;
      using privateDetails::Initial;
      using privateDetails::SyllableMark;
      using privateDetails::Tone;
      QVector< HanCharacterMark > han_char_marks;
      auto                        ans_words = answer.words ( );
      QString                     ans_chars;
      QVector< Initial >          ans_initials;
      QVector< Final >            ans_finals;
      QVector< Tone >             ans_tones;
      for ( auto const& word : ans_words ) {
        ans_chars += word.word;
        ans_initials.push_back ( word.syllable.initial );
        ans_finals.push_back ( word.syllable.final );
        ans_tones.push_back ( word.syllable.tone );
      }
      auto               gus_words = guess.words ( );
      QString            gus_chars;
      QVector< Initial > gus_initials;
      QVector< Final >   gus_finals;
      QVector< Tone >    gus_tones;
      for ( auto const& word : gus_words ) {
        gus_chars += word.word;
        gus_initials.push_back ( word.syllable.initial );
        gus_finals.push_back ( word.syllable.final );
        gus_tones.push_back ( word.syllable.tone );
      }
      auto             initial_marks = BasicContainerComparator::compare ( ans_initials, gus_initials );
      auto             final_marks   = BasicContainerComparator::compare ( ans_finals, gus_finals );
      auto             tone_marks    = BasicContainerComparator::compare ( ans_tones, gus_tones );
      auto             char_marks    = BasicStringComparator::compare ( ans_chars, gus_chars );
      HanCharacterMark han_mark;
      SyllableMark     syllable_mark;
      for ( int i = 0; i < initial_marks.size ( ); ++i ) {
        syllable_mark.initial_mark = initial_marks [ i ];
        syllable_mark.final_mark   = final_marks [ i ];
        syllable_mark.tone_mark    = tone_marks [ i ];
        han_mark.syllable_mark     = syllable_mark;
        han_mark.word_mark         = char_marks [ i ];
        han_char_marks.push_back ( han_mark );
      }
      return ComparedHandle { gus_words, han_char_marks };
    }
  };

  class HandleResourceHolder {
  public:
    using wordle = Handle;

  public:
    Runge_Generate_Just_Movable ( HandleResourceHolder )

  public:
    explicit HandleResourceHolder ( QFile& file ) {
      if ( ! file.open ( QIODevice::ReadOnly | QIODevice::Text ) ) {
        Runge_debug_Message ( "Resource Loading", "Can not open file: " + file.fileName ( ) );
        exit ( 1 );
        // error!
      }
      QTextStream stream { &file };
      while ( ! stream.atEnd ( ) ) handles_.push_back ( Handle { stream.readLine ( ).remove ( '\n' ) } );
      Runge_debug_Message ( "Resource Loading",
                            QString ( "Loading finished, find %1 wordles." ).arg ( this->handles_.size ( ) ) );
      file.close ( );
    }

  public:
    [[nodiscard]] QVector< Handle > const& data ( ) const noexcept { return handles_; }
    [[nodiscard]] qsizetype                size ( ) const noexcept { return handles_.size ( ); }

  private:
    QVector< Handle > handles_;
  };

  using HandleGenerator = Generators::BasicRandomGenerator< HandleResourceHolder >;

  enum class HandleParserError {
    InvalidWordle
  };
  class HandleParser {
  public:
    Runge_Generate_Just_Movable ( HandleParser )

  public:
    using wordle          = Handle;
    using resource_holder = HandleResourceHolder;
    using error           = HandleParserError;
    using io_device       = Utilities::QtCLIDevice;
    using result          = Utilities::Result< Handle, HandleParserError >;

  private:
    std::shared_ptr< HandleResourceHolder > res_ptr_;

  public:
    explicit HandleParser ( std::shared_ptr< HandleResourceHolder > res ) : res_ptr_ ( res ) { }

  public:
    Utilities::Result< Handle, HandleParserError > parse ( QString const& str ) {
      auto comparator = [ &str ] ( Handle const& handle ) {
        for ( int i = 0; i < handle.words ( ).size ( ); ++i )
          if ( handle.words ( ) [ i ].word != str [ i ] ) return false;
        return true;
      };
      auto it = std::find_if ( res_ptr_->data ( ).begin ( ), res_ptr_->data ( ).end ( ), comparator );
      if ( it != res_ptr_->data ( ).end ( ) )
        return *it;
      else
        return HandleParserError::InvalidWordle;
    }
  };

  template < class Scheme >
  class ColoredHandleFormatter {
  public:
    Runge_Generate_Abstract ( ColoredHandleFormatter )

  public:
    using wordle          = Handle;
    using compared_wordle = ComparedHandle;
    using io_device       = IODevice::QtCLIDevice;
    using color           = Utilities::Color;
    using color_scheme    = Scheme;

  public:
    static QTextStream& print ( QTextStream& out, Handle const& handle ) {
      using namespace Runge::Utilities;
      auto words = handle.words ( );
      for ( auto const& word : words ) {
        out << QString ( "%1" ).arg ( word.word ) << "(";
        out << Stringizer::convert ( word.syllable ) << ")";
      }
      return out;
    }

    static QTextStream& print ( QTextStream& out, ComparedHandle const& handle ) {
      using namespace Runge::Utilities;
      using namespace Runge::Tools;
      auto chooser         = ColorChooser< Scheme >::choose;
      auto words           = handle.word ( );
      auto marks           = handle.code ( );
      auto single_colorize = [] ( auto const& ch, Color color ) -> QString {
        return ColorWrapper::wrap ( Scheme::foreground, color ) ( QString ( "%1" ).arg ( ch ) );
      };
      ColoredSetter::set ( out, Scheme::foreground, chooser ( ComparedMark::Misplaced ) );
      for ( int i = 0; i < words.size ( ); ++i ) {
        out << single_colorize ( words [ i ].word, chooser ( marks [ i ].word_mark ) ) << "(";
        out << single_colorize ( Stringizer::convert ( words [ i ].syllable.initial ),
                                 chooser ( marks [ i ].syllable_mark.initial_mark ) );
        out << single_colorize ( Stringizer::convert ( words [ i ].syllable.final ),
                                 chooser ( marks [ i ].syllable_mark.final_mark ) );
        out << single_colorize ( Stringizer::convert ( words [ i ].syllable.tone ),
                                 chooser ( marks [ i ].syllable_mark.tone_mark ) );
        out << ")";
      }
      ColoredSetter::reset ( out );
      out << Qt::flush;
      return out;
    }
  };

  using DefaultColoredHandleFormatter = ColoredHandleFormatter< Marks::DefaultColorScheme >;
}; // namespace Runge::Components::Handle


#endif // FINAL_PROJ_HANDLE_COMPONENTS_HPP_
