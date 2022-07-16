#include "../../../src/components/basic_wordle_gui_components/basic_wordle_qt_button.hpp"

#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QStyle>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWidget>

int main ( int argc, char** argv ) {
  QApplication app ( argc, argv );
  qInfo ( ) << QStyleFactory::keys ( ) << Qt::endl;
  QApplication::setStyle ( QStyleFactory::create ( "fusion" ) );

  auto win = new QWidget;
  win->setStyle ( QStyleFactory::create ( "fusion" ) );


  auto button = new QPushButton(win);
  auto layout  = new QVBoxLayout;
  layout->addWidget ( button );
  win->setLayout ( layout );

  win->show ( );


  return app.exec ( );
}
