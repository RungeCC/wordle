#ifndef FINAL_PROJ_RESULT_TYPE_HPP_
#define FINAL_PROJ_RESULT_TYPE_HPP_

#include "macros.hpp"

#include <QString>
#include <optional>
#include <stdexcept>
#include <variant>

namespace Runge::TypeUtilities {

  class UnhandledErrorResult : public std::exception {
  private:
    char const* what_;

  public:
    Runge_Generate_Copyable ( UnhandledErrorResult )

  public:
    explicit UnhandledErrorResult ( QString const& note = "" ) {
      what_ = ( QString ( "It's an error type result, you must handle it.\n" ) + note ).toLocal8Bit ( ).data ( );
    }

  public:
    [[nodiscard]] char const* what ( ) const noexcept override { return what_; }
  };

  template < class OK, class Error >
  class Result {
  public:
    using ok    = OK;
    using error = Error;

  private:
    std::variant< std::monostate, OK, Error > value_;

  public:
    Result ( OK const& value ) : value_ ( value ) { }
    Result ( Error const& err ) : value_ ( err ) { }

  public:
    Runge_Generate_Copyable ( Result )

  public:
    [[nodiscard]] bool     is_ok ( ) const noexcept { return std::get_if< OK > ( &value_ ) != nullptr; }
    [[nodiscard]] bool     is_error ( ) const noexcept { return std::get_if< Error > ( &value_ ) != nullptr; }
    [[nodiscard]] explicit operator bool ( ) const noexcept { return this->is_ok ( ); }

  public:
    OK value ( ) {
      if ( is_ok ( ) )
        return std::get< OK > ( value_ );
      else
        throw UnhandledErrorResult { };
    }

    OK value_or ( OK val ) {
      if ( is_ok ( ) )
        return value ( );
      else
        return val;
    }

    std::optional< Error > err ( ) {
      if ( is_error ( ) )
        return std::get< Error > ( value_ );
      else
        return std::nullopt;
    }
  };
}; // namespace Runge::TypeUtilities

#endif // FINAL_PROJ_RESULT_TYPE_HPP_
