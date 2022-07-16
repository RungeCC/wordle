//
// Created by runge on 22-6-30.
//

#ifndef FINAL_PROJ_BASIC_WORDLE_QT_BUTTON_GROUP_HPP_
#define FINAL_PROJ_BASIC_WORDLE_QT_BUTTON_GROUP_HPP_

#include "basic_wordle_qt_button.hpp"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QToolButton>
#include <QVector>

namespace Runge::Components::QtGUI {

  class BasicWordleButtonGroup :  public QGroupBox {
    Q_OBJECT
  private:
    QVector< BasicWordleButton* > line_buttons_;

  public:
    explicit BasicWordleButtonGroup ( int grid_size= 50, int sep_size = 10, int count = 5, QWidget* parent= nullptr );
    ~BasicWordleButtonGroup ( ) override = default;

  public:
    void shake ( int amplitude = 5, int duration = 50, int loop = 2 );

  public:
    BasicWordleButton& operator[](int);
  };

}; // namespace Runge::Components::QtGUI

#endif // FINAL_PROJ_BASIC_WORDLE_QT_BUTTON_GROUP_HPP_
