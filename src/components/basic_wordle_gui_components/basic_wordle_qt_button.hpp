#ifndef FINAL_PROJ_BASIC_WORDLE_QT_BUTTON_HPP_
#define FINAL_PROJ_BASIC_WORDLE_QT_BUTTON_HPP_

#include "utilities.h++"

#include <QObject>
#include <QToolButton>

namespace Runge::Components::QtGUI {
  class BasicWordleButton :  public QToolButton {
    Q_OBJECT
  public:
    explicit BasicWordleButton ( int size, QWidget* parent = nullptr )
      : QToolButton { parent } {
      this->setMaximumHeight ( size );
      this->setMinimumHeight ( size );
      this->setMinimumWidth ( size );
      this->setMaximumWidth ( size );
    }
    ~BasicWordleButton ( ) override = default;

  public:
    void  set_bg_color ( Utilities::RGBColor );
    void  set_text ( QChar );
    QChar get_text ( );
  };
}; // namespace Runge::Components::QtGUI


#endif
