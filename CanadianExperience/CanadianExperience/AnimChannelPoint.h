#pragma once
#include "AnimChannel.h"

class CAnimChannelPoint :
    public CAnimChannel
{
public:
    CAnimChannelPoint();
    ~CAnimChannelPoint();

    Gdiplus::Point GetPoint() { return mPoint; }

    class KeyframePoint : public Keyframe
    {
    public:
        KeyframePoint(CAnimChannelPoint* channel, Gdiplus::Point point) :
            Keyframe(channel), mChannel(channel), mPoint(point) {}

        KeyframePoint() = delete;
        KeyframePoint(const KeyframePoint&) = delete;
        void operator=(const KeyframePoint&) = delete;

        Gdiplus::Point GetPoint() { return mPoint; }

        virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

        virtual void UseOnly() override { mChannel->mPoint = mPoint; }

        virtual void UseAs2() override { mChannel->mKeyframe2 = this; }



    private:
        Gdiplus::Point mPoint = Gdiplus::Point(0, 0);

        CAnimChannelPoint* mChannel;
    };

    void SetKeyframe(Gdiplus::Point point);
    void Tween(double t);

private:
    Gdiplus::Point mPoint = Gdiplus::Point(0, 0);

    KeyframePoint* mKeyframe1 = nullptr;

    KeyframePoint* mKeyframe2 = nullptr;
};

