#include "wordle.hpp"

#include <QChar>
#include <QFile>
#include <QMap>
#include <QSet>
#include <QString>
#include <QTextStream>
#include <random>

#if defined ( _WIN32 ) || defined( _WIN64 )

#include <windows.h> // windows api. 提供不同的控制台颜色

#endif

enum class HexColor {
  Black  [[maybe_unused]] = 0x0
  , Blue [[maybe_unused]] = 0x1
  , Green [[maybe_unused]] = 0x2
  , LakeBlue [[maybe_unused]] = 0x3
  , Red [[maybe_unused]] = 0x4
  , Purple [[maybe_unused]] = 0x5
  , Yellow [[maybe_unused]] = 0x6
  , LightGray  [[maybe_unused]] = 0x7
  , Gray  [[maybe_unused]] = 0x8
  , LightBlue  [[maybe_unused]] = 0x9
  , LightGreen  [[maybe_unused]] = 0xA
  , Cyan  [[maybe_unused]] = 0xB
  , LightRed  [[maybe_unused]] = 0xC
  , LightPurple  [[maybe_unused]] = 0xD
  , LightWhite  [[maybe_unused]] = 0xE
  , White  [[maybe_unused]] = 0xF
};

void set_console_color (
        HexColor foreground, HexColor background
) {
#if defined ( _WIN32 ) || defined( _WIN64 )
  SetConsoleTextAttribute ( GetStdHandle ( STD_OUTPUT_HANDLE ),
                            16 * qint16 ( background ) +
                            qint16 ( foreground ) );
#endif
}

void reset_console_color ( ) {
  set_console_color ( HexColor::White, HexColor::Black );
}

void colored_output ( const QString& str, HexColor foreground
                      , HexColor background ) {
  QTextStream qout { stdout };
  set_console_color ( foreground, background );
  qout << str << Qt::flush;
  reset_console_color ( );
}

using namespace ::std;
using namespace ::std::literals;

void Runge::Game::load_wordle_words ( const QString& filename ) {
  QFile file { filename };
  file.open ( QIODevice::ReadOnly | QIODevice::Text );

  QTextStream is { &file };
  QString line;

  while ( !is.atEnd ( ) ) {
    line = is.readLine ( );
    if ( line == "" )
      continue;
    wordle_data_.push_back ( line.first ( 5 ) );
    //    qDebug() << "1" << Qt::endl;
  }
  inited_ = true;
}

static constexpr char const filename[] =
        "C:\\Users\\21104\\OneDrive\\Project\\vscprojs\\cpp\\cpp_oop\\final_"
        "proj\\asset\\word5.txt";

void Runge::Game::init ( ) { load_wordle_words ( filename ); }

void Runge::Game::start ( ) {
  QTextStream qout { stdout };
  if ( !this->is_init ( ) ) {
    throw logic_error ( "can not start a game when it has not inited." );
  }

  qout << "Welcome! This is a wordle game designed by Runge." << Qt::endl;

  qout << "Rule: try to guess the word(in length 5)." << Qt::endl;

  QTextStream qin { stdin };

  QChar status;

  while ( true ) { //  main loop
    qout << "[N]ew game, [Q]uit, [H]elp." << Qt::endl;

    status = qin.readLine ( ).at ( 0 );

    switch ( status.toUpper ( ).cell ( ) ) {
      case ( 'N' ):
        qout << "new" << Qt::endl;
        basic_wordle ( );
        break;
      case ( 'H' ):
        qout << "help" << Qt::endl;
        break;
      case ( 'Q' ):
        qout << "quit" << Qt::endl;
        exit ( 0 ); // 结束函数
      default:
        continue; // 重新选择
    }
  }
}

QVector< Runge::GuessState >
basic_wordle_comparator ( const QString& answer, const QString& guess );

void basic_wordle_shower ( QString const& answer, QString const& guess );

void
basic_wordle_colored_shower ( QString const& answer, QString const& guess );

void Runge::Game::basic_wordle ( ) {
  QTextStream qout { stdout };
  random_device rd;
  mt19937_64 engine ( rd ( ) );
  uniform_int_distribution< qsizetype > int_dist ( 0, wordle_data_.count ( ) -
                                                      1 );
  QString guess;
  QString answer = wordle_data_[ int_dist ( engine ) ];
  QTextStream qin { stdin };
  qint16 count_max = 6;
  qint16 count = count_max;
  while ( true ) { // basic game loop
    guess.clear ( );
    if ( count == 0 ) {
      qout << "you lost the game, the answer is " << answer << Qt::endl;
      break;
    }
    qout << "Please guess(" << count_max - count + 1 << "/" << count_max
         << "):" << Qt::endl;


    guess = qin.readLine ( ).remove ( '\n' ).toLower ( );

    if ( !wordle_data_.contains ( guess ) ) {
      qout << "invalid guess." << Qt::endl;
      continue;
      // 如果输入不正确则开始下一个循环
    }
    --count;
    basic_wordle_colored_shower ( answer, guess );
    qout << Qt::endl;
  }
}

void
basic_wordle_shower ( QString const& answer
                      , QString const& guess ) {
  QTextStream qout { stdout };
  qout << guess << Qt::endl;
  for ( const auto& c: basic_wordle_comparator ( answer, guess ) ) {

    switch ( c ) {
      case Runge::GuessState::Wrong:
        qout << "x";
        break;
      case Runge::GuessState::Correct:
        qout << "^";
        break;
      case Runge::GuessState::Misplaced:
        qout << "~";
        break;
      default:
        qout << " ";
        break;
    }
  }
}

void
basic_wordle_colored_shower ( QString const& answer
                              , QString const& guess ) {
  QTextStream qout { stdout };
  QVector< Runge::GuessState > res = basic_wordle_comparator ( answer,
                                                               guess );
  for ( qsizetype i = 0; i < answer.count ( ); ++i ) {
    switch ( res[ i ] ) {
      case Runge::GuessState::Wrong:
        colored_output ( guess[ i ], HexColor::Gray, HexColor::Black );
        break;
      case Runge::GuessState::Correct:
        colored_output ( guess[ i ], HexColor::Green, HexColor::Black );
        break;
      case Runge::GuessState::Misplaced:
        colored_output ( guess[ i ], HexColor::Yellow, HexColor::Black );
        break;
      default:
        break;
    }
  }
  qout << Qt::endl;
}

QVector< Runge::GuessState >
basic_wordle_comparator ( const QString& answer, const QString& guess ) {
  QVector< Runge::GuessState > res;
  QMap< QChar, QSet< qsizetype>> answer_map;
  QMap< QChar, qsizetype > misplaced_map;
  for ( auto it = cbegin ( answer ); it != cend ( answer ); ++it ) {
    answer_map[ *it ].insert ( it - cbegin ( answer ) );
    misplaced_map[ *it ] = 0;
  }

  for ( auto it = guess.cbegin ( ); it != guess.cend ( ); ++it ) {
    if ( !answer_map.contains ( *it ) ) {
      res.push_back ( Runge::GuessState::Wrong );
    } else {
      if ( answer_map[ *it ].contains ( it - cbegin ( guess ) ) ) {
        res.push_back ( Runge::GuessState::Correct );
        answer_map[ *it ].remove ( it - cbegin ( guess ) );
      } else {
        if ( answer_map[ *it ].size ( ) > misplaced_map[ *it ] ) {
          res.push_back ( Runge::GuessState::Misplaced );
          ++misplaced_map[ *it ];
        } else {
          res.push_back ( Runge::GuessState::Wrong );
        }
      }
    }
  }

  return res;
}

