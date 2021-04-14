/**
 * filename "Polydrawables.cpp"
 *
 *\author Shrey Jindal
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
#include "pch.h"
#include "PolyDrawable.h"

 /**
  * Constructor
  * \param name The drawable name
  */
CPolyDrawable::CPolyDrawable(const std::wstring& name) : CDrawable(name)
{
}

void CPolyDrawable::Draw(Gdiplus::Graphics* graphics)
{   
    SolidBrush brush(mColor);

    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    graphics->FillPolygon(&brush, &points[0], (int)points.size());
}

bool CPolyDrawable::HitTest(Gdiplus::Point pos)
{
    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    GraphicsPath path;
    path.AddPolygon(&points[0], (int)points.size());
    return path.IsVisible(pos) ? true : false;
}

void CPolyDrawable::AddPoint(Gdiplus::Point point)
{
	mPoints.push_back(point);
}
