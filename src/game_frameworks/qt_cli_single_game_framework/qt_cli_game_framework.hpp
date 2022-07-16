#ifndef FINAL_PROJ_QT_CLI_GAME_FRAMEWORK_HPP_
#define FINAL_PROJ_QT_CLI_GAME_FRAMEWORK_HPP_

#include "concepts.h++"
#include "tools.h++"
#include "utilities.h++"

#include <QMap>
#include <QTextStream>
#include <functional>
#include <matchit.h>
#include <memory>
#include <tuple>

namespace Runge::GameFrameworks::privateDetails {
  using namespace ::Runge::Concepts;
  using namespace ::Runge::Utilities;
  using namespace ::Runge::Tools;
  using namespace ::std;
  using namespace ::std::literals;
  using namespace ::matchit;

  template < class Game >
  class QtCLISingleGameFramework {
  private:
    unique_ptr< Game > game_ptr_;

  public:
    Runge_Generate_Just_Movable ( QtCLISingleGameFramework );
    Runge_Generate_Destructible ( QtCLISingleGameFramework );

  public:
    explicit QtCLISingleGameFramework ( unique_ptr< Game >&& game_ptr )
      : game_ptr_ ( ::std::move ( game_ptr ) ) {
      Runge_debug_Message ( "Game Framework Initialization", "Calling game framework ctor." );
    }

  private:
    inline std::shared_ptr< typename Game::io_device > get_io_device_ ( ) const { return game_ptr_->get_io_device ( ); }

  private:
    inline void deal_unknown_command_ ( tuple< GameStateMark, NullableCommand > const& value ) {
      auto str = get< NullableCommand > ( value ).value ( ).get_command_name ( ).data ( );
      get_io_device_ ( )->get_out_stream ( ) << QString ( "command named \"%1\" is unknown" ).arg ( str ) << Qt::endl;
    }

    inline void new_game_ ( tuple< GameStateMark, NullableCommand > const& ) { this->game_ptr_->new_game ( ); }

    inline void pause_game_ ( tuple< GameStateMark, NullableCommand > const& value ) {
      if ( get< GameStateMark > ( value ).is_running ( ) ) this->game_ptr_->pause_game ( );
    }

    inline void resume_game_ ( tuple< GameStateMark, NullableCommand > const& value ) {
      if ( get< GameStateMark > ( value ).is_paused ( ) ) this->game_ptr_->resume_game ( );
    }

    [[noreturn]] inline void quit_game_ ( tuple< GameStateMark, NullableCommand > const& ) {
      get_io_device_ ( )->get_out_stream ( ) << "Ok, I'll quit. Have a nice day!" << Qt::endl;
      exit ( 0 );
    }

    inline void get_help_ ( tuple< GameStateMark, NullableCommand > const& ) {
      get_io_device_ ( )->get_out_stream ( ) << "command help: \n"
                                             << ".help\n.new\n.quit\n.pause\n.resume\n.name" << Qt::endl;
      get_io_device_ ( )->get_out_stream ( ) << "game help:" << this->game_ptr_->get_help ( ) << Qt::endl;
    }

    inline void deal_no_command_ ( tuple< GameStateMark, NullableCommand > const& value ) { }

    inline void get_name_ ( tuple< GameStateMark, NullableCommand > const& ) {
      get_io_device_ ( )->get_out_stream ( ) << this->game_ptr_->get_name ( ) << Qt::endl;
    }

  public:
#pragma clang diagnostic push
#pragma ide diagnostic   ignored "bugprone-macro-parentheses"
    [[noreturn]] void start ( ) {
        [[maybe_unused]] auto& out = this->get_io_device_ ( )->get_out_stream ( );
        [[maybe_unused]] auto& in  = this->get_io_device_ ( )->get_in_stream ( );
        out << "Hello, welcome to play the wordle game, current game is: " + game_ptr_->get_name ( ) << Qt::endl;
        out << "key in .help to show help messages." << Qt::endl;
        this->game_ptr_->new_game ( );
        Runge_debug_Message ( "Game Framework Running", "Enter main loop." );
        while ( true ) {
          auto res = game_ptr_->next_turn ( );
#ifdef Runge_Debug
        auto cmd = get< NullableCommand > ( res );
        if ( cmd.has_value ( ) ) {
          Runge_debug_Message ( "Game Framework Running",
                                QString ( "Receive command: " ) + cmd.value ( ).get_command_name ( ) );
        } else {
          Runge_debug_Message ( "Runge Framework Running", "No command." );
        }
#endif
        /**
         *  构建成员函数调用
         */
#define Runge_private_Member_Function_Call( name, res )                                                                \
  [ this, &res ] {                                                                                                     \
    Runge_debug_Message ( "Game Framework Running", "Call function " + QString { Runge_debug_To_QString ( name ) } );  \
    this->name ( res );                                                                                                \
    return;                                                                                                            \
  }
        match ( get< NullableCommand > ( res ) ) (
            pattern | some ( NewGame )    = Runge_private_Member_Function_Call ( new_game_, res ),
            pattern | some ( QuitGame )   = Runge_private_Member_Function_Call ( quit_game_, res ),
            pattern | some ( GetHelp )    = Runge_private_Member_Function_Call ( get_help_, res ),
            pattern | some ( GetName )    = Runge_private_Member_Function_Call ( get_name_, res ),
            pattern | some ( PauseGame )  = Runge_private_Member_Function_Call ( pause_game_, res ),
            pattern | some ( ResumeGame ) = Runge_private_Member_Function_Call ( resume_game_, res ),
            pattern | some ( _ )          = Runge_private_Member_Function_Call ( deal_unknown_command_, res ),
            pattern | none                = Runge_private_Member_Function_Call ( deal_no_command_, res ) );
#undef Runge_private_Member_Function_Call
      }
      Runge_debug_Message ( "Game Framework Running", "Leave main loop." );
    }
#pragma clang diagnostic pop
  };
}; // namespace Runge::GameFrameworks::privateDetails

namespace Runge::GameFrameworks {
  using privateDetails::QtCLISingleGameFramework;
}; // namespace Runge::GameFrameworks

#endif