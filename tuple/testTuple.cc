#include <gtest/gtest.h>
#include <iostream>

#include "Tuple.h"

TEST(Tuple,firstTest){
  t::Tuple<int,std::size_t,int,int,int> t(4,78,8,7,9);
  auto res = t.get<1>();
  std::cout << res;
  EXPECT_TRUE((std::is_same<decltype(res),int>::value) );
}

/* Constructors */

TEST(constructor,construction){
  t::Tuple<int,double> test(13,17);
  
  std::cout<<"element : "<<test.get<1>()<<std::endl;
}

/* Comparison operators */

TEST(operatorEqual,sameType){
  t::Tuple<int> t1(42);
  t::Tuple<int> t2(42);
  
  EXPECT_TRUE(t1==t2);
}

TEST(operatorEqual,differentTypesCompatible){
  t::Tuple<double> t1(42.0);
  t::Tuple<int> t2(42);

  EXPECT_TRUE((std::is_same<decltype(t1.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1==t2);
  EXPECT_TRUE(t1==t2);
}

TEST(operatorEqual,manyElementsCorrect){
  t::Tuple<double,int,std::string> t1(42.0,66,"abc");
  t::Tuple<double,int> t2(42.0,66,"abc");

  EXPECT_NO_THROW(t1==t2);
  EXPECT_TRUE(t1==t2);
}

TEST(operatorNotEqual,sameType){
  t::Tuple<int> t1(42);
  t::Tuple<int> t2(42);
  
  EXPECT_TRUE(t1==t2);
}

TEST(operatorNotEqual,differentTypesCompatible){
  t::Tuple<double> t1(42.0);
  t::Tuple<int> t2(43);

  EXPECT_TRUE((std::is_same<decltype(t1.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1!=t2);
  EXPECT_TRUE(t1!=t2);
}

TEST(operatorNotEqual,manyElementsCorrect){
  t::Tuple<double,int,std::string> t1(42.0,66,"abc");
  t::Tuple<double,int> t2(42.0,78,"abc");

  EXPECT_NO_THROW(t1!=t2);
  EXPECT_TRUE(t1!=t2);
}


TEST(operatorSuperior,sameType){
  t::Tuple<int> t1(43);
  t::Tuple<int> t2(42);
  
  EXPECT_TRUE(t1>t2);
}

TEST(operatorSuperior,differentTypesCompatible){
  t::Tuple<double> t1(43.0);
  t::Tuple<int> t2(42);

  EXPECT_TRUE((std::is_same<decltype(t1.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1>t2);
  EXPECT_TRUE(t1>t2);
}

TEST(operatorSuperior,manyElementsCorrect){
  t::Tuple<double,int,std::string> t1(43.0,67,"def");
  t::Tuple<double,int> t2(42.0,66,"abc");

  EXPECT_NO_THROW(t1>t2);
  EXPECT_TRUE(t1>t2);
}

TEST(operatorInferior,sameType){
  t::Tuple<int> t1(42);
  t::Tuple<int> t2(43);
  
  EXPECT_TRUE(t1<t2);
}

TEST(operatorInferior,differentTypesCompatible){
  t::Tuple<double> t1(42.0);
  t::Tuple<int> t2(43);

  EXPECT_TRUE((std::is_same<decltype(t1.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1<t2);
  EXPECT_TRUE(t1<t2);
}

TEST(operatorInferior,manyElementsCorrect){
  t::Tuple<double,int,std::string> t1(42.0,66,"abc");
  t::Tuple<double,int> t2(43.0,67,"def");

  EXPECT_NO_THROW(t1<t2);
  EXPECT_TRUE(t1<t2);
}

TEST(operatorSuperiorEqual,sameType){
  t::Tuple<int> t1(43);
  t::Tuple<int> t2(42);
  
  EXPECT_TRUE(t1>=t2);
}

TEST(operatorSuperiorEqual,differentTypesCompatible){
  t::Tuple<double> t1(43.0);
  t::Tuple<int> t2(42);

  EXPECT_TRUE((std::is_same<decltype(t1.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1>=t2);
  EXPECT_TRUE(t1>=t2);
}

TEST(operatorSuperiorEqual,manyElementsCorrect){
  t::Tuple<double,int,std::string> t1(43.0,66,"def");
  t::Tuple<double,int> t2(42.0,66,"abc");

  EXPECT_NO_THROW(t1>=t2);
  EXPECT_TRUE(t1>=t2);
}

TEST(operatorInferiorEqual,sameType){
  t::Tuple<int> t1(42);
  t::Tuple<int> t2(43);
  
  EXPECT_TRUE(t1<=t2);
}

TEST(operatorInferiorEqual,differentTypesCompatible){
  t::Tuple<double> t1(42.0);
  t::Tuple<int> t2(43);

  EXPECT_TRUE((std::is_same<decltype(t1.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1<=t2);
  EXPECT_TRUE(t1<=t2);
}

TEST(operatorInferiorEqual,manyElementsCorrect){
  t::Tuple<double,int,std::string> t1(42.0,66,"abc");
  t::Tuple<double,int> t2(43.0,66,"def");

  EXPECT_NO_THROW(t1<=t2);
  EXPECT_TRUE(t1<=t2);
}


/* Arithmetic operators */

TEST(operatorAddition,sameType){
  t::Tuple<int> t1(42);
  t::Tuple<int> t2(42);

  EXPECT_NO_THROW(t1+t2);
  EXPECT_EQ(t1.get<0>(),84);
}

TEST(operatorAddition,compatibleTypes){
  t::Tuple<int> t1(42);
  t::Tuple<double> t2(42.0);

  EXPECT_TRUE((std::is_same<decltype(t2.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1+t2);
  EXPECT_EQ(t1.get<0>(),84.0);
}

TEST(operatorAddition,manyElements){
  t::Tuple<int,double,std::string> t1(42,66.0,"abc");
  t::Tuple<int,double,std::string> t2(42,34.0,"def");

  EXPECT_NO_THROW(t1+t2);
  EXPECT_EQ(t1.get<0>(),84);
  EXPECT_EQ(t1.get<1>(),100.0);
  EXPECT_EQ(t1.get<2>(),"abcdef");
}

TEST(operatorSubstraction,sameType){
  t::Tuple<int> t1(42);
  t::Tuple<int> t2(42);

  EXPECT_NO_THROW(t1-t2);
  EXPECT_EQ(t1.get<0>(),84);
}

TEST(operatorSubstraction,compatibleTypes){
  t::Tuple<int> t1(42);
  t::Tuple<double> t2(42.0);

  EXPECT_TRUE((std::is_same<decltype(t2.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1-t2);
  EXPECT_EQ(t1.get<0>(),84.0);
}

TEST(operatorSubstraction,manyElements){
  t::Tuple<int,double> t1(42,66.0);
  t::Tuple<int,double> t2(42,34.0);

  EXPECT_NO_THROW(t1-t2);
  EXPECT_EQ(t1.get<0>(),0);
  EXPECT_EQ(t1.get<1>(),32.0);
}

TEST(operatorMultiplication,sameType){
  t::Tuple<int> t1(42);
  t::Tuple<int> t2(2);

  EXPECT_NO_THROW(t1*t2);
  EXPECT_EQ(t1.get<0>(),84);
}

TEST(operatorMultiplication,compatibleTypes){
  t::Tuple<int> t1(42);
  t::Tuple<double> t2(2.0);

  EXPECT_TRUE((std::is_same<decltype(t2.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1*t2);
  EXPECT_EQ(t1.get<0>(),84.0);
}

TEST(operatorMultiplication,manyElements){
  t::Tuple<int,double> t1(42,66.0);
  t::Tuple<int,double> t2(2,2);

  EXPECT_NO_THROW(t1-t2);
  EXPECT_EQ(t1.get<0>(),84);
  EXPECT_EQ(t1.get<1>(),132);
}

TEST(operatorDivision,sameType){
  t::Tuple<int> t1(42);
  t::Tuple<int> t2(2);

  EXPECT_NO_THROW(t1/t2);
  EXPECT_EQ(t1.get<0>(),21);
}

TEST(operatorDivision,compatibleTypes){
  t::Tuple<int> t1(42);
  t::Tuple<double> t2(2.0);

  EXPECT_TRUE((std::is_same<decltype(t2.get<0>()),double>::value) );
  EXPECT_NO_THROW(t1/t2);
  EXPECT_EQ(t1.get<0>(),21.0);
}

TEST(operatorDivision,manyElements){
  t::Tuple<int,double> t1(21,66.0);
  t::Tuple<int,double> t2(2,2);

  EXPECT_NO_THROW(t1-t2);
  EXPECT_EQ(t1.get<0>(),21);
  EXPECT_EQ(t1.get<1>(),33);
}

TEST(concatenation,twoStrings){
  t::Tuple<std::string> t1("it's");
  t::Tuple<std::string> t2("working");
  
  auto t3 = std::move(t1) | std::move(t2);

  EXPECT_EQ(t3.get<0>(),"it's");
  EXPECT_EQ(t3.get<1>(),"working");
}

TEST(concatenation,manyElements){
  t::Tuple<int,std::size_t,std::string> t1(-42,66u,"it's");
  t::Tuple<double,unsigned int,std::string> t2(420.0,99u,"working");
  
  auto t3 = std::move(t1) | std::move(t2);

  EXPECT_EQ(t3.get<0>(),-42);
  EXPECT_EQ(t3.get<1>(),66u);
  EXPECT_EQ(t3.get<2>(),"it's");
  EXPECT_EQ(t3.get<3>(),420);
  EXPECT_EQ(t3.get<4>(),99u);
  EXPECT_EQ(t3.get<5>(),"working");
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
