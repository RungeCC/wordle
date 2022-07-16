#ifndef FINAL_PROJ_QT_GUI_INTERFACE_HPP_
#define FINAL_PROJ_QT_GUI_INTERFACE_HPP_

#include "./wordle_interfaces.hpp"

#include <QGroupBox>
#include <QKeyEvent>
#include <QObject>
#include <QPushButton>
#include <QToolButton>
#include <QVector>
#include <QWidget>
#include <memory>

namespace Runge::QtGUIInterface::privateDetails {
  class IGameWidget : public QWidget {
  public:
    virtual QString get_help ( ) const   = 0;
    virtual QString get_name ( ) const   = 0;
    virtual void    new_game ( )         = 0;
    virtual void    pause_game ( )       = 0;
    virtual void    resume_game ( )      = 0;
    virtual QString get_answer ( ) const = 0;
    virtual ~IGameWidget ( )             = default;
  };
}; // namespace Runge::QtGUIInterface::privateDetails

namespace Runge::QtGUIInterface {
  using ::Runge::QtGUIInterface::privateDetails::IGameWidget;
}; // namespace Runge::QtGUIInterface

#endif // QT_GUI_INTERFACE_HPP
