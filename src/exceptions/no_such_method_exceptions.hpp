#ifndef FINAL_PROJ_NO_SUCH_METHOD_EXCEPTIONS_HPP_
#define FINAL_PROJ_NO_SUCH_METHOD_EXCEPTIONS_HPP_

#include "base_exceptions.hpp"

namespace Runge::Exceptions::NoSuchMethodExceptions::privateDetails {
  class NoSuchMethodException : public ::Runge::Exceptions::baseExceptions::Throwable {
  private:
    static QString method_type_helper_ ( QMetaMethod::MethodType type ) {
      QString meta_temp   = "class type %2 do not have such %1 with "
                            "signature %3 or which is not accessible.";
      QString ctor_temp   = meta_temp.arg ( "constructor" );
      QString signal_temp = "class type %1 do not have such signal with signature %2.";
      QString slot_temp   = meta_temp.arg ( "slot" );
      QString method_temp = meta_temp.arg ( "method" );
      switch ( type ) {
        case QMetaMethod::MethodType::Method: return method_temp; break;
        case QMetaMethod::MethodType::Slot: return slot_temp; break;
        case QMetaMethod::MethodType::Signal: return signal_temp; break;
        case QMetaMethod::MethodType::Constructor: return ctor_temp; break;
        default: break;
      }
    }
    static QString message_helper_ ( QString const&                 class_name,
                                     QString const&                 method_signature,
                                     QMetaMethod::MethodType const& method_type,
                                     QString const&                 note ) {
      return method_type_helper_ ( method_type ).arg ( class_name ).arg ( method_signature ) + "\nNote: " + note;
    }

  public:
    Runge_Generate_Regular ( NoSuchMethodException )
    Runge_Generate_Destructible ( NoSuchMethodException )

  public:
    NoSuchMethodException ( QString const&                 class_name,
                            QString const&                 method_signature,
                            QMetaMethod::MethodType const& method_type,
                            QString const&                 note )
      : Exceptions::baseExceptions::Throwable { message_helper_ ( class_name, method_signature, method_type, note ) } {
    }
  };

#define Get_No_Such_Type_Method_Exception_Name( type ) NoSuch##type##Exception

#define Generate_No_Such_type_Method_Exception( type, val )                                                            \
  class Get_No_Such_Type_Method_Exception_Name ( type ) : public NoSuchMethodException {                               \
  public:                                                                                                              \
    Runge_Generate_Regular ( Get_No_Such_Type_Method_Exception_Name ( type ) );                                        \
    Runge_Generate_Destructible ( Get_No_Such_Type_Method_Exception_Name ( type ) );                                   \
                                                                                                                       \
  public:                                                                                                              \
    Get_No_Such_Type_Method_Exception_Name (                                                                           \
        type ) ( QString const& class_name, QString const& method_signature, QString const& note )                     \
      : NoSuchMethodException { class_name, method_signature, val, note } { }                                          \
  }

  Generate_No_Such_type_Method_Exception ( NormalMethod, QMetaMethod::MethodType::Method )
  Generate_No_Such_type_Method_Exception ( Signal, QMetaMethod::MethodType::Signal )
  Generate_No_Such_type_Method_Exception ( Slot, QMetaMethod::MethodType::Slot )
  Generate_No_Such_type_Method_Exception ( Ctor, QMetaMethod::MethodType::Constructor )

#undef Generate_No_Such_type_Method_Exception
#undef Get_No_Such_Type_Method_Exception_Name
};  //  namespace Runge::Exceptions::NoSuchMethodExceptions::privateDetails

namespace Runge::Exceptions::NoSuchMethodExceptions {
  using privateDetails::NoSuchCtorException;
  using privateDetails::NoSuchNormalMethodException;
  using privateDetails::NoSuchSignalException;
  using privateDetails::NoSuchSlotException;
};  //  namespace Runge::Exceptions::NoSuchMethodExceptions

#endif  //  NO_SUCH_METHOD_EXCEPTIONS_HPP
