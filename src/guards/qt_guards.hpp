#ifndef FINAL_PROJ_QT_GUARDS_HPP_
#define FINAL_PROJ_QT_GUARDS_HPP_

#include "../includes/tools.h++"
#include "../includes/utilities.h++"
#include "qobj_concepts/qobj_concepts.hpp"

#include <QMetaObject>

namespace Runge::QtGuards::privateDetails {
  class HasSignalGuard {
    static inline void check ( QObject* obj, QString signature ) { }
  };
}; // namespace Runge::QtGuards::privateDetails

#endif
