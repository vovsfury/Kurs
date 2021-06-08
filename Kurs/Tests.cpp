#include "pch.h"
#include <fstream>
#include "CppUnitTest.h"
#include "..\Kurs\Edmonds-Karp.cpp"
#include "..\Kurs\Graph.cpp"
#include "..\Kurs\List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestCourseWork
{
	TEST_CLASS(EdmondsKarpTest)
	{
	public:
		TEST_METHOD(SearchUniqueVertexesTest)
		{
			ifstream read("..\\Kurs\\test1.txt");
			if (!read.is_open())
				return;
			int VertexesNumber = 0;
			string UniqueVertexes = "";
			SearchUniqueVertexes(UniqueVertexes, VertexesNumber, read);
			VertexesNumber = VertexesNumber - 1;
			char* Vertexes = new char[VertexesNumber];
			for (int k = 0; k < VertexesNumber; ++k)
				Vertexes[k] = UniqueVertexes[k];
			read.close();
			Assert::IsTrue(Vertexes[0] == 'S');
			Assert::IsTrue(Vertexes[1] == 'O');
			Assert::IsTrue(Vertexes[2] == 'P');
			Assert::IsTrue(Vertexes[3] == 'Q');
			Assert::IsTrue(Vertexes[4] == 'R');
			Assert::IsTrue(Vertexes[5] == 'T');
			Assert::IsTrue(VertexesNumber == 6);
			delete[] Vertexes;
		}
		TEST_METHOD(EdmondsKarpTest_1)
		{
			ifstream read("..\\Kurs\\test1.txt");
			if (!read.is_open())
				return;
			unsigned MaxFlow = 0;
			Process(MaxFlow, read);
			read.close();
			Assert::IsTrue(MaxFlow == 5);
		}
		TEST_METHOD(EdmondsKarpTest_2)
		{
			ifstream read("..\\Kurs\\test2.txt");
			if (!read.is_open())
				return;
			unsigned MaxFlow = 0;
			Process(MaxFlow, read);
			read.close();
			Assert::IsTrue(MaxFlow == 14);
		}
	};
	TEST_CLASS(GraphTest)
	{
	public:

		TEST_METHOD(GetValueTest)
		{
			int dim = 3;
			Graph Test(dim);
			Assert::IsTrue(Test.GetValue(0, 1) == 0);
		}
		TEST_METHOD(SetValueTest)
		{
			int dim = 3;
			Graph Test(dim);
			Test.SetValue(2, 2, 5);
			Assert::IsTrue(Test.GetValue(2, 2) == 5);
		}
		TEST_METHOD(BFSTest)
		{
			int dim = 3;
			Graph* Test = new Graph(dim);
			Graph* Flow = new Graph(3);
			Test->SetValue(0, 1, 1);
			Test->SetValue(0, 2, 1);
			Test->SetValue(1, 2, 1);
			Assert::IsTrue(Test->BFS(*Flow)->at(0) == 0);
			Assert::IsTrue(Test->BFS(*Flow)->at(1) == 2);
		}
	};
}
