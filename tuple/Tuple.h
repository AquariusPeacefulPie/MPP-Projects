#ifndef T_TUPLE_H
#define T_TUPLE_H

namespace t {

  template</* implementation defined */>
  class Tuple {
  public:
    /**
     * Default constructor
     */
    Tuple() {

    }

    /**
     * Constructor to initialize values
     */
    Tuple(/* implementation defined */) {

    }

    /**
     * Value getter
     */
    template<int index>
    /* implementation defined */ get() {

    }

    /**
     * Addition between to tuples
     */
    template <typename OtherType, typename ... OtherTypes>
    Tuple</* implementation defined */> operator+(const Tuple<OtherType, OtherTypes...>& other) {

    }

    /**
     * Addition between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple</* implementation defined */> operator+=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Substraction between to tuples
     */
    template <typename ... OtherTypes>
    Tuple</* implementation defined */> operator-(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Substraction between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple</* implementation defined */>& operator-=(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Multiplication between to tuples
     */
    template <typename ... OtherTypes>
    Tuple</* implementation defined */> operator*(const Tuple<OtherTypes...>& other) {

    }

    /**
     * Multiplication between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple</* implementation defined */>& operator*=(const Tuple<OtherTypes...>& other) {

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
  };

  /**
   * Helper function to create a tuple
   */
  template <class... Types>
  constexpr Tuple<Types...> makeTuple(Types&&... args) {

  }

}

#endif // T_TUPLE_H
