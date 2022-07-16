#ifndef FINAL_PROJ_QT_CLI_SINGLE_WORDLE_TEMPLATE_HPP_
#define FINAL_PROJ_QT_CLI_SINGLE_WORDLE_TEMPLATE_HPP_

#include "concepts.h++"
#include "utilities.h++"

#include <QString>
#include <QTextStream>
#include <QVector>
#include <memory>
#include <tuple>
#include <type_traits>
#include <variant>

namespace Runge::SingleGames::privateDetails {
  using namespace ::Runge::Concepts;
  using namespace ::Runge::Utilities;
  using namespace ::Runge::Tools;
  using namespace ::std;

  // 实际上并不需要真正传入 comparator
  // FIXME: 这里设计可以斟酌，我们这里要求传入所有模板参数，其实也可以设计一个默认参数
  // TODO: template<is_wordle Wordle, compared_wordle = ComparedWordle<Wordle>, ...>
  // TODO: 也就是偏特化类模板 ComparedWordle 等等
  template < is_io_device         IODevice,
             is_wordle_generator  WordleGenerator,
             is_wordle_comparator WordleComparator,
             is_wordle_formatter  WordleFormatter,
             is_wordle_parser     WordleParser >
    requires same_as<
                 typename WordleFormatter::compared_wordle,
                 typename WordleComparator::
                     compared_wordle > && same_as< typename WordleComparator::wordle, typename WordleGenerator::wordle > && same_as< typename WordleComparator::wordle, typename WordleParser::wordle > && same_as< IODevice, typename WordleFormatter::io_device > && same_as< IODevice, typename WordleParser::io_device >
  class QtCLISingleWordleTemplate {
  public:
    using wordle          = typename WordleComparator::wordle;
    using compared_wordle = typename WordleComparator::compared_wordle;
    using comparator      = WordleComparator;
    using generator       = WordleGenerator;
    using io_device       = IODevice;
    using formatter       = WordleFormatter;
    using parser          = WordleParser;

  private:
    shared_ptr< IODevice >                                io_device_;
    shared_ptr< WordleGenerator >                         generator_;
    shared_ptr< WordleParser >                            parser_;
    typename WordleComparator::wordle                     answer_;
    typename WordleComparator::wordle                     guess_;
    typename WordleComparator::compared_wordle            compared_;
    QVector< typename WordleComparator::compared_wordle > guesses_;
    quint16                                               max_count_;
    quint16                                               count_;
    const QString                                         name_;
    const QString                                         help_msg_;
    GameStateMark                                         state_ { };

  public:
    QtCLISingleWordleTemplate ( shared_ptr< IODevice >        io_device,
                                shared_ptr< WordleGenerator > generator,
                                shared_ptr< WordleParser >    parser,
                                quint16                       max_count,
                                QString                       name,
                                QString                       help_message )
      : io_device_ ( io_device )
      , generator_ ( generator )
      , parser_ ( parser )
      , max_count_ ( max_count )
      , count_ ( max_count )
      , name_ ( ::std::move ( name ) )
      , help_msg_ ( ::std::move ( help_message ) )
      , state_ ( Paused ) {
      Runge_debug_Message ( "Single Game Initialization", "Calling template ctor." );
    };

  public:
    [[nodiscard]] QString get_name ( ) const {
      Runge_debug_Message ( "Single Game Running", "Get name." );
      return name_;
    };

    [[nodiscard]] QString get_help ( ) const {
      Runge_debug_Message ( "Single Game Running", "Get help message." );
      return help_msg_;
    };

    [[nodiscard]] std::shared_ptr< IODevice > get_io_device ( ) const {
      Runge_debug_Message ( "Single Game Running", "Get IO Device." );
      return io_device_;
    }

  public: // 0, 1, 2, 3 (4)
    void new_game ( ) {
      guesses_.clear ( );
      count_    = 1;
      answer_   = generator_->generate ( );
      state_    = Running;
      auto& out = io_device_->get_out_stream ( );
      out << "new game has been started." << Qt::endl;
#ifdef Runge_Debug
      QString     str { "" };
      QTextStream stream { &str };
      WordleFormatter::print ( stream, answer_ );
      QString ans_str = stream.readAll ( ).trimmed ( );
      Runge_debug_Message ( "Single Game Running", QString ( "New game with wordle: %1" ).arg ( ans_str ) );
#endif
    }

    void pause_game ( ) noexcept {
      Runge_debug_Message ( "Single Game Running", "Pause game." );
      io_device_->get_out_stream ( ) << "game has been paused." << Qt::endl;
      state_ = Paused;
    }

    void resume_game ( ) noexcept {
      Runge_debug_Message ( "Single Game Running", "Resume game." );
      io_device_->get_out_stream ( ) << "game has been resumed." << Qt::endl;
      state_ = Running;
    }

  public:
    tuple< GameStateMark, NullableCommand > next_turn ( ) { // TODO: 重构为协议
      Runge_debug_Message ( "Single Game Running", "Next turn." );
      if ( state_.is_running ( ) ) {
        io_device_->get_out_stream ( ) << QString ( "please guess(%1/%2):" ).arg ( count_ ).arg ( max_count_ )
                                       << Qt::endl;
      }
      auto&   in   = io_device_->get_in_stream ( );
      // FIXME: 设计有问题，这里如果直接读取行，那么对 Wordle 的 Input 特化机制可能失效，因为 Wordle 可能是非单行的
      // TODO: 正确的设计应该是先尝试解析 Wordle，如果失败尝试解析 Command，如果依然失败则返回 invalid wordle 结果
      // TODO: 也不该用流函数这种罗嗦的东西，应该使用 WordleParser 类来解析流
      QString line = in.readLine ( );
      Runge_debug_Message ( "Single Game Running:Dealing New Turn", "Read line: " + line );
      auto command = CommandParser::parse ( line );
      if ( state_.is_running ( ) && ! command.has_value ( ) ) {
        Runge_debug_Message ( "Single Game Running:Dealing New Turn", "Dealing as wordle." );
        deal_input_ ( line );
      }
      auto res = make_pair ( state_, command );
      Runge_debug_Message ( "Single Game Running", "Back to game framework." );
      return res;
    }

  private:
    inline void deal_input_ ( QString& input ) {
      Runge_debug_Message ( "Single Game Running:Dealing Wordle", "Parse wordle." );
      auto  res = parser_->parse ( input );
      auto& out = io_device_->get_out_stream ( );
      if ( res.is_ok ( ) ) {
        Runge_debug_Message ( "Single Game Running:Dealing Wordle", "Parse wordle success." );
        guess_ = res.value ( );
      } else {
        Runge_debug_Message ( "Single Game Running:Dealing Wordle", "Parse wordle failed." );
        out << QString ( "%1 is not a valid wordle." ).arg ( input ) << Qt::endl;
        return;
      }
      Runge_debug_Message ( "Single Game Running:Dealing Wordle", "Compare wordles." );
      compared_ = WordleComparator::compare ( answer_, guess_ );
      guesses_.push_back ( compared_ );
      Runge_debug_Message ( "Single Game Running:Dealing Wordle", "Print out result." );
      if ( compared_ ) {
        WordleFormatter::print ( out, compared_ );
        out << Qt::endl;
        out << "you win!" << Qt::endl;
        state_ = Win;
        return;
      } else {
        WordleFormatter::print ( out, compared_ );
        out << Qt::endl;
      }
      if ( count_ == max_count_ ) {
        out << "you lose!" << Qt::endl;
        out << "the answer is ";
        WordleFormatter::print ( out, answer_ );
        out << "." << Qt::endl;
        state_ = Lose;
      } else {
        ++count_;
      }
      return;
    }
  };
}; // namespace Runge::SingleGames::privateDetails

namespace Runge::SingleGames {
  using privateDetails::QtCLISingleWordleTemplate;
}; // namespace Runge::SingleGames

#endif
