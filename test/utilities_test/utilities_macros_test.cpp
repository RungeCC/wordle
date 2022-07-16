#define CATCH_CONFIG_RUNNER
#include "src/utilities/macros.hpp"
#include "test/test_bases/test_utilities.hpp"

#include <QDebug>
#include <boost/preprocessor.hpp>

#define Runge_debug_Macro_Comparator( a, b ) Runge_debug_To_QString ( a ) == Runge_debug_To_QString ( b )
#define Runge_debug_Macro_Partial_Comparator( a, b )                                                                   \
  Runge_debug_To_QString ( a ) == QString { b }

//  FIXME: 重写宏比较器
//  这里无法通过单元测试的原因是，在不同格式化模式下宏展开的记号列表现不同
//  我们暂时通过定义偏比较器来解决这个问题，也就是，另一者是纯字符串
TEST_CASE ( "test macros" ) {
#undef Runge_debug_Macro_Debug
#define Runge_debug_Macro_Debug 1
  SECTION ( "test to QString utilities" ) {
    INFO ( "test variadic" );
    REQUIRE ( Runge_debug_To_QString ( a, b, c ) == "a, b, c" );
    INFO ( "test single argument" );
    REQUIRE ( Runge_debug_To_QString ( afwsfe ) == "afwsfe" );
  }
  SECTION ( "test macro switch utilities" ) {
#define mapper ( ( 0 ) ( 1 ) ) ( ( 1 ) ( 2 ) ) ( ( 2 ) ( 3 ) )
#define long_mapper                                                                                                    \
  ( ( 0 ) ( 1 ) ) ( ( 1 ) ( 2 ) ) ( ( 2 ) ( 3 ) ) ( ( 3 ) ( 4 ) ) ( ( 4 ) ( 5 ) ) ( ( 5 ) ( 6 ) ) ( ( 6 ) ( 7 ) ) (    \
      ( 7 ) ( 8 ) ) ( ( 8 ) ( 9 ) ) ( ( 9 ) ( 10 ) ) ( ( 10 ) ( 11 ) )
    INFO ( "test macro switch utilities" );
    REQUIRE ( Runge_Macro_Switch ( mapper, 0, 114 ) == 1 );
    REQUIRE ( Runge_Macro_Switch ( mapper, 2, 114 ) == 3 );
    REQUIRE ( Runge_Macro_Switch ( mapper, 5, 114 ) == 114 );
    REQUIRE ( Runge_Macro_Switch ( mapper, 10, 114 ) == 114 );
    INFO ( "test too long mappers" );
    REQUIRE ( Runge_debug_Macro_Comparator ( Runge_Macro_Switch ( long_mapper, 3, 123 ),
                                             Runge_private_Too_Many_Branches_Error_Message ) );
#undef mapper
#undef long_mapper
  }
  SECTION ( "test getters" ) {
    SECTION ( "test access getters" ) {
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Access ( Runge_Access_Public_Mark ), public ) );
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Access ( Runge_Access_Private_Mark ), private ) );
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Access ( Runge_Access_Protected_Mark ), protected ) );
      CHECK (
          Runge_debug_Macro_Comparator ( Runge_Get_Access ( 5 ), Runge_private_No_Such_Access_Mark_Error_Message ) );
    }
    SECTION ( "test method getters" ) {
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Method ( Runge_Method_Default_Mark ), default ) );
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Method ( Runge_Method_Delete_Mark ), delete ) );
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Method ( Runge_Method_Abstract_Mark ), 0 ) );
      CHECK (
          Runge_debug_Macro_Comparator ( Runge_Get_Method ( 5 ), Runge_private_No_Such_Method_Mark_Error_Message ) );
    }
    SECTION ( "test ctor type getters" ) {
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Ctor_Type ( Runge_Ctor_Type_Copy_Mark ) ( myclass ),
                                             myclass const& ) );
      CHECK ( Runge_debug_Macro_Partial_Comparator ( Runge_Get_Ctor_Type ( Runge_Ctor_Type_Move_Mark ) ( myclass ),
                                                     "myclass&&" ) );
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Ctor_Type ( Runge_Ctor_Type_Default_Mark ) ( myclass ), ) );
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Ctor_Type ( 5 ),
                                             Runge_private_No_Such_Ctor_Type_Mark_Error_Message ) );
    }
    SECTION ( "test assignment operator type getters" ) {
      CHECK ( Runge_debug_Macro_Comparator (
          Runge_Get_Assignment_Op_Type ( Runge_Assignment_Op_Type_Copy_Mark ) ( myclass ),
          myclass const& ) );
      CHECK ( Runge_debug_Macro_Partial_Comparator (
          Runge_Get_Assignment_Op_Type ( Runge_Assignment_Op_Type_Move_Mark ) ( myclass ),
          "myclass&&" ) );
      CHECK ( Runge_debug_Macro_Comparator ( Runge_Get_Assignment_Op_Type ( 5 ),
                                             Runge_private_No_Such_Assignment_Op_Type_Mark_Error_Message ) );
    }
  }
  SECTION ( "test ctor generator" ) {
    CHECK ( Runge_debug_Macro_Comparator ( Runge_Generate_Ctor ( myclass,
                                                                 Runge_Ctor_Type_Copy_Mark,
                                                                 Runge_Method_Delete_Mark,
                                                                 constexpr,
                                                                 noexcept,
                                                                 Runge_Access_Public_Mark ),
                                           public
                                           : constexpr myclass ( myclass const& ) noexcept = delete; ) );

    CHECK ( Runge_debug_Macro_Partial_Comparator ( Runge_Generate_Ctor ( myclass,
                                                                         Runge_Ctor_Type_Move_Mark,
                                                                         Runge_Method_Abstract_Mark,
                                                                         explicit inline,
                                                                         ,
                                                                         Runge_Access_Private_Mark ),
                                                   "private : explicit inline myclass ( myclass&& ) = 0;" ) );
  }
  SECTION ( "test dtor generator" ) {
    CHECK ( Runge_debug_Macro_Comparator (
        Runge_Generate_Dtor ( myclass, Runge_Method_Abstract_Mark, virtual, noexcept, Runge_Access_Public_Mark ), public
        : virtual ~myclass ( ) noexcept = 0; ) );
  }
  SECTION ( "test assignment operator generator" ) {
    CHECK ( Runge_debug_Macro_Comparator ( Runge_Generate_Assignment_Op ( myclass,
                                                                          Runge_Assignment_Op_Type_Copy_Mark,
                                                                          Runge_Method_Delete_Mark,
                                                                          constexpr,
                                                                          noexcept,
                                                                          Runge_Access_Public_Mark ),
                                           public
                                           : constexpr myclass & operator= ( myclass const& ) noexcept = delete; ) );

    CHECK ( Runge_debug_Macro_Comparator ( Runge_Generate_Assignment_Op ( myclass,
                                                                          Runge_Assignment_Op_Type_Move_Mark,
                                                                          Runge_Method_Abstract_Mark,
                                                                          explicit inline,
                                                                          ,
                                                                          Runge_Access_Private_Mark ),
                                           private
                                           : explicit inline myclass & operator= ( myclass&& ) = 0; ) );
  }
}

Runge_Catch2_Test_Main_Show_All
