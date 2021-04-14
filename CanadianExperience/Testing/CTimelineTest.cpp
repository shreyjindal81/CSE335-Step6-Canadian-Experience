
#include "pch.h"
#include "CppUnitTest.h"
#include "Timeline.h"
#include "AnimChannel.h"
#include "AnimChannelAngle.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNumFramesGetterSetterInitial)
		{
			CTimeline timeline;
			Assert::AreEqual(timeline.GetNumFrames(), 300);
			timeline.SetNumFrames(400);
			Assert::AreEqual(timeline.GetNumFrames(), 400);
		}

		TEST_METHOD(TestFramerateGetterSetterInitial)
		{
			CTimeline timeline;
			Assert::AreEqual(timeline.GetFrameRate(), 30);
			timeline.SetFrameRate(400);
			Assert::AreEqual(timeline.GetFrameRate(), 400);
		}

		TEST_METHOD(TestCurrentTimeGetterSetterInitial)
		{
			CTimeline timeline;
			Assert::AreEqual(timeline.GetCurrentTime(), 0.0);
			timeline.SetCurrentTime(400);
			Assert::AreEqual(timeline.GetCurrentTime(), 400.0);
		}

		TEST_METHOD(TestCTimelineAdd)
		{
			CTimeline timeline;
			CAnimChannelAngle channel;

			timeline.AddChannel(&channel);
			Assert::IsTrue(&timeline == channel.GetTimeline());
		}
	};
}