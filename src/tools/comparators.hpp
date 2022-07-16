#ifndef FINAL_PROJ_COMPARATORS_HPP_
#define FINAL_PROJ_COMPARATORS_HPP_

#include "concepts.h++"
#include "marks.hpp"

#include <QMap>
#include <QSet>
#include <QString>
#include <QVector>
#include <concepts>
#include <iterator>
#include <type_traits>

namespace Runge::Comparators::privateDetails {
  using namespace ::Runge::Marks;
  using namespace ::std;
  using namespace ::Runge::Concepts;

  class BasicContainerComparator {
  public:
    // 约束，必须是线性容器，数据类型必须正则
    // TODO: 实现线性容器的概念约束
    template < regular DataType, template < typename > typename Container >
    static Container< ComparedMark > compare ( Container< DataType > const& answer,
                                               Container< DataType > const& guess ) {
      Container< ComparedMark >                                           res;
      QMap< DataType, typename Container< DataType >::size_type >         misplaced_map;
      QMap< DataType, QSet< typename Container< DataType >::size_type > > answer_map;

      for ( auto it = std::cbegin ( answer ); it != std::cend ( answer ); ++it ) {
        answer_map [ *it ].insert ( distance ( std::cbegin ( answer ), it ) );
        misplaced_map [ *it ] = 0;
      }

      for ( auto it = guess.cbegin ( ); it != guess.cend ( ); ++it ) {
        if ( ! answer_map.contains ( *it ) ) {
          res.push_back ( ComparedMark::Wrong );
        } else {
          if ( answer_map [ *it ].contains ( distance ( std::cbegin ( guess ), it ) ) ) {
            res.push_back ( ComparedMark::Correct );
            answer_map [ *it ].remove ( distance ( std::cbegin ( guess ), it ) );
          } else {
            if ( answer_map [ *it ].size ( ) > misplaced_map [ *it ] ) {
              res.push_back ( ComparedMark::Misplaced );
              ++misplaced_map [ *it ];
            } else {
              res.push_back ( ComparedMark::Wrong );
            }
          }
        }
      }

      return res;
    }
    //
  };

  class BasicStringComparator {
  public:
    // 约束，必须是字符型
    // TODO: 实现字符型约束
    template < class StringType >
    static QVector< ComparedMark > compare ( StringType const& answer, StringType const& guess ) {
      using char_type = typename StringType::value_type;
      QVector< char_type > answer_list;
      QVector< char_type > guess_list;

      for ( auto const val : answer ) { answer_list.push_back ( val ); }
      for ( auto const val : guess ) { guess_list.push_back ( val ); }

      return BasicContainerComparator::compare< char_type, QVector > ( answer_list, guess_list );
    }
  };

  class BinaryContainerComparator { // 二值比较，将不会返回 Misplaced
  public:
    template < regular DataType, template < typename > typename Container >
    static Container< ComparedMark > compare ( Container< DataType > const& answer,
                                               Container< DataType > const& guess ) {
      Container< ComparedMark > res;

      for ( int i = 0; i < answer.size ( ); ++i ) {
        if ( answer [ i ] == guess [ i ] ) {
          res.push_back ( ComparedMark::Correct );
        } else {
          res.push_back ( ComparedMark::Wrong );
        }
      }
      return res;
    }
  };

  class BinaryStringComparator {
  public:
    template < class StringType >
    static QVector< ComparedMark > compare ( StringType const& answer, StringType const& guess ) {
      using char_type = typename StringType::value_type;
      QVector< char_type > answer_list;
      QVector< char_type > guess_list;

      for ( auto const val : answer ) { answer_list.push_back ( val ); }
      for ( auto const val : guess ) { guess_list.push_back ( val ); }

      return BinaryContainerComparator::compare< char_type, QVector > ( answer_list, guess_list );
    }
  };
}; // namespace Runge::Comparators::privateDetails

namespace Runge::Comparators {
  using privateDetails::BasicContainerComparator;
  using privateDetails::BasicStringComparator;
  using privateDetails::BinaryContainerComparator;
  using privateDetails::BinaryStringComparator;
}; // namespace Runge::Comparators

#endif
