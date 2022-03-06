#ifndef T_TUPLE_H
#define T_TUPLE_H

#include <string>
#include <iostream>

namespace t {


  template<typename ... Others>
  class Tuple {   
  public:
    template<int index>
    auto get() {
      return 0;
    }
  };


  template<typename T, typename ... Others>
  class Tuple<T, Others...> {
  public:
    /**
     * Default constructor
     */
    Tuple() = default;


    /**
     * Constructor to initialize values
     */
    Tuple(T firstValue, Others ... otherValues) : value(firstValue),rightMember(otherValues ...)   
    {

    }



    template <std::size_t index, typename... OthersTypes>
    void print()
    {
      if constexpr (index == 0)
      {
        return;
      }
      std::cout<<this->template get<index-1>()<<std::endl;
      print<index-1>();
    }

   /**
     * Values getter
     */
    template<int index>
    T get() {
      // return rightMember.test();
      if( index != 0){
          return rightMember.template get<index - 1 >();
      }
      return this->value;
    }

   

    /**
     * Addition between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator+(const Tuple<OtherTypes...>& other) {
      
    }

    /**
     * Addition between two tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator+=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Substraction between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator-(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Substraction between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...>& operator-=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Multiplication between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator*(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Multiplication between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...>& operator*=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Division between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator/(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Division between two tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...>& operator/=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Comparison operators
     */

    template <std::size_t index, typename... OthersTypes>
    bool compareTuple(t::Tuple<OthersTypes...> &t2)
    {
      if constexpr (index == 0)
      {
        return this->template get<0>() == t2.template get<0>();
      }
      else
      {
        return this->template get<index>() == t2.template get<index>() && 
                                  this->compareTuple<index - 1>(t2);
      }
    }

    template <typename ... OtherTypes>
    bool operator==(const Tuple<OtherTypes...>& other) {
      return this->compareTuple<sizeof...(OtherTypes) - 1>(other);
    }


    template <typename ... OtherTypes>
    bool operator!=(const Tuple<OtherTypes...>& other) {
      /* T0 DO */
    }

    template <typename ... OtherTypes>
    bool operator<(const Tuple<OtherTypes...>& other) {

    }

    template <typename ... OtherTypes>
    bool operator<=(const Tuple<OtherTypes...>& other) {

    }

    template <typename ... OtherTypes>
    bool operator>(const Tuple<OtherTypes...>& other) {

    }

    template <typename ... OtherTypes>
    bool operator>=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Concatenate two tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator|(Tuple<OtherTypes...>&& other) {

    }
  private:
    T value;
    t::Tuple<Others ...> rightMember;
  };

  /**
   * Helper function to create a tuple
   */
  template <class... Types>
  constexpr Tuple<Types...> makeTuple(Types&&... args) {

  }
  

}

#endif // T_TUPLE_H
