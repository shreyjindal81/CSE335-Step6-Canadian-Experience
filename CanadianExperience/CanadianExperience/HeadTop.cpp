///class that creates top of head
/// filename "HeadTop.cpp"
/// author Shrey Jindal
#include "pch.h"
#include "HeadTop.h"
#include "Timeline.h"
#include "Actor.h"

using namespace std; using namespace Gdiplus;
/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;
CHeadTop::CHeadTop(const std::wstring& name, const std::wstring& filename) : CImageDrawable(name, filename)
{

}

void CHeadTop::Draw(Gdiplus::Graphics* graphics)
{
    auto state = graphics->Save();
    graphics->TranslateTransform((float)mPlacedPosition.X, (float)mPlacedPosition.Y);
    graphics->RotateTransform((float)(-mPlacedR * RtoD));
    graphics->DrawImage(mImage.get(), -GetCenter().X, -GetCenter().Y,
        mImage->GetWidth(), mImage->GetHeight());
    graphics->Restore(state);

    state = graphics->Save();
    auto p1 = TransformPoint(Point(40, 60));
    auto p2 = TransformPoint(Point(20, 65));
    Pen eyebrowPen(Color::Black, 4);
    graphics->DrawLine(&eyebrowPen, p1, p2);
    graphics->Restore(state);

    state = graphics->Save();
    p1 = TransformPoint(Point(67, 60));
    p2 = TransformPoint(Point(87, 65));
    graphics->DrawLine(&eyebrowPen, p1, p2);
    graphics->Restore(state);

    float wid = 15.0f;
    float hit = 20.0f;
    SolidBrush brush(Color::Black);
    SolidBrush brushw(Color::AliceBlue);
    state = graphics->Save();
    p1 = TransformPoint(Point(35,80));
    graphics->TranslateTransform(Gdiplus::REAL(p1.X), Gdiplus::REAL(p1.Y));
    graphics->RotateTransform((float)(-mPlacedR * RtoD));
    graphics->FillEllipse(&brush, -wid / 2, -hit / 2, wid, hit);
    graphics->FillEllipse(&brushw, -10 / 2, -10 / 2, 10, 10);
    graphics->Restore(state);

    state = graphics->Save();
    p1 = TransformPoint(Point(72, 80));
    graphics->TranslateTransform(Gdiplus::REAL(p1.X), Gdiplus::REAL(p1.Y));
    graphics->RotateTransform((float)(-mPlacedR * RtoD));
    graphics->FillEllipse(&brush, -wid / 2, -hit / 2, wid, hit);
    graphics->FillEllipse(&brushw, -10 / 2, -10 / 2, 10, 10);
    graphics->Restore(state);
}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param  p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}


 
void CHeadTop::SetActor(CActor* actor)
{
    CImageDrawable::SetActor(actor);

    // Set the channel name
    mPChannel.SetName(actor->GetName() + L":" + GetName() + L":position");

}


 
void CHeadTop::SetTimeline(CTimeline* timeline)
{
    CImageDrawable::SetTimeline(timeline);

    timeline->AddChannel(&mPChannel);
}


 
void CHeadTop::SetKeyframe()
{
    CImageDrawable::SetKeyframe();
    mPChannel.SetKeyframe(GetPosition());
}

 
void CHeadTop::GetKeyframe()
{
    CImageDrawable::GetKeyframe();
    if (mPChannel.IsValid())
        SetPosition(mPChannel.GetPoint());
}

