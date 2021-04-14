#pragma once
#include "Drawable.h"
#include <memory>

using namespace std; using namespace Gdiplus;
///drawables that are an iamge
class CImageDrawable :
    public CDrawable
{
public:
    CImageDrawable(const std::wstring& name, const std::wstring& filename);

    virtual void Draw(Gdiplus::Graphics* graphics);

    virtual bool HitTest(Gdiplus::Point pos);

    virtual void SetCenter(Point point) { mCenter = point; }

    virtual Point GetCenter() { return mCenter; }
protected:
    /// The image for this drawable
    std::unique_ptr<Gdiplus::Bitmap> mImage;

private:
    Point mCenter = Point(0, 0);
};

