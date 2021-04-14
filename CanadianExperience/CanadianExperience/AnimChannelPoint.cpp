#include "pch.h"
#include "AnimChannelPoint.h"
#include "Timeline.h"

using namespace std;
using namespace Gdiplus;


 
CAnimChannelPoint::CAnimChannelPoint()
{
}

 
CAnimChannelPoint::~CAnimChannelPoint()
{
}
 
void CAnimChannelPoint::SetKeyframe(Gdiplus::Point point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    shared_ptr<KeyframePoint> keyframe = make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}
 
void CAnimChannelPoint::Tween(double t)
{
    Point x = mKeyframe1->GetPoint();
    Point y = mKeyframe2->GetPoint();

    mPoint = Point(int(x.X + t * (y.X - x.X)), int(x.Y + t * (y.Y - x.Y)));
}
    