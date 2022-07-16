#ifndef FINAL_PROJ_CONCEPTS_HPP_
#define FINAL_PROJ_CONCEPTS_HPP_

#include "utilities.h++"

#include <type_traits>

namespace Runge::Concepts::privateDetails {
  using namespace ::std;
  using namespace ::Runge::Utilities;

  template < class T >
  concept noncopyable = !
  is_copy_assignable_v< T > && ! is_copy_constructible_v< T >;

  template < class T >
  concept just_movable = noncopyable< T > && movable< T >;

#define Runge_Has_Type_Concept( subtype )                                                                              \
  template < class T >                                                                                                 \
  concept has_##subtype =                                                                                              \
    requires ( )                                                                                                       \
  {                                                                                                                    \
    typename T::subtype;                                                                                               \
  };

  Runge_Has_Type_Concept ( string_type );

  template < class T >
  concept is_correct_callable = requires ( T const& t ) {
                                  { t.is_correct ( ) } -> same_as< bool >;
                                  { t.operator bool ( ) } -> same_as< bool >;
                                };

  template < class T, class ComparedWordle >
  concept compare_callable
      = requires ( const typename ComparedWordle::wordle& wordle1, const typename ComparedWordle::wordle& wordle2 ) {
          { T::compare ( wordle1, wordle2 ) } -> same_as< ComparedWordle >;
        };

  template < class T, class Wordle >
  concept is_valid_wordle_callable = requires ( const T& obj, Wordle const& wordle ) {
                                       { obj.is_valid_wordle ( wordle ) } -> same_as< bool >;
                                     };

  template < class T, class Wordle >
  concept generate_callable = requires ( T& obj ) {
                                { obj.generate ( ) } -> same_as< Wordle >;
                              };

  template < class T, class String, class Wordle, class Error, template < class, class > class ResultType >
  concept parse_callable = requires ( T& obj, String const& data ) {
                             { obj.parse ( data ) } -> same_as< ResultType< Wordle, Error > >;
                           };

  template < class T, class Stream, class Wordle >
  concept print_callable = requires ( T& obj, Wordle const& wordle, Stream& stream ) {
                             { obj.print ( stream, wordle ) }; // 我们不规范 print 的函数的返回值
                           };


  template < class T, class Result >
  concept get_in_stream_callable = requires ( const T& obj ) {
                                     { obj.get_in_stream ( ) } -> same_as< Result& >;
                                   };

  template < class T, class Result >
  concept get_out_stream_callable = requires ( const T& obj ) {
                                      { obj.get_out_stream ( ) } -> same_as< Result& >;
                                    };
}; // namespace Runge::Concepts::privateDetails

// namespace Runge::Concepts {
//   using privateDetails::is_comparator_compatible_wordle_generator;
//   using privateDetails::is_comparator_compatible_wordle_io_device;
//   using privateDetails::is_compared_wordle;
//   using privateDetails::is_compared_wordle_of;
//   using privateDetails::is_io_device;
//   using privateDetails::is_io_device_of_wordle;
//   using privateDetails::is_wordle;
//   using privateDetails::is_wordle_comparator;
//   using privateDetails::is_wordle_comparator_of;
//   using privateDetails::is_wordle_generator;
//   using privateDetails::is_wordle_generator_of;
//   using privateDetails::is_wordle_regularizer;
//   using privateDetails::is_wordle_regularizer_of;
//   using privateDetails::is_wordle_validator;
// };  //  namespace Runge::Concepts
//
// namespace Runge::Concepts::QtText {
//   using privateDetails::is_comparator_compatible_qt_text_wordle_io_device;
//   using privateDetails::is_qt_text_io_compared_wordle;
//   using privateDetails::is_qt_text_io_compared_wordle_of;
//   using privateDetails::is_qt_text_io_device;
//   using privateDetails::is_qt_text_io_device_of_wordle;
//   using privateDetails::is_qt_text_io_wordle;
// };  //  namespace Runge::Concepts::QtText

namespace Runge::Concepts {
  template < class T >
  concept is_io_device
      = privateDetails::just_movable<
            T > && privateDetails::get_in_stream_callable< T, typename T::input_pipeline > && privateDetails::get_out_stream_callable< T, typename T::output_pipeline > && privateDetails::has_string_type< T >;

  template < class T >
  concept is_wordle = std::semiregular< T >;

  template < class T >
  concept is_compared_wordle
      = std::semiregular< T > && is_wordle< typename T::wordle > && privateDetails::is_correct_callable< T >;

  template < class T, class Wordle >
  concept is_compared_wordle_of = is_compared_wordle< T > && std::same_as< typename T::wordle, Wordle >;

  template < class T >
  concept is_wordle_comparator
      = std::is_abstract_v<
            T > && is_compared_wordle_of< typename T::compared_wordle, typename T::wordle > && privateDetails::compare_callable< T, typename T::compared_wordle >;

  template < class T, class ComparedWordle >
  concept is_wordle_comparator_of_compared
      = is_wordle_comparator< T > && std::same_as< typename T::compared_wordle, ComparedWordle >;

  template < class T >
  concept is_wordle_generator
      = privateDetails::just_movable< T > && privateDetails::generate_callable< T, typename T::wordle >;

  template < class T, class Wordle >
  concept is_wordle_generator_of = is_wordle_generator< T > && std::same_as< typename T::wordle, Wordle >;

  template < class T >
  concept is_wordle_parser
      = privateDetails::just_movable<
            T > && is_io_device< typename T::io_device > && privateDetails::parse_callable< T, typename T::io_device::string_type, typename T::wordle, typename T::error, ::Runge::Utilities::Result >;

  template < class T, class Wordle >
  concept is_wordle_parser_of = is_wordle_parser< T > && std::same_as< typename T::wordle, Wordle >;

  template < class T >
  concept is_wordle_formatter
      = std::
            is_abstract_v< T > && is_io_device< typename T::io_device > && privateDetails::print_callable< T, typename T::io_device::output_pipeline, typename T::wordle > && privateDetails::print_callable< T, typename T::io_device::output_pipeline, typename T::compared_wordle > && is_compared_wordle_of< typename T::compared_wordle, typename T::wordle >;


}; // namespace Runge::Concepts

#define Runge_Test_Impl_Trait( trait, arg... ) static_assert ( trait< arg > )

#endif
