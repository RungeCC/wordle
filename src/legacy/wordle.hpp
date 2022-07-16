#ifndef FINAL_PROJ_WORDLE_HPP_
#define FINAL_PROJ_WORDLE_HPP_


// Qt lib
#include <QDebug>
#include <QString>
#include <QVector>
#include <functional>
#include <type_traits>



namespace Runge {

  class Noncopyable {
  public:
    Noncopyable ( ) = default;

    Noncopyable ( const Noncopyable& ) = delete;

    Noncopyable& operator= ( const Noncopyable& ) = delete;
  };

  class Game : public Noncopyable {
  public:  // ctors
    Game ( ) = default;

  public:  // dtor
    ~Game ( ) = default;

  public:
    void init ( );
    void start ( );

  public:  // getter
    [[nodiscard]] constexpr bool is_init ( ) const noexcept {
      return inited_;
    }

  private:
    void load_wordle_words ( const QString& filename );

    void basic_wordle ( );

  private:
    QVector< QString > wordle_data_;
    bool               inited_ = false;
  };

  enum class GuessState {
    Correct   = 1,
    Misplaced = -1,
    Wrong     = 0,
    Invalid   = 7
  };

  enum class WordleState { Answer = 0, Guess = 1, Empty = -1 };


};  // namespace Runge


#endif  // end of FINAL_PROJ_WORDLE_HPP_