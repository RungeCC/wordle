#include "qt_gui_game_framework.hpp"

#include "concepts.h++"
#include "tools.h++"
#include "utilities.h++"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

namespace Runge::Game::privateDetails {
  using namespace ::Runge::QtGUIInterface;
  using namespace ::Runge::Utilities;

  QtGUIGameFramework::QtGUIGameFramework ( IGameWidget* center_widget, QWidget* parent ) : widget ( center_widget ) {
    Runge_debug_Message ( "Game Framework Initialization", "Calling game framework ctor." );
    auto game_item          = this->menuBar ( )->addMenu ( "Game" );
    auto help_item          = this->menuBar ( )->addMenu ( "Help" );
    auto new_game_action    = new QAction ( "New game", this );
    auto get_help_action    = new QAction ( "Get help", this );
    auto pause_game_action  = new QAction ( "Pause game", this );
    auto resume_game_action = new QAction ( "Resume game", this );
    new_game_action->setShortcut ( QKeySequence::New );
    get_help_action->setShortcut ( Qt::Key_F1 );
    pause_game_action->setShortcut ( QKeySequence ( Qt::CTRL | Qt::Key_P ) );
    resume_game_action->setShortcut ( QKeySequence ( Qt::CTRL | Qt::Key_R ) );
    game_item->addAction ( new_game_action );
    game_item->addAction ( pause_game_action );
    game_item->addAction ( resume_game_action );
    help_item->addAction ( get_help_action );
    QObject::connect ( new_game_action, SIGNAL ( triggered ( ) ), this, SLOT ( new_game ( ) ) );
    QObject::connect ( get_help_action, SIGNAL ( triggered ( ) ), this, SLOT ( get_help ( ) ) );
    QObject::connect ( pause_game_action, SIGNAL ( triggered ( ) ), this, SLOT ( pause_game ( ) ) );
    QObject::connect ( resume_game_action, SIGNAL ( triggered ( ) ), this, SLOT ( resume_game ( ) ) );
    QObject::connect ( widget, SIGNAL ( game_over ( bool ) ), this, SLOT ( game_over ( bool ) ) );
    this->setCentralWidget ( widget );
    this->setWindowTitle ( widget->get_name ( ) );
    widget->setParent ( this );
  }

  void QtGUIGameFramework::new_game ( ) {
    Runge_debug_Message ( "Game Framework Running", "New game." );
    widget->new_game ( );
  }

  void QtGUIGameFramework::get_help ( ) {
    Runge_debug_Message ( "Game Framework Running", "Show help message." );
    auto msg_box = new QMessageBox ( this );
    msg_box->setWindowTitle ( "help message" );
    msg_box->setText ( widget->get_help ( ) );
    msg_box->setWindowTitle ( "help message" );
    msg_box->exec ( );
  }

  void QtGUIGameFramework::game_over ( bool mark ) {
    Runge_debug_Message ( "Game Framework Running",
                          "Show game over message. Result:" + QString ( mark ? "Win" : "Lose" ) );
    auto msg_box = new QMessageBox ( this );
    if ( mark ) {
      msg_box->setWindowTitle ( "Congratulations!" );
      msg_box->setText ( "You win!" );
    } else {
      msg_box->setWindowTitle ( "Sorry." );
      msg_box->setText ( QString ( "You lose! The answer is %1." ).arg ( widget->get_answer ( ) ) );
    }
    msg_box->exec ( );
  }
  void QtGUIGameFramework::pause_game ( ) {
    Runge_debug_Message ( "Game Framework Running", "Pause game." );
    widget->pause_game ( );
  }
  void QtGUIGameFramework::resume_game ( ) {
    Runge_debug_Message ( "Game Framework Running", "Resume game." );
    widget->resume_game ( );
  }

}; // namespace Runge::Game::privateDetails
