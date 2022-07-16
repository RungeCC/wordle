#ifndef FINAL_PROJ_BASE_EXCEPTION_HPP_
#define FINAL_PROJ_BASE_EXCEPTION_HPP_

#include "../includes/utilities.h++"

#include <QDebug>
#include <QMetaMethod>
#include <QString>
#include <boost/stacktrace.hpp>
#include <stdexcept>
#include <string>

namespace Runge::Exceptions::baseExceptions {
  using namespace ::std;


  class Throwable : std::exception {
  private:
    char const* what_ = "";

  public:
    Runge_Generate_Copyable ( Throwable );
    Runge_Generate_Destructible ( Throwable );

  public:
    explicit Throwable ( QString const& message ) { what_ = message.toLocal8Bit ( ).data ( ); }

  public:
    [[noreturn]] virtual void raise ( ) const final { throw *this; }

  public:
    [[nodiscard]] virtual char const* what ( ) const noexcept override final { return what_; }
  };

};  //  namespace Runge::Exceptions::baseExceptions

#endif
