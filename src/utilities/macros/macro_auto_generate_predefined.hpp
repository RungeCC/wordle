#ifndef FINAL_PROJ_MACRO_AUTO_GENERATE_PREDEFINED_HPP_
#define FINAL_PROJ_MACRO_AUTO_GENERATE_PREDEFINED_HPP_

#include "macro_auto_generate.hpp"

#define Runge_Generate_Copy_Ctors( classname, method, prefix, suffix )                                                 \
  Runge_Generate_Ctor ( classname, Runge_Ctor_Type_Copy_Mark, method, prefix, suffix, Runge_Access_Public_Mark )       \
  Runge_Generate_Assignment_Op ( classname,                                                                            \
                                 Runge_Assignment_Op_Type_Copy_Mark,                                                   \
                                 method,                                                                               \
                                 prefix,                                                                               \
                                 suffix,                                                                               \
                                 Runge_Access_Public_Mark )

#define Runge_Generate_Move_Ctors( classname, method, prefix, suffix )                                                 \
  Runge_Generate_Ctor ( classname, Runge_Ctor_Type_Move_Mark, method, prefix, suffix, Runge_Access_Public_Mark )       \
  Runge_Generate_Assignment_Op ( classname,                                                                            \
                                 Runge_Assignment_Op_Type_Move_Mark,                                                   \
                                 method,                                                                               \
                                 prefix,                                                                               \
                                 suffix,                                                                               \
                                 Runge_Access_Public_Mark )

#define Runge_Generate_Default_Ctors( classname, method, prefix, suffix )                                              \
  Runge_Generate_Ctor ( classname, Runge_Ctor_Type_Default_Mark, method, prefix, suffix, Runge_Access_Public_Mark )

#define Runge_Generate_Default_Constructible( classname )                                                              \
  Runge_Generate_Default_Ctors ( classname, Runge_Method_Default_Mark, , )

#define Runge_Generate_Destructible( classname )                                                                       \
  Runge_Generate_Dtor ( classname, Runge_Method_Default_Mark, virtual, , Runge_Access_Public_Mark )

#define Runge_Generate_Copyable( classname )                                                                           \
  Runge_Generate_Copy_Ctors ( classname, Runge_Method_Default_Mark, , )                                                \
  Runge_Generate_Move_Ctors ( classname, Runge_Method_Default_Mark, , noexcept )

#define Runge_Generate_Just_Movable( classname )                                                                       \
  Runge_Generate_Copy_Ctors ( classname, Runge_Method_Delete_Mark, , )                                                 \
  Runge_Generate_Move_Ctors ( classname, Runge_Method_Default_Mark, , noexcept )

#define Runge_Generate_Semi_Regular( classname )                                                                       \
  Runge_Generate_Copyable ( classname )                                                                                \
  Runge_Generate_Default_Constructible ( classname )

#define Runge_Generate_Self_Equality_Operator( classname, method, prefix, suffix )                                     \
  Runge_Generate_Equality_Compare_Op ( classname, classname, method, prefix, suffix )

#define Runge_Generate_Self_Equality_Comparable( classname )                                                           \
  Runge_Generate_Self_Equality_Operator ( classname, Runge_Method_Default_Mark, , )

#define Runge_Generate_Regular( classname )                                                                            \
  Runge_Generate_Semi_Regular ( classname )                                                                            \
  Runge_Generate_Self_Equality_Comparable ( classname )

#define Runge_Generate_Abstract( classname )                                                                           \
  Runge_Generate_Dtor ( classname, Runge_Method_Abstract_Mark, virtual, , Runge_Access_Public_Mark )


#endif
