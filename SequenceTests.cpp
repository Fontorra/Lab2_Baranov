#include "pch.h"
#include "CppUnitTest.h"
#include "..\LAB2\DynamicArraySequence.h"
#include "..\LAB2\Sequence.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SequenceTests
{
	TEST_CLASS(DynamicArraySequenceTests)
	{
	public:
		
		TEST_METHOD(ConstructorTests)
		{
			DynamicArraySequence<int> Sequence1;
			Assert::IsTrue(Sequence1.GetLength() == 0);
			DynamicArraySequence<int> Sequence2(10);
			Assert::IsTrue(Sequence2.GetLength() == 10);
			for (int i = 0; i < 10; i++) {
				Assert::IsTrue(Sequence2[i] == 0);
			}
			char* charArray = new char[5];
			for (int i = 0; i < 5; i++) {
				charArray[i] = i + 56;
			}
			DynamicArraySequence<char> Sequence3(charArray, 5);
			Assert::IsTrue(Sequence3.GetLength() == 5);
			for (int i = 0; i < 5; i++) {
				Assert::IsTrue(Sequence3[i] == i + 56);
			}

			DynamicArraySequence<char> copySequence3(Sequence3);
			Assert::IsTrue(&Sequence3 != &copySequence3);
			Assert::IsTrue(copySequence3 == Sequence3);
			delete[] charArray;
		}
		TEST_METHOD(Operators)
		{
			int* intList = new int[15];
			for (int i = 0; i < 15; i++) {
				intList[i] = i;
			}
			DynamicArraySequence<int> sequence(intList, 15);
			DynamicArraySequence<int> newSequence(10);
			newSequence = sequence;
			Assert::IsFalse(&sequence == &newSequence);
			Assert::IsTrue(sequence == newSequence);
			newSequence[10] = 133;
			Assert::IsTrue(newSequence[10] == 133);
			newSequence[0] = -31;
			Assert::IsTrue(newSequence[0] == -31);
			newSequence[newSequence.GetLength() - 1] = 585;
			Assert::IsTrue(newSequence[newSequence.GetLength() - 1] == 585);

			try {
				newSequence[newSequence.GetLength()] = 0;
				Assert::Fail();
			}
			catch (exception ex) {}

			try {
				newSequence[-1] = 0;
				Assert::Fail();
			}
			catch (exception ex) {}

			DynamicArraySequence<int> List1(intList, 10);
			DynamicArraySequence<int> List2(intList, 10);
			Assert::IsTrue(List1 == List2);
			delete[] intList;
		}

		TEST_METHOD(Pop_Inserts_Gets_And_Sets)
		{
			DynamicArraySequence<double> sequence(20);
			sequence[5] = 10.5;
			Assert::IsTrue(sequence.Get(5) == 10.5);
			Assert::IsTrue(sequence.GetLength() == 20);
			sequence.InsertAt(5, 35.2);
			Assert::IsTrue(sequence.Get(5) == 35.2);
			Assert::IsTrue(sequence.GetLength() == 21);
			sequence.Append(-81.2);
			Assert::IsTrue(sequence.GetLast() == -81.2);
			Assert::IsTrue(sequence.GetLength() == 22);
			sequence.Prepend(0.9);
			Assert::IsTrue(sequence.GetFirst() == 0.9);
			Assert::IsTrue(sequence.GetLength() == 23);
			try {
				sequence.Get(44);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				sequence.Get(-5);
				Assert::Fail();
			}
			catch (exception ex) {}
			sequence.InsertAt(20, 500);
			Assert::IsTrue(sequence.Get(20) == 500);
			sequence.InsertAt(0, -0.5);
			Assert::IsTrue(sequence.Get(0) == -0.5);
			sequence.InsertAt(5, 13);
			try {
				sequence.InsertAt(-50, 1);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				sequence.InsertAt(sequence[sequence.GetLength() + 1], 50);
				Assert::Fail();
			}
			catch (exception ex) {}
			Assert::IsTrue(sequence.Get(5) == 13);
			Assert::IsTrue(sequence.GetLength() == 26);
			double trueElem = sequence[25];
			double elem = sequence.Pop(25);
			Assert::IsTrue(elem = trueElem);
			try {
				sequence.Pop(25);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				sequence.Pop(-1);
				Assert::Fail();
			}
			catch (exception ex) {}
			DynamicArraySequence<char> charSequence;
			try {
				charSequence.GetFirst();
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				charSequence.Get(0);
				Assert::Fail();
			}
			catch (exception ex) {}
			charSequence.InsertAt(0, 91);
			Assert::IsTrue(charSequence.GetFirst() == 91);
			Assert::IsTrue(charSequence.GetLength() == 1);
			char item = charSequence.Pop(0);
			Assert::IsTrue(item == 91);
			Assert::IsTrue(charSequence.GetLength() == 0);
			charSequence.Append(50);
			Assert::IsTrue(charSequence.GetFirst() == 50);
			charSequence.Pop(0);
			charSequence.Prepend(20);
			Assert::IsTrue(charSequence.GetFirst() == 20);
		}

		TEST_METHOD(GetSubSequence)
		{
			int* items = new int[20];
			for (int i = 0; i < 20; i++) items[i] = i + 10;
			DynamicArraySequence<int> sequence(items, 20);
			DynamicArraySequence<int> copySequence(sequence);
			DynamicArraySequence<int> newSequence = *(DynamicArraySequence<int>*)sequence.GetSubSequence(5, 10);
			Assert::IsTrue(newSequence.GetLength() == 6);
			Assert::IsTrue(sequence == copySequence);
			for (int i = 0; i < 6; i++) {
				Assert::IsTrue(newSequence[i] == sequence.Get(i + 5));
			}
			newSequence = *(DynamicArraySequence<int>*)sequence.GetSubSequence(0, sequence.GetLength() - 1);
			Assert::IsTrue(newSequence == sequence);
			try {
				newSequence = *(DynamicArraySequence<int>*)sequence.GetSubSequence(0, sequence.GetLength());
				Assert::Fail();
			}
			catch (exception ex) {}

			try {
				newSequence = *(DynamicArraySequence<int>*)sequence.GetSubSequence(-1, sequence.GetLength() - 1);
				Assert::Fail();
			}
			catch (exception ex) {}
			try {
				newSequence = *(DynamicArraySequence<int>*)sequence.GetSubSequence(100, sequence.GetLength() - 1);
				Assert::Fail();
			}
			catch (exception ex) {}
			newSequence = *(DynamicArraySequence<int>*)
				sequence.GetSubSequence(sequence.GetLength() - 1, 
				sequence.GetLength() - 5);
			Assert::IsTrue(newSequence.GetLength() == 0);
			newSequence = *(DynamicArraySequence<int>*)sequence.GetSubSequence(6, 6);
			Assert::IsTrue(newSequence.GetLength() == 1);
			Assert::IsTrue(newSequence.Get(0) == 16);
			DynamicArraySequence<int> SecondSequence;
			try {
				newSequence = *(DynamicArraySequence<int>*)SecondSequence.GetSubSequence(0, 0);
				Assert::Fail();
			}
			catch (exception ex) {}
			delete[] items;
		}
		TEST_METHOD(Concat)
		{
			int* items = new int[20];
			for (int i = 0; i < 20; i++) items[i] = i;
			DynamicArraySequence<int> FirstSequence(items, 20);
			DynamicArraySequence<int> sequence(items, 20);
			for (int i = 0; i < 5; i++) {
				items[i] = i + 10;
				sequence.Append(i + 10);
			}
			DynamicArraySequence<int> SecondSequence(items, 5);
			DynamicArraySequence<int> ResultSequence = *(DynamicArraySequence<int>*)FirstSequence.Concat(&SecondSequence);
			Assert::IsTrue(ResultSequence == sequence);
			Assert::IsTrue(ResultSequence.GetLength() == 25);
			DynamicArraySequence<int> voidSequence;
			ResultSequence = *(DynamicArraySequence<int>*)FirstSequence.Concat(&voidSequence);
			Assert::IsTrue(ResultSequence == FirstSequence);
			ResultSequence = *(DynamicArraySequence<int>*)FirstSequence.Concat(&FirstSequence);
			for (int i = 0; i < 20; i++) {
				Assert::IsTrue(ResultSequence[i] == i);
			}
			for (int i = 20; i < 40; i++) {
				Assert::IsTrue(ResultSequence[i] == i - 20);
			}
			Assert::IsTrue(ResultSequence.GetLength() == 40);
			ResultSequence = *(DynamicArraySequence<int>*)voidSequence.Concat(&voidSequence);
			Assert::IsTrue(ResultSequence == voidSequence);
		}
	};
}
