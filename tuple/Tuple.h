#ifndef T_TUPLE_H
#define T_TUPLE_H

namespace t {

  template<typename T, typename ... Other>
  class Tuple {
  public:
    /**
     * Default constructor
     */
    Tuple() = default;


    /**
     * Constructor to initialize values
     */
    Tuple(T firstValue, Other ... otherValue):value(firstValue),rightMember(otherValue ...)   
    {
    }

    /**
     * Value getter
     */
    template<int index>
    T get() {
      if( index != 0){
        return rightMember.get(index - 1);
      }
      return this->value;
    }

    /**
     * Addition between to tuples
     */
    template <typename OtherType, typename ... OtherTypes>
    Tuple<T,Other> operator+(const Tuple<OtherType, OtherTypes...>& other) {

    }

    /**
     * Addition between two tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Other ...> operator+=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Substraction between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Other ...> operator-(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Substraction between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Other ...>& operator-=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Multiplication between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Other ...> operator*(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Multiplication between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Other ...>& operator*=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Division between to tuples
     */
    template <typename ... OtherTypes>
    Tuple</* implementation defined */> operator/(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Division between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple</* implementation defined */>& operator/=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Comparaison operators
     */
    template <typename ... OtherTypes>
    bool operator==(const Tuple<OtherTypes...>& other) {

    }

    template <typename ... OtherTypes>
    bool operator!=(const Tuple<OtherTypes...>& other) {

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
    Tuple</* implementation defined */> operator|(Tuple<OtherTypes...>&& other) {

    }
  private:
    T value;
    t::Tuple<Other ...> rightMember;
  };

  /**
   * Helper function to create a tuple
   */
  template <class... Types>
  constexpr Tuple<Types...> makeTuple(Types&&... args) {

  }
  

}

#endif // T_TUPLE_H
