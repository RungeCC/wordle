#ifndef FINAL_PROJ_COMMANDS_HPP_
#define FINAL_PROJ_COMMANDS_HPP_

#include "matchit.h"
#include "utilities.h++"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QSet>
#include <QString>
#include <QVector>
#include <concepts>
#include <optional>
#include <string_view>
#include <variant>

namespace Runge::Commands::privateDetails {
  using namespace ::std;

  class Command {
  private:
    QString command_str_;

  public:
    explicit Command ( QString const& command ) : command_str_ ( command ) { }
    ~Command ( ) = default;

  public:
    Runge_Generate_Regular ( Command )

  public:
    [[nodiscard]] QString const& get_command_name ( ) const { return command_str_; }
  };

  using NullableCommand  = optional< Command >;

  inline auto NewGame    = Command ( "new" );
  inline auto PauseGame  = Command ( "pause" );
  inline auto ResumeGame = Command ( "resume" );
  inline auto GetHelp    = Command ( "help" );
  inline auto GetName    = Command ( "name" );
  inline auto QuitGame   = Command ( "quit" );
  inline auto NoCommand  = nullopt;

  class CommandMaker {
  public:
    inline static NullableCommand make_command ( QString& str ) {
      QRegularExpression      command_pattern ( R"(^\.(\w+)\s*\n?$)" );
      QRegularExpressionMatch match = command_pattern.match ( str );
      if ( match.hasMatch ( ) )
        return Command ( QString ( match.captured ( 1 ).toLocal8Bit ( ).data ( ) ) );
      else
        return NoCommand;
    }
  };

  class CommandParser {
  public:
    inline static NullableCommand parse ( QString& str ) {
      QRegularExpression      command_pattern ( R"(^\.(\w+)\s*\n?$)" );
      QRegularExpressionMatch match = command_pattern.match ( str );
      if ( match.hasMatch ( ) )
        return Command ( QString ( match.captured ( 1 ).toLocal8Bit ( ).data ( ) ) );
      else
        return NoCommand;
    }
  };

  class CommandHelper {
  private:
    inline static auto make_opt_qstring_ ( optional< QString > const& some = nullopt ) {
      return [ some ] ( ) { return some; };
    }

  public:
    inline static optional< QString > get_help ( NullableCommand const& cmd ) {
      using namespace ::matchit;
      return match ( cmd ) ( pattern | some ( NewGame )    = make_opt_qstring_ ( "start a new game" ),
                             pattern | some ( QuitGame )   = make_opt_qstring_ ( "quit the game" ),
                             pattern | some ( GetHelp )    = make_opt_qstring_ ( "print help message" ),
                             pattern | some ( GetName )    = make_opt_qstring_ ( "print current game nam" ),
                             pattern | some ( PauseGame )  = make_opt_qstring_ ( "pause the game" ),
                             pattern | some ( ResumeGame ) = make_opt_qstring_ ( "resume the game" ),
                             pattern | some ( _ )          = make_opt_qstring_ ( ),
                             pattern | none                = make_opt_qstring_ ( ) );
    }
  };

}; // namespace Runge::Commands::privateDetails

namespace Runge::Commands {
  using privateDetails::Command;
  using privateDetails::CommandHelper;
  using privateDetails::CommandMaker;
  using privateDetails::CommandParser;
  using privateDetails::NullableCommand;

  using privateDetails::GetHelp;
  using privateDetails::GetName;
  using privateDetails::NewGame;
  using privateDetails::NoCommand;
  using privateDetails::PauseGame;
  using privateDetails::QuitGame;
  using privateDetails::ResumeGame;
}; // namespace Runge::Commands

#endif
