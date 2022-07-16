#ifndef FINAL_PROJ_MACRO_UTILITIES_HPP_
#define FINAL_PROJ_MACRO_UTILITIES_HPP_

#include <QDebug>
#include <boost/preprocessor.hpp>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"
#define Runge_debug_To_QString( var... )   QString ( BOOST_PP_STRINGIZE_I ( var ) )
#define Runge_debug_To_StdString( var... ) std::string ( BOOST_PP_STRINGIZE_I ( var ) )

#define Runge_debug_Show_Macro( var... )   qDebug ( ) << Runge_debug_To_QString ( var ) << Qt::flush;

#define Runge_debug_Macro_Debug            0
#define Runge_Error_Msg( msg )             BOOST_PP_IF ( Runge_debug_Macro_Debug, msg, BOOST_PP_ASSERT_MSG ( 0, msg ) )
#pragma GCC diagnostic pop
#endif
