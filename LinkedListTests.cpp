#include "pch.h"
#include "CppUnitTest.h"
#include "..\LAB2\LinkedList.h"
#include "..\LAB2\SomeClasses.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTests
{
	TEST_CLASS(LinkedListTests)
	{
	public:
		TEST_METHOD(ConstructorTests)
		{
			LinkedList<int> List1;
			Assert::IsTrue(List1.GetLength() == 0);
			LinkedList<int> List2(10);
			Assert::IsTrue(List2.GetLength() == 10);
			for (int i = 0; i < 10; i++) {
				Assert::IsTrue(List2[i] == 0);
			}
			LinkedList<Complex> *complexList = new LinkedList<Complex>(5);
			complexList->Set(0, Complex(1, 2));
			complexList->Set(1, Complex(2, 4));
			complexList->Set(2, Complex(3, 6));
			complexList->Set(3, Complex(4, 8));
			complexList->Set(4, Complex(5, 10));
			Assert::IsTrue(complexList->GetLength() == 5);
			for (int i = 0; i < 5; i++) {
				Assert::IsTrue(complexList->Get(i) == Complex(i + 1, 2 * (i + 1)));
			}

			LinkedList<Complex> copyComplexList(*complexList);
			Assert::IsTrue(complexList != &copyComplexList);
			Assert::IsTrue(copyComplexList == *complexList);
		}
		TEST_METHOD(Operators)
		{
			int* intList = new int[15];
			for (int i = 0; i < 15; i++) {
				intList[i] = i;
			}
			LinkedList<int> List(intList, 15);
			LinkedList<int> newList(10);
			newList = List;
			Assert::IsFalse(&List == &newList);
			Assert::IsTrue(List == newList);
			newList[10] = 133;
			Assert::IsTrue(newList[10] == 133);
			newList[0] = -31;
			Assert::IsTrue(newList[0] == -31);
			newList[newList.GetLength() - 1] = 585;
			Assert::IsTrue(newList[newList.GetLength() - 1] == 585);

			try {
				newList[newList.GetLength()] = 0;
				Assert::Fail();
			}
			catch (exception ex) {}

			try {
				newList[-1] = 0;
				Assert::Fail();
			}
			catch (exception ex) {}

			LinkedList<int> List1(intList, 10);
			LinkedList<int> List2(intList, 10);
			Assert::IsTrue(List1 == List2);
			delete[] intList;
		}

		TEST_METHOD(Pop_Inserts_Gets_And_Sets) 
		{
			LinkedList<double> List(20);
			List.Set(19, 150);
			Assert::IsTrue(List.GetLast() == 150);
			List.Set(0, -20);
			Assert::IsTrue(List.GetFirst() == -20);
			List.Set(5, 10.5);
			Assert::IsTrue(List.Get(5) == 10.5);
			Assert::IsTrue(List.GetLength() == 20);
			List.InsertAt(5, 35.2);
			Assert::IsTrue(List.Get(5) == 35.2);
			Assert::IsTrue(List.GetLength() == 21);
			List.Append(-81.2);
			Assert::IsTrue(List.GetLast() == -81.2);
			Assert::IsTrue(List.GetLength() == 22);
			List.Prepend(0.9);
			Assert::IsTrue(List.GetFirst() == 0.9);
			Assert::IsTrue(List.GetLength() == 23);
			try {
				List.Set(List.GetLength(), 1111);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				List.Set(-5, 1111);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				List.Get(44);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				List.Get(-5);
				Assert::Fail();
			}
			catch (exception ex) {}
			List.InsertAt(20, 500);
			Assert::IsTrue(List.Get(20) == 500);
			List.InsertAt(0, -0.5);
			Assert::IsTrue(List.Get(0) == -0.5);
			List.InsertAt(5, 13);
			try {
				List.InsertAt(-50, 1);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				List.InsertAt(List[List.GetLength() + 1], 50);
				Assert::Fail();
			}
			catch (exception ex) {}
			Assert::IsTrue(List.Get(5) == 13);
			Assert::IsTrue(List.GetLength() == 26);
			double trueElem = List[25];
			double elem = List.Pop(25);
			Assert::IsTrue(elem = trueElem);
			try {
				List.Pop(25);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				List.Pop(-1);
				Assert::Fail();
			}
			catch (exception ex) {}
			LinkedList<char> charList;
			try {
				charList.GetFirst();
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				charList.Get(0);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				charList.Set(0, 1);
				Assert::Fail();
			}
			catch (exception ex) {}
			charList.InsertAt(0, 91);
			Assert::IsTrue(charList.GetFirst() == 91);
			Assert::IsTrue(charList.GetLength() == 1);
			char item = charList.Pop(0);
			Assert::IsTrue(item == 91);
			Assert::IsTrue(charList.GetLength() == 0);
			charList.Append(50);
			Assert::IsTrue(charList.GetFirst() == 50);
			charList.Pop(0);
			charList.Prepend(20);
			Assert::IsTrue(charList.GetFirst() == 20);
		}

		TEST_METHOD(GetSubList) 
		{
			int* items = new int[20];
			for (int i = 0; i < 20; i++) items[i] = i + 10;
			LinkedList<int> List(items, 20);
			LinkedList<int> copyList(List);
			LinkedList<int> newList = *List.GetSubList(5, 10);
			Assert::IsTrue(newList.GetLength() == 6);
			Assert::IsTrue(List == copyList);
			for (int i = 0; i < 6; i++) {
				Assert::IsTrue(newList[i] == List.Get(i + 5));
			}
			newList = *List.GetSubList(0, List.GetLength() - 1);
			Assert::IsTrue(newList == List);
			try {
				newList = *List.GetSubList(0, List.GetLength());
				Assert::Fail();
			}
			catch (exception ex) {}
			
			try {
				newList = *List.GetSubList(-1, List.GetLength() - 1);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				newList = *List.GetSubList(100, List.GetLength() - 1);
				Assert::Fail();
			}
			catch (exception ex) {}
			newList = *List.GetSubList(List.GetLength() - 1, List.GetLength() - 5);
			Assert::IsTrue(newList.GetLength() == 0);
			newList = *List.GetSubList(6, 6);
			Assert::IsTrue(newList.GetLength() == 1);
			Assert::IsTrue(newList.Get(0) == 16);
			LinkedList<int> SecondList;
			try {
				newList = *SecondList.GetSubList(0, 0);
				Assert::Fail();
			}
			catch (exception ex) {}
			delete[] items;
		}
		TEST_METHOD(Concat)
		{
			int* items = new int[20];
			for (int i = 0; i < 20; i++) items[i] = i;
			LinkedList<int> FirstList(items, 20);
			LinkedList<int> List(items, 20);
			for (int i = 0; i < 5; i++) {
				items[i] = i + 10;
				List.Append(i + 10);
			}
			LinkedList<int> SecondList(items, 5);
			LinkedList<int> ResultList = *FirstList.Concat(&SecondList);
			Assert::IsTrue(ResultList == List);
			Assert::IsTrue(ResultList.GetLength() == 25);
			LinkedList<int> voidList;
			ResultList = *FirstList.Concat(&voidList);
			Assert::IsTrue(ResultList == FirstList);
			ResultList = *FirstList.Concat(&FirstList);
			for (int i = 0; i < 20; i++) {
				Assert::IsTrue(ResultList[i] == i);
			}
			for (int i = 20; i < 40; i++) {
				Assert::IsTrue(ResultList[i] == i - 20);
			}
			Assert::IsTrue(ResultList.GetLength() == 40);
			ResultList = *voidList.Concat(&voidList);
			Assert::IsTrue(ResultList == voidList);
		}
	};
}
