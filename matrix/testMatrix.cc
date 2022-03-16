#include <gtest/gtest.h>

#include "Matrix.h"

TEST(constructor,debut){
mat::Matrix<int,2,3>mat;

}

TEST(constructor,withArray){
  mat::Matrix<int, 2, 3> mat({1, 2, 3, 4, 5, 6});
  std::cout << mat.Rows << "\n";
  std::cout << mat.Size << "\n";

}

TEST(operator,test){
  mat::Matrix<int, 2, 4> mat({1, 2, 3, 4, 5, 6,7,8});
  std::cout << mat(1,2) << "----\n";

}


TEST(convert,RowToCOl){
  mat::Matrix<int, 3, 4> matrice({1,2,3,4,5,6,7,8,9,10,11,12});

  EXPECT_EQ( matrice(0,0),1);
  EXPECT_EQ( matrice(0,1),2);
  EXPECT_EQ( matrice(0,2),3);
  EXPECT_EQ( matrice(0,3),4);

  EXPECT_EQ( matrice(1,0),5);
  EXPECT_EQ( matrice(1,1),6);
  EXPECT_EQ( matrice(1,2),7);
  EXPECT_EQ( matrice(1,3),8);

  EXPECT_EQ( matrice(2,0),9);
  EXPECT_EQ( matrice(2,1),10);
  EXPECT_EQ( matrice(2,2),11);
  EXPECT_EQ( matrice(2,3),12);
  EXPECT_TRUE(matrice.Order == mat::MatrixOrdering::RowMajor);

  mat::Matrix newMatrix = mat::convert( matrice );
  EXPECT_EQ( newMatrix(0,0),1);
  EXPECT_EQ( newMatrix(0,1),2);
  EXPECT_EQ( newMatrix(0,2),3);
  EXPECT_EQ( newMatrix(0,3),4);

  EXPECT_EQ( newMatrix(1,0),5);
  EXPECT_EQ( newMatrix(1,1),6);
  EXPECT_EQ( newMatrix(1,2),7);
  EXPECT_EQ( newMatrix(1,3),8);

  EXPECT_EQ( newMatrix(2,0),9);
  EXPECT_EQ( newMatrix(2,1),10);
  EXPECT_EQ( newMatrix(2,2),11);
  EXPECT_EQ( newMatrix(2,3),12);
  EXPECT_TRUE(newMatrix.Order == mat::MatrixOrdering::ColMajor);

}

TEST(convert,ColToRow){
  mat::Matrix<int, 2, 3,mat::MatrixOrdering::ColMajor> matrice({1,2,3,4,5,6});
  
  EXPECT_EQ( matrice(0,0),1);
  EXPECT_EQ( matrice(0,1),3);
  EXPECT_EQ( matrice(0,2),5);
  EXPECT_EQ( matrice(1,0),2);
  EXPECT_EQ( matrice(1,1),4);
  EXPECT_EQ( matrice(1,2),6);
  EXPECT_TRUE(matrice.Order == mat::MatrixOrdering::ColMajor);
  mat::Matrix newMatrix = mat::convert( matrice );
  EXPECT_EQ( newMatrix(0,0),1);
  EXPECT_EQ( newMatrix(0,1),3);
  EXPECT_EQ( newMatrix(0,2),5);
  EXPECT_EQ( newMatrix(1,0),2);
  EXPECT_EQ( newMatrix(1,1),4);
  EXPECT_EQ( newMatrix(1,2),6);
  EXPECT_TRUE(newMatrix.Order == mat::MatrixOrdering::RowMajor);

}



int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
