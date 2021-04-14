#include "pch.h"
#include "CppUnitTest.h"
#include "PictureObserver.h"
#include "Picture.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	class CPictureObserverMock : public CPictureObserver
	{
	public:
		CPictureObserverMock() : CPictureObserver() {}
		//virtual void UpdateObserver() override {}
		bool mUpdated = false;
		virtual void UpdateObserver() override { mUpdated = true; }
	};
	TEST_CLASS(CPictureObserverTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCPictureObserverOneObserver)
		{
			// Allocate a CPicture object
			std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer.mUpdated);
		}
		TEST_METHOD(TestCPictureObserverGetPicture)
		{
			// Allocate a CPicture object
			std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			Assert::IsTrue(observer.GetPicture()==nullptr);
			// And set it for the observer:
			observer.SetPicture(picture);
			Assert::IsTrue(observer.GetPicture() == picture);
			
		}

		TEST_METHOD(TestCPictureObserverMultipleTest)
		{
			// Allocate a CPicture object
			std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();
			// Create a mock observer object
			CPictureObserverMock observer1;
			CPictureObserverMock observer2;

			// And set it for the observer:
			observer1.SetPicture(picture);
			observer2.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);
			Assert::IsTrue(observer2.mUpdated);

		}

		TEST_METHOD(TestCPictureObserverMultipleRemoveTest)
		{
			// Allocate a CPicture object
			std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();
			// Create a mock observer object
			CPictureObserverMock observer1;

			// And set it for the observer:
			observer1.SetPicture(picture);

			{
				CPictureObserverMock observer2;
				observer2.SetPicture(picture);
			}
			
			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);


		}
	};
}