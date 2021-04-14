/*
* the timeline class
*
* filename 'Timeline.cpp'
*
* author Shrey Jindal
*
*/
#include "pch.h"
#include "Timeline.h"

/// destructor
CTimeline::~CTimeline()
{
}

/**
 * Constructor
 */
CTimeline::CTimeline()
{
}

void CTimeline::AddChannel(CAnimChannel* c)
{
	mChannels.push_back(c);
	c->SetTimeline(this);
}

/** Sets the current time
*
* Ensures all of the channels are
* valid for that point in time.
*/
void CTimeline::SetCurrentTime(double c)
{
    // Set the time
    mCurrentTime = c;

    for (auto i : mChannels)
    {
        i->SetFrame(GetCurrentFrame());
    }
}

void CTimeline::RemoveKeyframe()
{
    for (auto i : mChannels)
    {
        i->RemoveKeyframe();
    }
}