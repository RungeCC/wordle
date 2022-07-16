//
// Created by runge on 22-6-30.
//

#ifndef FINAL_PROJ_BASIC_WORDLE_QT_BUTTON_GRID_HPP_
#define FINAL_PROJ_BASIC_WORDLE_QT_BUTTON_GRID_HPP_

#include "basic_wordle_qt_button.hpp"
#include "basic_wordle_qt_button_group.hpp"

#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

namespace Runge::Components::QtGUI {
  class BasicWordleButtonGrid : public QWidget {
    Q_OBJECT
  private:
    QVector< BasicWordleButtonGroup* > rows_;

  public:
    explicit BasicWordleButtonGrid ( int      button_size  = 50,
                                     int      button_sep   = 10,
                                     int      extra_v_sep  = 5,
                                     int      row_count    = 6,
                                     int      column_count = 5,
                                     QWidget* parent       = nullptr );
    ~BasicWordleButtonGrid ( ) override = default;

  public:
    BasicWordleButtonGroup& operator[] ( int );
  };
}; // namespace Runge::Components::QtGUI

#endif // FINAL_PROJ_BASIC_WORDLE_QT_BUTTON_GRID_HPP_
