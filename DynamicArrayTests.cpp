#include "pch.h"
#include "CppUnitTest.h"
#include "..\LAB2\DynamicArray.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DynamicArrayTests
{
	TEST_CLASS(DynamicArrayTests)
	{
	public:
		TEST_METHOD(ConstructorTests)
		{
			DynamicArray<int> Array1;
			Assert::IsTrue(Array1.GetSize() == 0);
			DynamicArray<int> Array2(10);
			Assert::IsTrue(Array2.GetSize() == 10);
			for (int i = 0; i < 10; i++) {
				Assert::IsTrue(Array2[i] == 0);
			}
			char* charArray = new char[5];
			for (int i = 0; i < 5; i++) {
				charArray[i] = i + 90;
			}
			DynamicArray<char> Array3(charArray, 5);
			Assert::IsTrue(Array3.GetSize() == 5);
			for (int i = 0; i < 5; i++) {
				Assert::IsTrue(Array3[i] == i + 90);
			}

			DynamicArray<char> copyArray3(Array3);
			Assert::IsTrue(&Array3 != &copyArray3);
			Assert::IsTrue(copyArray3 == Array3);
			delete[] charArray;
		}
		TEST_METHOD(Operators)
		{
			int* intArray = new int[15];
			for (int i = 0; i < 15; i++) {
				intArray[i] = i;
			}
			DynamicArray<int> Array(intArray, 15);
			DynamicArray<int> newArray(10);
			newArray = Array;
			Assert::IsFalse(&Array == &newArray);
			Assert::IsTrue(Array == newArray);
			newArray[10] = 29;
			Assert::IsTrue(newArray[10] == 29);
			try {
				newArray[20] = 0;
				Assert::Fail();
			}
			catch (exception ex) {}
			DynamicArray<int> Array1(intArray, 10);
			DynamicArray<int> Array2(intArray, 10);
			Assert::IsTrue(Array1 == Array2);
			delete[] intArray;
		}

		TEST_METHOD(Insert_Get_And_Sets) 
		{
			DynamicArray<double> Array(20);
			Array.Set(19, 150);
			Assert::IsTrue(Array.Get(19) == 150);
			Array.Set(0, -20);
			Assert::IsTrue(Array.Get(0) == -20);
			Array.Set(5, 10.5);
			Assert::IsTrue(Array.Get(5) == 10.5);
			Assert::IsTrue(Array.GetSize() == 20);
			try {
				Array.Set(Array.GetSize(), 1111);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				Array.Set(-5, 1111);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				Array.Get(44);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				Array.Get(-5);
				Assert::Fail();
			}
			catch (exception ex) {}
			Array.InsertAt(20, 500);
			Assert::IsTrue(Array.Get(20) == 500);
			Array.InsertAt(0, -0.5);
			Assert::IsTrue(Array.Get(0) == -0.5);
			Array.InsertAt(5, 13);
			try {
				Array.InsertAt(-50, 1);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				Array.InsertAt(Array[Array.GetSize() + 1], 50);
				Assert::Fail();
			}
			catch (exception ex) {}
			Assert::IsTrue(Array.Get(5) == 13);
			Assert::IsTrue(Array.GetSize() == 23);
		}
		TEST_METHOD(Pop_And_Resize) 
		{
			int* intArray = new int[15];
			for (int i = 0; i < 15; i++) {
				intArray[i] = i;
			}
			DynamicArray<int> Array(intArray, 10);
			int value = Array.Pop(9);
			Assert::IsTrue(value == 9);
			Array.Set(0, 123);
			value = Array.Pop(0);
			Assert::IsTrue(value == 123);
			Array.Set(5, -25);
			value = Array.Pop(5);
			Assert::IsTrue(value == -25);
			Assert::IsTrue(Array.GetSize() == 7);
			try {
				Array.Pop(Array.GetSize());
				Assert::Fail();
			}
			catch (exception ex) {}

			try {
				Array.Pop(-1);
				Assert::Fail();
			}
			catch (exception ex) {}
			Array.Resize(50);
			Assert::IsTrue(Array.GetSize() == 50);
			Assert::IsTrue(Array[40] == 0);
			Array.Resize(0);
			Assert::IsTrue(Array.GetSize() == 0);
			try {
				int a = Array[0];
				Assert::Fail();
			}
			catch (exception ex) {};
			delete[] intArray;
		}
	};
}
