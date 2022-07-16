#include "qt_basic_gui_game.hpp"

#include <QAction>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPoint>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <algorithm>
#include <utility>

constexpr int grid_width = 50;

namespace Runge::Game::privateDetails {
  using namespace ::std;
  using namespace ::Runge::Components::BasicWordle;
  using namespace ::Runge::Components::QtGUI;
  using namespace ::Runge::Utilities;
  using namespace ::Runge::Tools;
  BasicQtGUIGame::BasicQtGUIGame ( shared_ptr< BasicWordleGenerator > generator,
                                   shared_ptr< BasicWordleParser >    parser,
                                   int                                count,
                                   QWidget*                           parent )
    : grid_{new BasicWordleButtonGrid { 50, 10, 5, 6, 5, this} }
    , max_row_number_ ( count )
    , generator_ ( generator )
    , parser_ ( parser ) {
    Runge_debug_Message ( "Single Game Initialization", "Call basic Qt GUI game ctor." );
    answer_     = generator_->generate ( );
    row_number_ = 0;
    auto layout = new QVBoxLayout { this };
    layout->addWidget ( grid_, 0, Qt::AlignHCenter | Qt::AlignTop );
    this->setLayout ( layout );
    this->setMinimumHeight ( grid_->height ( ) );
    this->setMinimumWidth ( grid_->width ( ) );
    this->BasicQtGUIGame::new_game ( );
  }

  void BasicQtGUIGame::set_button_text_ ( int row, int col, QChar val ) {
    Runge_debug_Message ( "Single Game Running", QString ( "Set (%1, %2) to %3" ).arg ( row ).arg ( col ).arg ( val ) );
    ( *grid_ ) [ row ][ col ].set_text ( val );
  }

  void BasicQtGUIGame::set_button_color_ ( int row, int col, Marks::ComparedMark mark ) {
    RGBColor color { 0, 0, 0 };
    switch ( mark ) {
      case Marks::ComparedMark::Wrong: color = RGBColor { 150, 150, 150 }; break;
      case Marks::ComparedMark::Correct: color = RGBColor { 40, 200, 40 }; break;
      case Marks::ComparedMark::Misplaced: color = RGBColor { 230, 230, 10 }; break;
      case Marks::ComparedMark::Empty: color = RGBColor { 255, 255, 255 }; break;
      default: break;
    }
    Runge_debug_Message ( "Single Game Running",
                          QString ( "Set (%1, %2) to rgb(%3, %4, %5)" )
                              .arg ( row )
                              .arg ( col )
                              .arg ( color.red )
                              .arg ( color.green )
                              .arg ( color.blue ) );
    ( *grid_ ) [ row ][ col ].set_bg_color ( color );
  }

  void BasicQtGUIGame::shake_group_ ( int row ) {
    Runge_debug_Message ( "Single Game Running", QString ( "Shake row %1" ).arg ( row ) );
    ( *grid_ ) [ row ].shake ( );
  }

  void BasicQtGUIGame::eval_line_ ( ) {
    auto str
        = accumulate ( begin ( line_chars_ ), end ( line_chars_ ), QString { "" }, [] ( QString const& str, QChar c ) {
            return str + QString { c };
          } );
    Runge_debug_Message ( "Single Game Running", QString ( "Receive line %1" ).arg ( str ) );
    auto res = parser_->parse ( str.toLower ( ) );
    if ( res.is_error ( ) ) {
      for ( int i = 0; i < 5; ++i ) set_button_text_ ( row_number_, i, ' ' );
      shake_group_ ( row_number_ );
      return;
    } else {
      auto guess_    = res.value ( );
      auto compared_ = BasicWordleComparator::compare ( answer_, guess_ );
      for ( int i = 0; i < 5; ++i ) set_button_color_ ( row_number_, i, compared_.code ( ).at ( i ) );
      compared_wordles_.push_back ( compared_ );
      ++row_number_;
      if ( compared_ ) {
        state_ = Win;
        emit game_over ( state_.is_win ( ) );
        return;
      }
    }
  }

  void BasicQtGUIGame::new_game ( ) {
    for ( int i = 0; i < max_row_number_; ++i ) {
      for ( int j = 0; j < 5; ++j ) {
        set_button_text_ ( i, j, ' ' );
        set_button_color_ ( i, j, Marks::ComparedMark::Empty );
      }
    }
    this->answer_ = this->generator_->generate ( );
    Runge_debug_Message ( "Single Game Running", QString ( "New game with answer: %1" ).arg ( answer_.data ( ) ) );
    line_chars_.clear ( );
    row_number_ = 0;
    compared_wordles_.clear ( );
    state_ = Running;
  }

  void BasicQtGUIGame::resume_game ( ) {
    Runge_debug_Message ( "Single Game Running", "Resume game." );
    state_ = Running;
  }

  void BasicQtGUIGame::pause_game ( ) {
    Runge_debug_Message ( "Single Game Running", "Pause game." );
    state_ = Paused;
  }

  QString BasicQtGUIGame::get_help ( ) const {
    Runge_debug_Message ( "Single Game Running", "Get help." );
    static const QString help_msg = "这是一款基于 Qt C++ 编写的 Wordle 小游戏，你一共有六次机会猜一个"
                                    "长度为五的英文单词。\n\n敲击键盘上的对应按键即可输入，按下退格删除"
                                    "当前输入，按下回车确认本行猜测，结果将会用色块来表示：\n\n"
                                    "如果颜色为绿色，说明猜测字母正确且位置正确；为黄色，则说明字母正确位置错"
                                    "误；否则是灰色。\n\n"
                                    "你可以在选单中重新开始游戏，每局游戏都会随机产生答案，祝你好运！";
    return help_msg;
  }


  void BasicQtGUIGame::deal_keys_ ( int val ) {
    if ( row_number_ == max_row_number_ ) {
      state_ = Lose;
      emit game_over ( state_.is_win ( ) );
      return;
    }
    if ( ( val == Qt::Key_Enter || val == Qt::Key_Return ) && line_chars_.size ( ) == 5 ) {
      eval_line_ ( );
      line_chars_.clear ( );
    } else if ( val <= Qt::Key_Z && val >= Qt::Key_A && line_chars_.size ( ) < 5 ) {
      set_button_text_ ( row_number_, line_chars_.size ( ), QChar ( val ) );
      line_chars_.push_back ( QChar ( val ) );
    } else if ( val == Qt::Key_Backspace && ! line_chars_.empty ( ) ) {
      line_chars_.pop_back ( );
      set_button_text_ ( row_number_, line_chars_.size ( ), QChar ( ' ' ) );
    } else {
      return;
    }
  }

  void BasicQtGUIGame::keyPressEvent ( QKeyEvent* key ) {
    Runge_debug_Message ( "Single Game Running", QString ( "Key pressed: %1" ).arg ( key->text ( ) ) );
    if ( state_.is_running ( ) ) deal_keys_ ( key->key ( ) );
  }
  QString BasicQtGUIGame::get_answer ( ) const { return answer_.data ( ); }

}; // namespace Runge::Game::privateDetails
