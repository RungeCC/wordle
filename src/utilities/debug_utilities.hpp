//
// Created by runge on 22-6-28.
//

#ifndef FINAL_PROJ_DEBUG_UTILITIES_HPP_
#define FINAL_PROJ_DEBUG_UTILITIES_HPP_

#include <QDebug>
#include <boost/preprocessor.hpp>

#ifndef Runge_Debug_Using_Pretty
#  define Runge_Debug_Using_Pretty 0
#endif

#ifdef Runge_Debug
#  define Runge_debug_Func( )  BOOST_PP_IF ( Runge_Debug_Using_Pretty, __PRETTY_FUNCTION__, __func__ )

#  define Runge_debug_Where( ) QString ( "%1:%2:%3" ).arg ( __FILE__ ).arg ( __LINE__ ).arg ( Runge_debug_Func ( ) )
#  define Runge_debug_Message( stage, msg )                                                                            \
    qDebug ( ) << "? In:" << Runge_debug_Where ( ) << Qt::flush;                                                       \
    qDebug ( ) << "?   Stage:" << ( stage ) << Qt::flush;                                                              \
    qDebug ( ) << "?   Debug:" << ( msg ) << Qt::flush;
#else
#  define Runge_debug_Message( ... )
#endif

#endif // FINAL_PROJ_DEBUG_UTILITIES_HPP_
