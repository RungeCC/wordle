//
// Created by runge on 22-6-30.
//

#include "basic_wordle_qt_button_group.hpp"

#include <QAnimationGroup>
#include <QPoint>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

namespace Runge::Components::QtGUI {

  BasicWordleButtonGroup::BasicWordleButtonGroup ( int grid_size, int sep_size, int count, QWidget* parent )
    : QGroupBox { parent } {
    auto layout = new QHBoxLayout { this };
    for ( int i = 0; i < count; ++i ) {
      auto button = new BasicWordleButton { grid_size, this };
      button->set_text ( ' ' );
      line_buttons_.push_back ( button );
      layout->addWidget ( button );
    }
    this->setLayout ( layout );
    this->setMaximumHeight ( grid_size + 2 * sep_size );
    this->setMinimumHeight ( grid_size + 2 * sep_size );
    this->setMaximumWidth ( count * grid_size + ( count + 1 ) * sep_size );
    this->setMinimumWidth ( count * grid_size + ( count + 1 ) * sep_size );
  }
  void BasicWordleButtonGroup::shake ( int amplitude, int duration, int loop ) {
    auto  group               = this;
    auto  start_pos           = group->pos ( );
    auto  right_pos           = start_pos + QPoint ( 5, 0 );
    auto  left_pos            = start_pos - QPoint ( 5, 0 );
    auto* anime_mid_to_right  = new QPropertyAnimation ( group, "pos" );
    auto* anime_right_to_left = new QPropertyAnimation ( group, "pos" );
    auto* anime_left_to_mid   = new QPropertyAnimation ( group, "pos" );
    anime_mid_to_right->setDuration ( duration );
    anime_mid_to_right->setStartValue ( start_pos );
    anime_mid_to_right->setEndValue ( right_pos );
    anime_mid_to_right->setEasingCurve ( QEasingCurve::InOutCubic );

    anime_right_to_left->setDuration ( 2 * duration );
    anime_right_to_left->setStartValue ( right_pos );
    anime_right_to_left->setEndValue ( left_pos );
    anime_right_to_left->setEasingCurve ( QEasingCurve::InOutCubic );

    anime_left_to_mid->setDuration ( duration );
    anime_left_to_mid->setStartValue ( left_pos );
    anime_left_to_mid->setEndValue ( start_pos );
    anime_left_to_mid->setEasingCurve ( QEasingCurve::InOutCubic );

    auto anime_grp = new QSequentialAnimationGroup;
    anime_grp->addAnimation ( anime_mid_to_right );
    anime_grp->addAnimation ( anime_right_to_left );
    anime_grp->addAnimation ( anime_left_to_mid );

    anime_grp->setLoopCount ( 2 );
    anime_grp->start ( );
  }
  BasicWordleButton& BasicWordleButtonGroup::operator[] ( int num ) { return *( line_buttons_ [ num ] ); }

}; // namespace Runge::Components::QtGUI