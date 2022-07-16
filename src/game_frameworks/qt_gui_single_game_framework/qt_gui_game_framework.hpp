#ifndef FINAL_PROJ_QT_GUI_GAME_FRAMEWORK_HPP_
#define FINAL_PROJ_QT_GUI_GAME_FRAMEWORK_HPP_

#include "interfaces.h++"
#include "tools.h++"
#include "utilities.h++"

#include <QMainWindow>

namespace Runge::Game::privateDetails {
  using namespace ::Runge::QtGUIInterface;
  using namespace ::Runge::Tools;
  class QtGUIGameFramework : public QMainWindow {
    Q_OBJECT
  public:
    explicit QtGUIGameFramework ( IGameWidget* center_widget, QWidget* parent = nullptr );

  private:
    IGameWidget* widget;

  public:
    void start ( ) {
      Runge_debug_Message ( "Game Framework Running", "Game start." );
      this->show ( );
    }

  public slots:
    void new_game ( );
    void get_help ( );
    void pause_game ( );
    void resume_game ( );
    void game_over ( bool );
  };
}; // namespace Runge::Game::privateDetails

namespace Runge::Game {
  using ::Runge::Game::privateDetails::QtGUIGameFramework;
}; // namespace Runge::Game

namespace Runge::GameFrameworks {
  using ::Runge::Game::privateDetails::QtGUIGameFramework;
}; // namespace Runge::GameFrameworks

#endif
