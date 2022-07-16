#ifndef FINAL_PROJ_STRINGIZER_HPP_
#define FINAL_PROJ_STRINGIZER_HPP_
#include "debug_utilities.hpp"

#include <QString>
#include <QTextStream>
#include <concepts>
#include <type_traits>

namespace Runge::StringUtilities::privateDetails {
  using namespace ::std;

  template < class T >
  concept is_qstring = same_as< T, QString >;

  template < class T >
  concept qstring_convertible = convertible_to< T, QString >;

  template < class T >
  concept to_string_callable = requires ( T const& val ) {
                                 { val.to_string ( ) } -> same_as< QString >;
                               };

  template < class T >
  concept out_stream_operator_callable = requires ( QTextStream& os, T const& val ) {
                                           { os << val } -> same_as< QTextStream& >;
                                         };

  using namespace ::std;
  template < class T >
  struct StringizerHelper {
    // 重载决议：
    // 1. 首先会尝试查找偏特化，如果查找到了就略去下面的模板匹配
    // 2. 否则，如果是 QString 自己直接返回自己
    // 3. 否则，如果是一个 to_string 可调用类型，返回他的值
    // 4. 否则，如果是一个可转换到 QString 的类型，尝试转换类型
    // 5. 否则，如果它可以向流中格式化，尝试使用流转化为字符串类型
    // 6. 最后，断言错误或者抛出异常
    static QString convert ( T const& val ) {
      if constexpr ( is_qstring< T > ) {
        return val;
      } else if constexpr ( to_string_callable< T > ) {
        return val.to_string ( );
      } else if constexpr ( qstring_convertible< T > ) {
        return QString ( val );
      } else if constexpr ( out_stream_operator_callable< T > ) {
        QString     str = "";
        QTextStream os { &str, QIODeviceBase::ReadWrite };
        os << val << Qt::flush;
        return os.readAll ( );
      } else {
        assert ( false );
      }
    }
  };

  struct Stringizer {
    template < class T >
    static QString convert ( T const& val ) {
      return StringizerHelper< T >::convert ( val );
    }
  };
}; // namespace Runge::StringUtilities::privateDetails

namespace Runge::StringUtilities {
  using privateDetails::Stringizer;
  using privateDetails::StringizerHelper;
}; // namespace Runge::StringUtilities

#endif // FINAL_PROJ_STRINGIZER_HPP_
