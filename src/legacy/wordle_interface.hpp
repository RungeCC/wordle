//
// Created by 21104 on 2022/3/30.
//

#ifndef FINAL_PROJ_WORDLE_INTERFACE_HPP_
#define FINAL_PROJ_WORDLE_INTERFACE_HPP_

#include <QString>
#include <QTextStream>
#include <QVector>
#include <type_traits>


namespace Runge {
  class Noncopyable {
  public:
    Noncopyable ( )                    = default;
    Noncopyable ( const Noncopyable& ) = delete;
    Noncopyable& operator= ( const Noncopyable& ) = delete;
  };
};  // namespace Runge

namespace Runge {

  enum class ComparedMark {
    Correct   = 1,
    Misplaced = -1,
    Wrong     = 0,
    Invalid   = 7
  };

  enum class WordleMark { Answer = 0, Guess = 1, Empty = -1 };
  class IWordle : public Noncopyable {
  public:
    virtual QTextStream& operator<< ( QTextStream& ) const = 0;
    virtual QTextStream& operator>> ( QTextStream& )       = 0;

  public:
    virtual WordleMark get_mark ( ) const = 0;
  };

  class IComparedWordle : public Noncopyable {
  public:
    virtual QTextStream& operator<< ( QTextStream& ) const = 0;
    virtual              operator bool ( ) const           = 0;
  };

  class IWordleComparator : public Noncopyable {
  public:
    virtual IComparedWordle
        compare ( const IWordle&, const IWordle& ) const = 0;
  };

  class IWordleGenerator : public Noncopyable {
  public:
    virtual IWordle generate ( ) = 0;
  };


};  // namespace Runge

#endif  // FINAL_PROJ_WORDLE_INTERFACE_HPP
