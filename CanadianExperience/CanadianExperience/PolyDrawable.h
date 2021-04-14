/**
 * filename "Polydrawables.h"
 * 
 * \ author Shrey Jindal
 * 
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
#pragma once
#include <memory>
#include <vector>

#include "Drawable.h"


/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class CPolyDrawable : public CDrawable
{
public:
    /** \brief Default constructor disabled */
    CPolyDrawable() = delete;
    /** \brief Copy constructor disabled */
    CPolyDrawable(const CPolyDrawable&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CPolyDrawable&) = delete;


    ///Setter for mColor
    ///\param color
	virtual void SetColor(Gdiplus::Color color) { mColor = color; }; 
    ///Getter for mColor
    ///\returns mColor
	virtual Gdiplus::Color GetColor() { return mColor; };
    ///constructor
    ///\param name
    CPolyDrawable(const std::wstring& name);

    ///called when poly needs to be drawn
    ///\param graphics by pointer
    virtual void Draw(Graphics* graphics) override;

    /// tests if the passed point is on the drawable
    ///\param point
    virtual bool HitTest(Gdiplus::Point point) override;

    virtual void AddPoint(Gdiplus::Point point);


private:
	/// The polygon color
	Gdiplus::Color mColor = Gdiplus::Color::Black;

    /// The array of point objects
    std::vector<Gdiplus::Point> mPoints;
};

