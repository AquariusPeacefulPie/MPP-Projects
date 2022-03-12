#ifndef T_TUPLE_H
#define T_TUPLE_H

namespace t {


  bool check(){
    return true;
  }


  template<typename ... Others>
  class Tuple {
    int operator()(){
      return 0;
    }
  public:
    // template<int index>
    //  auto get() {

    //   return nullptr;
    // }

    // template <typename ... OtherTypes>
    // bool operator==(const Tuple<OtherTypes...>& other)const {
    //       return true;
    // }

  };

    /**
   * Helper function to create a tuple
   */
  template <class... Types>
  constexpr Tuple<Types...> makeTuple(Types&&... args) {
    return {std::forward<Types>(args)...};
  }


  template<typename T, typename ... Others>
  class Tuple<T, Others...> {
  public:
    //  friend class rightMember;
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

    Tuple<Others ...> getRightMember()const {
      return this->rightMember;
    }

    /**
     * Value getter
     */
    template<int index>
     const auto& get() const{
      // return rightMember.test();
      if constexpr( index != 0){
          return rightMember.template get<index - 1 >();
      }else{
        return this->value;
      }
    }

    /**
     * Value getter
     */
    template<int index>
      auto& get() {
      // return rightMember.test();
      if constexpr( index != 0){
          return rightMember.template get<index - 1 >();
      }else{
        return this->value;
      }
    }





    /**
     * Addition between to tuples
     */
    
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator+(const Tuple<OtherTypes...>& other) const {
      
      // Premiere methode probleme si on fait float + int et que other a un int c'est un int qui est retourné alors que ca doit être un float

      //  auto t = other;
      // t += *this; 
      // return t;


      //Deuxieme methode avec makeTuple mais probleme je vois pas comment faire avec make tuple sachant qu'on a pas le bon nombre d'argument
      const size_t size = sizeof...(OtherTypes) ;
      
      auto t3 = t::makeTuple( get<0>() + other.template get<0>(),get<1>() + other.template get<1>() );


      // std::cout << typeid(s).name() << "\n";
     return t3;
    }


    /**
     * Addition between two tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> &operator+=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value = get<0>() +  other.template get<0>();
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember += other.getRightMember();
      }
      return *this;
    }

    /**
     * Substraction between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator-(const Tuple<OtherTypes...>& other)const {
      auto t = other;
      t -= *this; 
      return t;
    }

    /**
     * Substraction between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> & operator-=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value -=  other.value;
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember -= other.rightMember;
      }
      return *this;
    }

    /**
     * Multiplication between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator*(const Tuple<OtherTypes...>& other)const {
      auto t = other;
      t *= *this; 
      return t;
    }

    /**
     * Multiplication between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...>& operator*=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value *=  other.value;
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember *= other.rightMember;
      }
      return *this;
    }

    /**
     * Division between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator/(const Tuple<OtherTypes...>& other)const {
      auto t = other;
      t /= *this; 
      return t;
    }

    /**
     * Division between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...>& operator/=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value /=  other.value;
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember /= other.rightMember;
      }
      return *this;
    }

    /**
     * Comparaison operators
     */
    template <typename ... OtherTypes>
    bool operator==(const Tuple<OtherTypes...>& other)const {
      const size_t size = sizeof...(OtherTypes) ;
        if ( other.value != value){
          return false;
        }else{
            if constexpr(size == 1){
              return true;
            }else{
              return (this->rightMember == other.rightMember);
            }
        } 
    }


    template <typename ... OtherTypes>
    bool operator!=(const Tuple<OtherTypes...>& other)const {
      const size_t size = sizeof...(OtherTypes) ;

        if ( other.value != value){
          return true;
        }else{
            if constexpr(size == 1){
              return false;
            }else{
              return (this->rightMember != other.rightMember);
            }
        }

    }

    template <typename ... OtherTypes>
    bool operator<(const Tuple<OtherTypes...>& other)const {
      const size_t size = sizeof...(OtherTypes) ;

        if ( value < other.value ){
          return true;
        }else {
            if constexpr(size == 1){
              return false;

            }else{
              return (this->rightMember < other.rightMember);
            }
        } 
    }

    template <typename ... OtherTypes>
    bool operator<=(const Tuple<OtherTypes...>& other) const{
      const size_t size = sizeof...(OtherTypes) ;

        if ( value <= other.value ){
          return true;
        }else {
            if constexpr(size == 1){
              return true;
            }else{
              return (this->rightMember <= other.rightMember);
            }
        } 

    }

    template <typename ... OtherTypes>
    bool operator>(const Tuple<OtherTypes...>& other)const {
      const size_t size = sizeof...(OtherTypes) ;

        if ( value > other.value ){
          return true;
        }else {
            if constexpr(size == 1){
              return false;
            }else{
              return (this->rightMember > other.rightMember);
            }
        }
         
    }

    template <typename ... OtherTypes>
    bool operator>=(const Tuple<OtherTypes...>& other) const{
      const size_t size = sizeof...(OtherTypes) ;

        if ( value >= other.value ){
          return true;
        }else {

            if constexpr(size == 1){
              return true;
            }else{
              return (this->rightMember >= other.rightMember);
            }

        } 
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

  // /**
  //  * Helper function to create a tuple
  //  */
  // template <class... Types>
  // constexpr Tuple<Types...> makeTuple(Types&&... args) {
  //   return {std::forward<Types>(args)...};
  // }

  

}

#endif // T_TUPLE_H
