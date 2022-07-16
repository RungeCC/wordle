//
// Created by runge on 22-6-30.
//

#include "basic_wordle_qt_button_grid.hpp"

namespace Runge::Components::QtGUI {

  BasicWordleButtonGrid::BasicWordleButtonGrid ( int      button_size,
                                                 int      button_sep,
                                                 int      extra_v_sep,
                                                 int      row_count,
                                                 int      column_count,
                                                 QWidget* parent )
    : QWidget ( parent ) {
    auto layout_ = new QVBoxLayout ( this );
    layout_->setAlignment ( Qt::AlignHCenter | Qt::AlignTop );
    for ( int i = 0; i < row_count; i++ ) {
      auto row = new BasicWordleButtonGroup ( button_size, button_sep, column_count, this );
      rows_.push_back ( row );
      layout_->addWidget ( row );
    }
    layout_->addSpacing ( extra_v_sep );
    this->setLayout ( layout_ );
    this->setMinimumHeight ( row_count * ( button_size + button_sep + extra_v_sep ) );
    this->setMinimumWidth ( column_count * ( button_size ) + ( column_count + 2 ) * button_sep );
  }
  BasicWordleButtonGroup& BasicWordleButtonGrid::operator[] ( int num ) { return *(rows_ [ num ]); }


}; // namespace Runge::Components::QtGUI