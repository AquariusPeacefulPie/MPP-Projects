#ifndef MAT_MATRIX_H
#define MAT_MATRIX_H
#include <array>
 
namespace mat {
  enum class MatrixOrdering {
    RowMajor,
    ColMajor,
  };

  template<typename Type, int RowCount, int ColCount, MatrixOrdering order = MatrixOrdering::RowMajor>
  class Matrix {
  public:

    static constexpr int Rows = RowCount;

    // Columns count
    static constexpr int Cols = ColCount;

    // Elements count
    static constexpr int Size = Cols*Rows;

    // Matrix order
    static constexpr MatrixOrdering Order = order;

    // Default constructor



    constexpr Matrix() {
      for( size_t i = 0 ; i < RowCount*ColCount ;i++){
        m_container[i]= 0;
      }
    }

    // Initialisation constructor
    template<int DataLength>
    constexpr Matrix(const Type(&data)[DataLength]) {
      static_assert(DataLength == Size,"Size is different");
      for(size_t i = 0 ; i < RowCount*ColCount ;i++){
        m_container[i] = data[i];
      }
    }

    // Conversion constructor
    // constexpr Matrix(const Matrix<Type, Rows, Cols, Order>& other) {
    //   int k = 0;
    //   if(Order != this.Order){
    //     auto otherConvert = convert(other);
    //     for(auto it = otherConvert.begin(); it != otherConvert.end(); ++it) {
    //       m_container[k] = *it;
    //       k++;
    //     }
    //   }else{
    //     for(auto it = other.begin(); it != other.end(); ++it) {
    //       m_container[k] = *it;
    //       k++;
    //   }
    // }
    // }


    // Affectation from a matrix with different ordering
    // constexpr auto& operator=(const Matrix<Type, Rows, Cols, Order>& other) {
    // }

    // // Return the transposed matrix
    constexpr Matrix<Type, Cols, Rows, Order> transpose() {
      Matrix<Type,Cols,Rows,Order> newMat;
      for(size_t i = 0; i<Cols; i++){
        for(size_t j = 0; j<Rows; j++){ 
          newMat(i,j) = (*this)(j,i);
        }
      }
      return newMat;
    }

    // Get the value at specified row and col
    constexpr const Type& operator() (int row, int col) const {
      if(order == MatrixOrdering::RowMajor){
        return  m_container[(row * Cols) + col];
      }
        return  m_container[(col * Rows) + row];      
    }

    constexpr Type& operator() (int row, int col) {
      if(order == MatrixOrdering::RowMajor){
        return  m_container[(row * Cols) + col];
      }
        return  m_container[(col * Rows) + row];      
    }

    //Print the matrix in the terminal
    void print(){
      for(size_t i = 0; i<Rows; i++){
        for(size_t j = 0; j<Cols; j++){
          std::cout<<(*this)(i,j)<<" ";
        }
        std::cout<<std::endl;
      }
    }

    // Addition - in place
    template<typename OtherType, MatrixOrdering otherOrder>
    auto& operator+=(const Matrix<OtherType, Rows, Cols, otherOrder>& other) {
      Matrix<Type, Rows, Cols, Order> tmp;
      tmp = *this + other;

      *this = tmp;

      return *this;
    }

    // Addition - classic
    template<typename OtherType, MatrixOrdering otherOrder>
    constexpr Matrix<std::common_type_t<Type, OtherType>, Rows, Cols, Order> operator+(const Matrix<OtherType, Rows, Cols, otherOrder>& other) const {
      Matrix<Type,Rows,Cols,Order> newMat;
      for(size_t i = 0; i<Rows; i++){
        for(size_t j = 0; j<Cols; j++){
          newMat(i,j) = (*this)(i,j) + other(i,j);
        }
      }
      return newMat;
    }

     // Substration - in place
    template<typename OtherType, MatrixOrdering otherOrder>
    auto& operator-=(const Matrix<OtherType, Rows, Cols, otherOrder>& other) {
      Matrix<Type, Rows, Cols, Order> tmp;
      tmp = *this - other;

      *this = tmp;

      return *this;
    }

    // Substraction - classic
    template<typename OtherType, MatrixOrdering otherOrder>
    constexpr Matrix<std::common_type_t<Type, OtherType>, Rows, Cols, Order> operator-(const Matrix<OtherType, Rows, Cols, otherOrder>& other) const {
      Matrix<Type,Rows,Cols,Order> newMat;
      for(size_t i = 0; i<Rows; i++){
        for(size_t j = 0; j<Cols; j++){
          newMat(i,j) = (*this)(i,j) - other(i,j);
        }
      }
      return newMat;
    }

    // Product - in place
    template<typename OtherType, MatrixOrdering otherOrder>
    auto& operator*=(const Matrix<OtherType, Rows, Cols, otherOrder>& other) {
      Matrix<Type, Rows, Cols, Order> tmp;
      tmp = *this * other;

      *this = tmp;

      return *this;
    }

    // Product - classic
    template<typename OtherType, int OtherCols, MatrixOrdering otherOrder>
    constexpr Matrix<std::common_type_t<Type, OtherType>, Rows, OtherCols, Order> operator*(const Matrix<OtherType, Cols, OtherCols, otherOrder>& other) const  {
      Matrix<Type,Rows,OtherCols,Order> newMat;
      //Memory indexes
      int b = 0;
      int rank = 0;
      int c = 0;
      //Matrix computation
      for(size_t i = 0; i<Rows; ++i){
        for(size_t j = 0; j<OtherCols*Cols+OtherCols-1; ++j){
            if(b==Cols){
              b = 0;
              rank++;
              c++;
            }
            else{
              newMat(i,rank) += (*this)(i,b) * other(b,c); 
              b++;
            }
        }
        c = rank = b = 0;
      }
      return newMat;
    }

    // Equality
    template<typename OtherType, int OtherRows, int OtherCols, MatrixOrdering otherOrder>
    constexpr bool operator==(const Matrix<OtherType, OtherRows, OtherCols, otherOrder>& other) const {
      for(size_t i = 0; i<OtherRows; i++){
        for(size_t j = 0; j<OtherCols; j++){
          if((*this)(i,j)!=other(i,j)){
            return false;
          }
        }
      }
      return true;
    }

    // Difference
    template<typename OtherType, int OtherRows, int OtherCols, MatrixOrdering otherOrder>
    constexpr bool operator!=(const Matrix<OtherType, OtherRows, OtherCols, otherOrder>& other) const {
      return !(*this == other);
    }

  // public:
  //   /**
  //    * Define here the iterator classe
  //    * iterator must be allow to modify the values
  //    * const_iterator must be point to constant value
  //    */

    using iterator = typename std::array<Type,Size>::iterator ;

    constexpr iterator begin() {

      return m_container.begin();
    }

    constexpr iterator end() {
      return m_container.end();
    }

    using const_iterator = typename std::array<Type,Size>::const_iterator ;

    constexpr const_iterator begin() const {
      return m_container.cbegin();
    }

    constexpr const_iterator end() const {
      return m_container.cend();
    }

  private:
    std::array<Type,RowCount*ColCount> m_container;
  };

  /**
   * Define here the VecR and VecC classes
   */
// template<typename Type, int RowCount, int ColCount, MatrixOrdering order = MatrixOrdering::RowMajor>
// class VecC : protected mat::Matrix
// { 
//     public: 
//     constexpr VecC() {
//       for( size_t i = 0 ; i < Rows ;i++){
//         m_container[i]= 0;
//       }
//     }
// }; 

  // template<typename Type, int Cols>
  // constexpr VecR<Type, Cols> vecRow(const Type(&data)[Cols]) {
  // }

  // template<typename Type, int Rows>
  // constexpr VecC<Type, Rows> vecCol(const Type(&data)[Rows]) {
    
  //   for(size_t i = 0 ; i < Rows ;i++){
  //     vecCol->m_container[i] = data[i];
  //   }    
  // }



  // Convert the matrix to the opposite ordering
  template<typename Type, int Rows, int Cols, MatrixOrdering Order>
  constexpr auto convert(const Matrix<Type, Rows, Cols, Order>& mat) {
    std::array <Type,Rows*Cols> tempArray;
    Type newArray[Cols*Rows];
    
    int k = 0;
    for(auto it = mat.begin(); it != mat.end(); ++it) {
      tempArray[k] = *it;
      ++k; 
    }

    k = 0;

    if constexpr(Order == MatrixOrdering::RowMajor){
      for(int i = 0; i < Cols ;i++){
        for(int j = i ;j < Rows*Cols ;j = j + Cols){
          newArray[k] = tempArray[j];
          k++;
        // std::cout<< newArray[j] << "*****\n";
        }
      }
        return Matrix<Type, Rows, Cols, MatrixOrdering::ColMajor>(newArray);
        
    }else{
      for(int i = 0 ; i < Rows ; i++){
        for(int j = i ; j < Rows*Cols ; j = j + Rows){
          newArray[k] = tempArray[j];
          k++;        
        }
      }
      return Matrix<Type, Rows, Cols, MatrixOrdering::RowMajor>(newArray);
    }


    // return s;

    

  }
  

  // // Retrun the identity matrix
  // template<typename Type, int Size>
  // constexpr Matrix<Type, Size, Size> identity() {
  // }
}

#endif // MAT_MATRIX_H
