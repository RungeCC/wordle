#ifndef FINAL_PROJ_BAD_RESOURCE_EXCEPTIONS_HPP_
#define FINAL_PROJ_BAD_RESOURCE_EXCEPTIONS_HPP_

#include "base_exceptions.hpp"
#include "src/utilities/macros.hpp"

namespace Runge::Exceptions::BadResourceExceptions::privateDetails {
  class BadResourceExceptions : public ::Runge::Exceptions::baseExceptions::Throwable {
  public:
    Runge_Generate_Regular ( BadResourceExceptions )
    Runge_Generate_Destructible ( BadResourceExceptions )
  };
}; // namespace Runge::Exceptions::BadResourceExceptions::privateDetails

#endif
