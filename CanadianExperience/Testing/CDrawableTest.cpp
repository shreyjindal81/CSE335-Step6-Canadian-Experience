#include "pch.h"
#include "CppUnitTest.h"
#include "Drawable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	class CDrawableMock : public CDrawable
	{
	public:
		CDrawableMock(std::wstring name) :CDrawable(name) {};
		virtual bool HitTest(Gdiplus::Point pos) { return true; };
		virtual void Draw(Gdiplus::Graphics* graphics) {};
	};
	TEST_CLASS(CDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestItitialiseAndGetter)
		{
			CDrawableMock drawable(L"Test");
			Assert::IsTrue(drawable.GetName() == L"Test");
		}

		TEST_METHOD(TestRotation)
		{
			CDrawableMock drawable(L"Test");
			Assert::IsTrue(drawable.GetRotation()==0);
			drawable.SetRotation(40.5);
			Assert::AreEqual(40.5, drawable.GetRotation(), 0.000001);
		}

		TEST_METHOD(TestPosition)
		{
			CDrawableMock drawable(L"Test");
			Assert::AreEqual(0, drawable.GetPosition().X);
			Assert::AreEqual(0, drawable.GetPosition().Y);
			drawable.SetPosition(Gdiplus::Point(20, 30));
			Assert::AreEqual(20, drawable.GetPosition().X);
			Assert::AreEqual(30, drawable.GetPosition().Y);
		}

		TEST_METHOD(TestCDrawableAssociation)
		{
			CDrawableMock body(L"Body");
			auto arm = std::make_shared<CDrawableMock>(L"Arm");
			auto leg = std::make_shared<CDrawableMock>(L"Leg");

			Assert::IsNull(arm->GetParent());
			Assert::IsNull(leg->GetParent());

			body.AddChild(arm);
			body.AddChild(leg);

			Assert::IsTrue(arm->GetParent() == &body);
			Assert::IsTrue(leg->GetParent() == &body);
		}
	};
}