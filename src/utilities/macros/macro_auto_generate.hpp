#ifndef FINAL_PROJ_MACRO_AUTO_GENERATE_HPP_
#define FINAL_PROJ_MACRO_AUTO_GENERATE_HPP_

#include "macro_switch.hpp"

#define Runge_Access_Public_Mark                        0
#define Runge_Access_Private_Mark                       1
#define Runge_Access_Protected_Mark                     2
#define Runge_private_No_Such_Access_Mark_Error_Message "unknown access specifier!"
// clang-format off
#define Runge_private_Access_Mapper                                                                                    \
  ( ( Runge_Access_Public_Mark ) ( public ) )                                                                          \
  ( ( Runge_Access_Private_Mark ) ( private ) )                                                                        \
  ( ( Runge_Access_Protected_Mark ) ( protected ) )
// clang-format on
#define Runge_Get_Access( value )                                                                                      \
  Runge_Macro_Switch ( Runge_private_Access_Mapper, value, Runge_private_No_Such_Access_Mark_Error_Message )

#define Runge_Method_Default_Mark                       0
#define Runge_Method_Delete_Mark                        1
#define Runge_Method_Abstract_Mark                      2
#define Runge_private_No_Such_Method_Mark_Error_Message "unknown method!"
// clang-format off
#define Runge_private_Method_Mapper                                                                                    \
  ( ( Runge_Method_Default_Mark ) ( default ) )                                                                        \
  ( ( Runge_Method_Delete_Mark ) ( delete ) )                                                                          \
  ( ( Runge_Method_Abstract_Mark ) ( 0 ) )
// clang-format on
#define Runge_Get_Method( value )                                                                                      \
  Runge_Macro_Switch ( Runge_private_Method_Mapper, value, Runge_private_No_Such_Method_Mark_Error_Message )

#define Runge_Ctor_Type_Copy_Mark                                   0
#define Runge_Ctor_Type_Move_Mark                                   1
#define Runge_Ctor_Type_Default_Mark                                2
#define Runge_private_No_Such_Ctor_Type_Mark_Error_Message          "unknown ctor type!"

#define Runge_Assignment_Op_Type_Copy_Mark                          0
#define Runge_Assignment_Op_Type_Move_Mark                          1
#define Runge_private_No_Such_Assignment_Op_Type_Mark_Error_Message "unknown assignment operator type!"

#define Runge_private_Copy_Type_Op( classname )                     classname const&
#define Runge_private_Move_Type_Op( classname )                     classname&&
#define Runge_private_Default_Type_Op( classname )

// clang-format off

#define Runge_private_Ctor_Type_Mapper                                                                                 \
  ( ( Runge_Ctor_Type_Copy_Mark ) ( Runge_private_Copy_Type_Op ) )                                                     \
  ( ( Runge_Ctor_Type_Move_Mark ) ( Runge_private_Move_Type_Op ) )                                                     \
  ( ( Runge_Ctor_Type_Default_Mark ) ( Runge_private_Default_Type_Op ) )

#define Runge_private_Assignment_Op_Type_Mapper                                                                        \
  ( ( Runge_Assignment_Op_Type_Copy_Mark ) ( Runge_private_Copy_Type_Op ) )                                            \
  ( ( Runge_Assignment_Op_Type_Move_Mark ) ( Runge_private_Move_Type_Op ) )
// clang-format on
#define Runge_Get_Ctor_Type( value )                                                                                   \
  Runge_Macro_Switch ( Runge_private_Ctor_Type_Mapper, value, Runge_private_No_Such_Ctor_Type_Mark_Error_Message )

#define Runge_Get_Assignment_Op_Type( value )                                                                          \
  Runge_Macro_Switch ( Runge_private_Assignment_Op_Type_Mapper,                                                        \
                       value,                                                                                          \
                       Runge_private_No_Such_Assignment_Op_Type_Mark_Error_Message )
// clang-format off
#define Runge_Generate_Ctor( classname, type, method, prefix, suffix, access )                                         \
  Runge_Get_Access ( access ) : prefix classname ( Runge_Get_Ctor_Type ( type ) ( classname ) ) suffix                 \
    = Runge_Get_Method ( method );

#define Runge_Generate_Assignment_Op( classname, type, method, prefix, suffix, access )                                \
  Runge_Get_Access ( access ): prefix classname&                                                                       \
    operator= ( Runge_Get_Assignment_Op_Type ( type ) ( classname ) ) suffix                                           \
      = Runge_Get_Method ( method );
// clang-format on
#define Runge_Generate_Dtor( classname, method, prefix, suffix, access )                                               \
  Runge_Get_Access ( access ) : prefix ~classname ( ) suffix = Runge_Get_Method ( method );

#define Runge_Generate_Equality_Compare_Op( classname1, classname2, method, prefix, suffix )                           \
  friend prefix bool operator== ( classname1 const&, classname2 const& ) = Runge_Get_Method ( method );

#endif
