///class that creates top of head
/// filename "HeadTop.h"
/// author Shrey Jindal
#pragma once
#include "ImageDrawable.h"
#include "AnimChannelPoint.h"

using namespace std;
using namespace Gdiplus;

///Class that creates top of head
class CHeadTop :
    public CImageDrawable
{
public:
    CHeadTop(const std::wstring& name, const std::wstring& filename);
    virtual bool IsMovable() { return true; }
    virtual void Draw(Gdiplus::Graphics* graphics) override;

    Gdiplus::Point TransformPoint(Gdiplus::Point p);

    virtual void SetActor(CActor* actor) override;

    virtual void SetTimeline(CTimeline* timeline) override;

    virtual void SetKeyframe() override;

    virtual void GetKeyframe() override;

    CAnimChannelPoint mPChannel;
};

