#include "basic_wordle_qt_button.hpp"

namespace Runge::Components::QtGUI {


  void BasicWordleButton::set_bg_color ( Utilities::RGBColor color ) {
    this->setStyleSheet (
        QString ( "background-color: rgb(%1, %2, %3);" ).arg ( color.red ).arg ( color.green ).arg ( color.blue ) );
  }
  void  BasicWordleButton::set_text ( QChar ch ) { this->setText ( ch ); }
  QChar BasicWordleButton::get_text ( ) { return this->text ( ) [ 0 ]; }

}; // namespace Runge::Components::QtGUI