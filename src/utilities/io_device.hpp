#ifndef FINAL_PROJ_IO_DEVICE_HPP_
#define FINAL_PROJ_IO_DEVICE_HPP_

#include "debug_utilities.hpp"
#include "macros.hpp"

#include <QString>
#include <QTextStream>
#include <memory>

namespace Runge::IODevice {
  class QtCLIDevice {
  public:
    using input_pipeline  = QTextStream;
    using output_pipeline = QTextStream;
    using string_type     = QString;

  public:
    QtCLIDevice ( std::unique_ptr< QTextStream >&& in, std::unique_ptr< QTextStream >&& out )
      : in_ ( ::std::move ( in ) )
      , out_ ( ::std::move ( out ) ) {
      Runge_debug_Message ( "IO Device Initialization", "Call Qt CLI IO device ctor." );
    }

    QtCLIDevice ( ) {
      in_  = std::make_unique< QTextStream > ( stdin );
      out_ = std::make_unique< QTextStream > ( stdout );
    }

  public:
    Runge_Generate_Just_Movable ( QtCLIDevice )

  public:
    [[nodiscard]] QTextStream& get_in_stream ( ) const { return *in_; }

    [[nodiscard]] QTextStream& get_out_stream ( ) const { return *out_; }

  private:
    std::unique_ptr< QTextStream > in_;
    std::unique_ptr< QTextStream > out_;
  };
}; // namespace Runge::IODevice


#endif