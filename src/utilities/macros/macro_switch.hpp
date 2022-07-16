#ifndef FINAL_PROJ_MACRO_SWITCH_HPP_
#define FINAL_PROJ_MACRO_SWITCH_HPP_

#include "macro_utilities.hpp"
#include <boost/preprocessor.hpp>

#define Runge_private_Pair_First(pair) BOOST_PP_SEQ_ELEM(0, pair)
#define Runge_private_Pair_Second(pair) BOOST_PP_SEQ_ELEM(1, pair)

#define Runge_private_Switch_Op_0(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(0, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_1(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(1, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_2(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(2, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_3(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(3, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_4(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(4, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_5(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(5, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_6(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(6, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_7(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(7, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_8(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(8, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))
#define Runge_private_Switch_Op_9(s, state, x)                                 \
  BOOST_PP_REMOVE_PARENS(                                                      \
      BOOST_PP_IF(BOOST_PP_EQUAL(9, Runge_private_Pair_First(x)),              \
                  Runge_private_Pair_Second(x), state))

#define Runge_private_Max_Switch_Branches 10

#define Runge_private_Too_Many_Branches_Error_Message                          \
  "too many switch branches!"

#define Runge_private_Make_Switch_Op(value)                                    \
  BOOST_PP_CAT(Runge_private_Switch_Op_, value)

#define Runge_Macro_Switch(map, target, failed_msg)                            \
  BOOST_PP_IF(                                                                 \
      BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(map),                                 \
                       Runge_private_Max_Switch_Branches),                     \
      Runge_Error_Msg(Runge_private_Too_Many_Branches_Error_Message),          \
      BOOST_PP_IF(BOOST_PP_GREATER_EQUAL(target, BOOST_PP_SEQ_SIZE(map)),      \
                  Runge_Error_Msg(failed_msg),                                 \
                  BOOST_PP_SEQ_FOLD_LEFT(Runge_private_Make_Switch_Op(target), \
                                         Runge_Error_Msg(failed_msg), map)))

#endif
