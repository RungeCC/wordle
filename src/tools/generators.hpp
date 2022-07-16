//
// Created by runge on 22-6-28.
//

#ifndef FINAL_PROJ_GENERATORS_HPP_
#define FINAL_PROJ_GENERATORS_HPP_

#include "utilities.h++"

#include <memory>
#include <random>

namespace Runge::Generators {
  template < class Resource, class RandomEngine = std::mt19937_64 >
  class BasicRandomGenerator {
  public:
    using wordle          = typename Resource::wordle;
    using resource_holder = Resource;
    using random_engine   = RandomEngine;

  private:
    std::shared_ptr< Resource >                res_ptr_;
    RandomEngine                               engine_ { std::random_device { }( ) };
    std::uniform_int_distribution< qsizetype > int_dist_;

  public:
    Runge_Generate_Just_Movable ( BasicRandomGenerator )

  public:
    explicit BasicRandomGenerator ( std::shared_ptr< Resource > res )
      : res_ptr_ { res }
      , int_dist_ { 0, res->size ( ) - 1 } { }

  public:
    typename Resource::wordle generate ( ) {
      auto res = res_ptr_->data ( ) [ int_dist_ ( engine_ ) ];
      return res;
    }
  };

}; // namespace Runge::Generators

#endif // FINAL_PROJ_GENERATORS_HPP_
