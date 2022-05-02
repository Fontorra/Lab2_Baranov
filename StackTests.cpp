#include "pch.h"
#include "CppUnitTest.h"
#include "..\LAB2\Stack.h"
#include "..\LAB2\SomeClasses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int FunctionMap(int item) {
	return item * item;
}

bool FunctionWhereFirst(double item) {
	if (item > 5.4) return true;
	else return false;
}

bool FunctionWhereSecond(double item) {
	return false;
}

int FunctionReduce(int item, int c) {
	return item + c;
}

namespace StackTests
{
	TEST_CLASS(StackTests)
	{
	public:
		TEST_METHOD(MapTest) {
			int* Array = new int[10];
			for (int i = 0; i < 10; i++) Array[i] = i;
			Stack<int> StackArray(Array, 10, 1);
			StackArray.Map(&FunctionMap);
			for (int i = 0; i < 10; i++) {
				Assert::IsTrue(StackArray.Pop() == i * i);
			}
			Stack<int> StackList(Array, 10, 2);
			StackList.Map(&FunctionMap);
			for (int i = 0; i < 10; i++) {
				Assert::IsTrue(StackList.Pop() == i * i);
			}
		}
		TEST_METHOD(WhereTest) {
			double* Array = new double[10];
			for (int i = 0; i < 10; i++) Array[i] = i + 0.5;
			Stack<double> StackArray(Array, 10, 1);
			Stack<double> newArray = *StackArray.Where(&FunctionWhereFirst);
			double item = 5.5;
			while (!newArray.isEmpty()) {
				Assert::IsTrue(newArray.Pop() == item);
				item++;
			}
			Stack<double> StackList(Array, 10, 2);
			Stack<double> newList = *StackList.Where(&FunctionWhereFirst);
			Assert::IsTrue(newList.isEmpty());
			Stack<double> voidStack(0, 2);
		}

		TEST_METHOD(ReduceTest) {
			int* Array = new int[10];
			for (int i = 0; i < 10; i++) Array[i] = i;
			Stack<int> StackArray(Array, 10, 1);
			int result = StackArray.Reduce(&FunctionReduce, 0);
			Assert::IsTrue(result == 45);
			Stack<int> StackList(Array, 10, 2);
			result = StackArray.Reduce(&FunctionReduce, 10);
			Assert::IsTrue(result == 55);
		}

		TEST_METHOD(FindSubSequenceTest) {
			int* Array = new int[10];
			for (int i = 0; i < 10; i++) Array[i] = 2 * i + 1;
			int* firstArray = new int[3];
			firstArray[0] = 3;
			firstArray[1] = 5;
			firstArray[2] = 17;
			int* secondArray = new int[3];
			secondArray[0] = 5;
			secondArray[1] = 8;
			secondArray[2] = 13;
			int* thirdArray = new int;
			Stack<int> stack(Array, 10, 1);
			Stack<int> firstStack(firstArray, 3, 1);
			Stack<int> secondStack(secondArray, 3, 1);
			Stack<int> thirdStack(thirdArray, 0, 1);
			Assert::IsTrue(stack.FindSubSequence(&firstStack));
			Assert::IsFalse(stack.FindSubSequence(&secondStack));
			Assert::IsTrue(stack.FindSubSequence(&thirdStack));
		}

		TEST_METHOD(TowerOfHanoiTest) {
			int* Array = new int[10];
			for (int i = 0; i < 10; i++) Array[i] = i;
			Stack<int> StackArray(Array, 10, 1);
			Stack<int> ExcpectedResult(StackArray);
			Stack<int> StackResult;
			Stack<int> StackBuffer;
			TowerOfHanoi(&StackArray, &StackResult, &StackBuffer);
			Assert::IsTrue(StackResult == ExcpectedResult);
			for (int i = 0; i < 10; i++) Array[i] = i + 5;
			Stack<int> StackArraynew(Array, 5, 1);
			Stack<int> StackResultnew;
			Stack<int> StackBuffernew;
			Stack<int> ExcpectedResultnew(StackArraynew);
			TowerOfHanoi(&StackArraynew, &StackResultnew, &StackBuffernew);
			Assert::IsTrue(StackResultnew == ExcpectedResultnew);

		}
	};
}
