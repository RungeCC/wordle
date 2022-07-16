#ifndef FINAL_PROJ_QOBJ_CONCEPTS_HPP_
#define FINAL_PROJ_QOBJ_CONCEPTS_HPP_

#include <QMap>
#include <QMetaMethod>
#include <QMetaObject>
#include <QObject>
#include <QString>
#include <optional>
#include <type_traits>

namespace Runge::QObjectConcepts::privateDetails {
  using namespace ::std;

  class QObjectMethodInvokable {
  public:
    static bool check ( QObject const*                      obj,
                        const QString&                      signature,
                        optional< QMetaMethod::MethodType > mtd_type    = nullopt,
                        optional< QString >                 ret_type    = nullopt,
                        bool                                check_const = false ) {
      auto meta  = obj->metaObject ( );
      auto index = meta->indexOfMethod ( QMetaObject::normalizedSignature ( signature.toLocal8Bit ( ).data ( ) ) );
      if ( index == -1 ) return false;
      auto mtd = meta->method ( index );
      if ( ! mtd.isValid ( ) ) return false;
      if ( check_const && ! mtd.isConst ( ) ) return false;
      if ( mtd_type.has_value ( ) && mtd_type.value ( ) != mtd.methodType ( ) ) { return false; }
      if ( ret_type.has_value ( )
           && QMetaObject::normalizedType ( ret_type.value ( ).toLocal8Bit ( ).data ( ) )
                  != QString ( mtd.typeName ( ) ) ) {
        return false;
      }
      return true;
    }
  };
}; // namespace Runge::QObjectConcepts::privateDetails

namespace Runge::QObjectConcepts {
  using privateDetails::QObjectMethodInvokable;
}; // namespace Runge::QObjectConcepts

#endif
