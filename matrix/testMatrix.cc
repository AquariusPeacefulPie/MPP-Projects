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


/*
  Arithmetic operators
*/


TEST(additionInPlace,oneElement){
  int arr[1] = {5};
  int arr2[1] = {10};

  mat::Matrix<int,1,1> mat(arr);
  mat::Matrix<int,1,1> mat2(arr2);

  mat+=mat2;

  EXPECT_EQ(15,mat(0,0));
}


TEST(additionInPlace,ManyElements){
  int arr[1] = {5};
  int arr2[1] = {10};

  mat::Matrix<int,1,1> mat(arr);
  mat::Matrix<int,1,1> mat2(arr2);

  mat+=mat2;

  EXPECT_EQ(15,mat(0,0));
}


TEST(additionInPlace,differentOrder){
  int arr[1] = {5};
  int arr2[1] = {10};

  mat::Matrix<int,1,1> mat(arr);
  mat::Matrix<int,1,1> mat2(arr2);

  mat+=mat2;

  EXPECT_EQ(15,mat(0,0));
}


TEST(addition,oneElement){
  int arr[1] = {5};
  int arr2[1] = {10};

  mat::Matrix<int,1,1> mat(arr);
  mat::Matrix<int,1,1> mat2(arr2);

  mat::Matrix<int,1,1> mat3;
  mat3 = mat + mat2;

  EXPECT_EQ(15,mat3(0,0));
}


TEST(substractionInPlace,oneElement){
  int arr[1] = {5};
  int arr2[1] = {10};

  mat::Matrix<int,1,1> mat(arr);
  mat::Matrix<int,1,1> mat2(arr2);

  mat-=mat2;

  EXPECT_EQ(-5,mat(0,0));
}


TEST(substraction,oneElement){
  int arr[1] = {5};
  int arr2[1] = {10};

  mat::Matrix<int,1,1> mat(arr);
  mat::Matrix<int,1,1> mat2(arr2);

  mat::Matrix<int,1,1> mat3;
  mat3 = mat - mat2;

  EXPECT_EQ(-5,mat3(0,0));
}


TEST(product,manyElements){
  int arr[6] = {1,2,3,4,5,6};

  mat::Matrix<int,2,3> mat(arr);
  mat::Matrix<int,3,2> mat2(arr);

  mat::Matrix<int,2,2> mat3;

  std::cout<<"mat 1 : "<<std::endl;
  mat.print();

  std::cout<<"mat 1 : "<<std::endl;
  mat2.print();

  mat3 = mat * mat2;
   
  mat3.print();


  EXPECT_EQ(22,mat3(0,0));
  EXPECT_EQ(28,mat3(0,1));
  EXPECT_EQ(49,mat3(1,0));
  EXPECT_EQ(64,mat3(1,1));
}

TEST(product,squaredMatrix){
  int arr[4] = {1,2,3,4};

  mat::Matrix<int,2,2> mat(arr);
  mat::Matrix<int,2,2> mat2(arr);

  mat::Matrix<int,2,2> mat3;

  mat3 = mat * mat2;

  EXPECT_EQ(7,mat3(0,0));
  EXPECT_EQ(10,mat3(0,1));
  EXPECT_EQ(15,mat3(1,0));
  EXPECT_EQ(22,mat3(1,1));
}

TEST(productInPlace,squaredMatrix){
  int arr[4] = {1,2,3,4};

  mat::Matrix<int,2,2> mat(arr);
  mat::Matrix<int,2,2> mat2(arr);
  mat::Matrix<int,2,2> mat3;

  mat *= mat2;

  EXPECT_EQ(7,mat(0,0));
  EXPECT_EQ(10,mat(0,1));
  EXPECT_EQ(15,mat(1,0));
  EXPECT_EQ(22,mat(1,1));
}

TEST(transpose,squaredMatrix){
  int arr[4] = {1,2,3,4};
  mat::Matrix<int,2,2> mat(arr);
  mat::Matrix<int,2,2> mat2 = mat.transpose();
  

  EXPECT_EQ(1,mat2(0,0));
  EXPECT_EQ(3,mat2(0,1));
  EXPECT_EQ(2,mat2(1,0));
  EXPECT_EQ(4,mat2(1,1));

  EXPECT_EQ(1,mat2(0,0));
  EXPECT_EQ(3,mat2(0,1));
  EXPECT_EQ(2,mat2(1,0));
  EXPECT_EQ(4,mat2(1,1));
}

TEST(transpose,simple){
  int arr[6] = {1,3,5,2,4,6};
  mat::Matrix<int,2,3> mat(arr);
  mat::Matrix<int,3,2> mat2 = mat.transpose();

  EXPECT_EQ(1,mat(0,0));
  EXPECT_EQ(3,mat(0,1));
  EXPECT_EQ(5,mat(0,2));
  EXPECT_EQ(2,mat(1,0));
  EXPECT_EQ(4,mat(1,1));
  EXPECT_EQ(6,mat(1,2));

  EXPECT_EQ(1,mat2(0,0));
  EXPECT_EQ(2,mat2(0,1));
  EXPECT_EQ(3,mat2(1,0));
  EXPECT_EQ(4,mat2(1,1));
  EXPECT_EQ(5,mat2(2,0));
  EXPECT_EQ(6,mat2(2,1));
}




int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
