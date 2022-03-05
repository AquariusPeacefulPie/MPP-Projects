#ifndef T_TUPLE_H
#define T_TUPLE_H

namespace t {


  template<typename ... Others>
  class Tuple {
    int operator()(){
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
    Tuple(T firstValue, Others ... otherValues) : value(firstValue),rightMember(get(1),otherValues ...)   
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
    Tuple<T,Others ...> operator+(const Tuple<OtherType, OtherTypes...>& other) {

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
     * Division between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...>& operator/=(const Tuple<OtherTypes...>& other) {

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
