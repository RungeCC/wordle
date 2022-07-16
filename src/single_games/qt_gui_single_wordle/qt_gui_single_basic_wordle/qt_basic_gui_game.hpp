#ifndef FINAL_PROJ_QT_BASIC_GUI_GAME_HPP_
#define FINAL_PROJ_QT_BASIC_GUI_GAME_HPP_

#include "components/basic_wordle.h++"
#include "components/qt_gui.h++"
#include "interfaces.h++"
#include "tools.h++"

#include <QGroupBox>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMetaType>
#include <QObject>
#include <QPushButton>
#include <QToolButton>
#include <QVector>
#include <QWidget>
#include <memory>


namespace Runge::Game::privateDetails {
  using namespace ::Runge::Components::BasicWordle;
  using namespace ::Runge::QtGUIInterface;
  using namespace ::Runge::Components::QtGUI;
  using namespace ::Runge::Tools;
  using namespace ::std;
  class BasicQtGUIGame : public IGameWidget {
    Q_OBJECT
  public:
    explicit BasicQtGUIGame ( shared_ptr< BasicWordleGenerator >,
                              shared_ptr< BasicWordleParser >,
                              int      = 6,
                              QWidget* = nullptr );
    ~BasicQtGUIGame ( ) override = default;

  protected:
    void keyPressEvent ( QKeyEvent* ) override;

  private:
    BasicWordleButtonGrid*             grid_;
    QVector< BasicComparedWordle >     compared_wordles_;
    int                                max_row_number_;
    int                                row_number_;
    QVector< QChar >                   line_chars_;
    BasicWordle                        answer_;
    shared_ptr< BasicWordleGenerator > generator_;
    shared_ptr< BasicWordleParser >    parser_;
    GameStateMark                      state_;

  private:
    void deal_keys_ ( int );
    void set_button_text_ ( int row, int col, QChar val );
    void set_button_color_ ( int row, int col, Marks::ComparedMark mark );
    void shake_group_ ( int row );
    void eval_line_ ( );

  public:
    void                  new_game ( ) override;
    [[nodiscard]] QString get_help ( ) const override;
    void                  pause_game ( ) override;
    void                  resume_game ( ) override;
    QString               get_answer ( ) const override;
    [[nodiscard]] QString get_name ( ) const override { return "basic wordle game"; }
  signals:
    void game_over ( bool );
  };
}; // namespace Runge::Game::privateDetails

namespace Runge::Game {
  using ::Runge::Game::privateDetails::BasicQtGUIGame;
}; // namespace Runge::Game

namespace Runge::SingleGames {
  using ::Runge::Game::privateDetails::BasicQtGUIGame;
}; // namespace Runge::SingleGames


#endif // QT_BASIC_GUI_GAME_HPP
