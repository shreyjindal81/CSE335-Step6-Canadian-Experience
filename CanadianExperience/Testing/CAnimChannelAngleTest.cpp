#include "pch.h"
#include "CppUnitTest.h"
#include "AnimChannel.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CAnimChannelAngleTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNameAndAngle)
		{
			CAnimChannelAngle a;
			a.SetAngle(10.9);
			a.SetName(L"test");
			std::wstring b = L"test";
			Assert::AreEqual(a.GetAngle(), 10.9, 0.00001);
			Assert::AreEqual(a.GetName(), b);
		}

	};
}