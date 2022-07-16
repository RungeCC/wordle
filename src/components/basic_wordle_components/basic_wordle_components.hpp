#ifndef FINAL_PROJ_BASIC_WORDLE_COMPONENTS_HPP_
#define FINAL_PROJ_BASIC_WORDLE_COMPONENTS_HPP_

#include "tools.h++"
#include "utilities.h++"

#include <QFile>
#include <QMap>
#include <QSet>
#include <QString>
#include <QTextStream>
#include <QVector>
#include <memory>
#include <random>
#include <type_traits>
#include <utility>

namespace Runge::Components::BasicWordle {
  class BasicWordle {
  public:
    Runge_Generate_Regular ( BasicWordle )

  public:
    // 从底层数据构造的构造函数
    explicit BasicWordle ( QString const& data )
      : data_ { data } { }

  public:
    [[nodiscard]] QString const& data ( ) const noexcept { return data_; }

  private:
    QString data_;
  };

  class BasicComparedWordle {
  public:
    using wordle        = BasicWordle;
    using compared_mark = ::Runge::Tools::ComparedMark;

  public:
    Runge_Generate_Regular ( BasicComparedWordle )
    BasicComparedWordle ( QString const&, QVector< Tools::ComparedMark >& );

  private:
    QVector< Tools::ComparedMark > code_;
    QString                        data_;

  public:
    [[nodiscard]]      operator bool ( ) const noexcept;
    [[nodiscard]] bool is_correct ( ) const noexcept;

  public:
    [[nodiscard]] QVector< Tools::ComparedMark > const& code ( ) const noexcept { return code_; }
    [[nodiscard]] QString const&                        data ( ) const noexcept { return data_; }
  };

  class BasicWordleComparator {
  public:
    using wordle          = BasicWordle;
    using compared_wordle = BasicComparedWordle;

  public:
    Runge_Generate_Abstract ( BasicWordleComparator )

  public:
    static BasicComparedWordle compare ( BasicWordle const&, BasicWordle const& );
  };

  class BasicWordleResourceHolder {
  public:
    using wordle = BasicWordle;

  public:
    Runge_Generate_Just_Movable ( BasicWordleResourceHolder )

  public:
    explicit BasicWordleResourceHolder ( QFile& file );

  public:
    [[nodiscard]] QVector< BasicWordle > const& data ( ) const noexcept { return wordles_; }
    [[nodiscard]] qsizetype                     size ( ) const noexcept { return wordles_.size ( ); }

  private:
    QVector< BasicWordle > wordles_;
  };

  using BasicWordleGenerator = Generators::BasicRandomGenerator< BasicWordleResourceHolder >;

  class BasicWordleFormatter {
  public:
    using wordle          = BasicWordle;
    using compared_wordle = BasicComparedWordle;
    using io_device       = ::Runge::Utilities::QtCLIDevice;

  public:
    Runge_Generate_Abstract ( BasicWordleFormatter )

  public:
    static QTextStream& print ( QTextStream&, BasicWordle const& );
    static QTextStream& print ( QTextStream&, BasicComparedWordle const& );
  };

  enum class BasicWordleParserError {
    InvalidWordle
  };

  class BasicWordleParser {
  public:
    using wordle          = BasicWordle;
    using io_device       = ::Runge::Utilities::QtCLIDevice;
    using resource_holder = BasicWordleResourceHolder;
    using error           = BasicWordleParserError;
    using result          = Utilities::Result< BasicWordle, BasicWordleParserError >;

  private:
    std::shared_ptr< BasicWordleResourceHolder > res_ptr_;

  public:
    Runge_Generate_Just_Movable ( BasicWordleParser )
    explicit BasicWordleParser ( std::shared_ptr< BasicWordleResourceHolder > );

  public:
    Utilities::Result< BasicWordle, BasicWordleParserError > parse ( QString const& );
  };
}; // namespace Runge::Components::BasicWordle


#endif // FINAL_PROJ_BASIC_WORDLE_HPP_
