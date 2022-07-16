#ifndef FINAL_PROJ_MARKS_HPP_
#define FINAL_PROJ_MARKS_HPP_

#include "matchit.h"
#include "utilities.h++"

#include <QString>
#include <optional>
#include <string_view>
#include <type_traits>
#include <variant>

namespace Runge::Marks::privateDetails {
  using namespace ::std;
  using namespace ::Runge::Utilities;

  struct PausedType { };
  struct RunningType { };
  enum struct GameOverState {
    Win,
    Lose
  };
  struct GameOverType {
    GameOverState value;
    constexpr explicit GameOverType ( GameOverState value_ )
      : value ( value_ ) { }
    friend constexpr bool operator== ( GameOverType const& a, GameOverType const& b ) { return a.value == b.value; }
  };

  inline constexpr PausedType   Paused_ { };
  inline constexpr RunningType  Running_ { };
  inline constexpr GameOverType Win_ { GameOverState::Win };
  inline constexpr GameOverType Lose_ { GameOverState::Lose };

  class GameStateMark {
  public:
    using type = variant< RunningType, PausedType, GameOverType >;

  private:
    variant< RunningType, PausedType, GameOverType > value_;

  public:
    constexpr explicit GameStateMark ( variant< RunningType, PausedType, GameOverType > value )
      : value_ ( value ) { }
    constexpr ~GameStateMark ( ) = default;

  public:
    Runge_Generate_Regular ( GameStateMark )

  public:
    [[maybe_unused]] [[nodiscard]] constexpr variant< RunningType, PausedType, GameOverType > get_value ( ) const { return value_; }
    [[maybe_unused]] constexpr explicit operator variant< RunningType, PausedType, GameOverType > ( ) const {
      return value_;
    }
    template < class T >
    [[maybe_unused]] [[nodiscard]] constexpr bool is_type ( ) const {
      return nullptr != get_if< decay_t< T > > ( &value_ );
    }
    template < class T >
    [[maybe_unused]] constexpr optional< T > get_opt ( ) const {
      if constexpr ( is_type< T > ( ) ) {
        return get< T > ( value_ );
      } else {
        return nullopt;
      }
    }
    [[maybe_unused]] constexpr bool is_running ( ) const { return is_type< RunningType > ( ); }
    [[maybe_unused]] constexpr bool is_paused ( ) const { return is_type< PausedType > ( ); }
    [[maybe_unused]] constexpr bool is_game_over ( ) const { return is_type< GameOverType > ( ); }
    [[maybe_unused]] constexpr bool is_win ( ) const {
      return is_game_over ( ) && get< GameOverType > ( value_ ) == Win_;
    }
    [[maybe_unused]] constexpr bool is_lose ( ) const {
      return is_game_over ( ) && get< GameOverType > ( value_ ) == Lose_;
    }
  };

  inline constexpr auto Running = GameStateMark ( Running_ );
  inline constexpr auto Paused  = GameStateMark ( Paused_ );
  inline constexpr auto Win     = GameStateMark ( Win_ );
  inline constexpr auto Lose    = GameStateMark ( Lose_ );

  template < GameOverState st >
  constexpr auto state = matchit::app ( &GameOverType::value, st );

  enum class ComparedMark {
    Correct   = 1,
    Misplaced = -1,
    Wrong     = 0,
    Invalid   = 7,
    Empty     = 10
  };

  // TODO: 更加一般的色彩设定
  template < Color Correct, Color Wrong, Color Misplaced, Color Foreground >
  struct ColorScheme {
    static constexpr Color correct    = Correct;
    static constexpr Color wrong      = Wrong;
    static constexpr Color misplaced  = Misplaced;
    static constexpr Color foreground = Foreground;
  };
  // TODO: 定义 PaddingScheme 和对应的概念

  using DefaultColorScheme = ColorScheme< Color::Green, Color::BrightBlack, Color::Yellow, Color::BrightWhite >;

  template < class Scheme >
  struct ColorChooser {
    static Color choose ( ComparedMark const& mark ) {
      switch ( mark ) {
        case ComparedMark::Correct: return Scheme::correct;
        case ComparedMark::Misplaced: return Scheme::misplaced;
        case ComparedMark::Wrong: return Scheme::wrong;
        case ComparedMark::Invalid: return Scheme::foreground;
        case ComparedMark::Empty: return Scheme::foreground;
        default: return Scheme::foreground;
      }
    }
  };

  using DefaultColorChooser = ColorChooser< DefaultColorScheme >;
}; // namespace Runge::Marks::privateDetails

namespace Runge::Marks {
  using privateDetails::ColorScheme;
  using privateDetails::ComparedMark;
  using privateDetails::DefaultColorScheme;
  using privateDetails::GameOverState;
  using privateDetails::GameOverType;
  using privateDetails::GameStateMark;
  using privateDetails::Lose;
  using privateDetails::Paused;
  using privateDetails::PausedType;
  using privateDetails::Running;
  using privateDetails::RunningType;
  using privateDetails::state;
  using privateDetails::Win;
  using privateDetails::ColorChooser;
  using privateDetails::DefaultColorChooser;
}; // namespace Runge::Marks


#endif // FINAL_PROJ_MARKS_HPP_
