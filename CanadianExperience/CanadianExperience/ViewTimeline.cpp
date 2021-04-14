/**
 * \file ViewTimeline.cpp
 *
 * \author Shrey Jindal
 */


#include "pch.h"
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"
#include "Picture.h"
#include "MainFrm.h"
#include "Timeline.h"
#include <sstream>

using namespace std;
using namespace Gdiplus;

/// The window height in pixels
const int WindowHeight = 60;

/// The spacing from the top of the 
/// window to the top of the tick marks in pixels
const int BorderTop = 20;

/// Space to the left of the scale in pixels
const int BorderLeft = 10;

/// Space to the right of the scale in pixels
const int BorderRight = 10;

/// The spacing between ticks on the timeline in pixels
const int TickSpacing = 3;

/// The length of a short tick mark in pixels
const int TickShort = 10;

/// The length of a long tick mark in pixels
const int TickLong = 20;

IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** Constructor */
CViewTimeline::CViewTimeline()
{
    mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
    assert(mPointer->GetLastStatus() == Ok);
}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}




/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{
    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

        // Get the timeline
    CTimeline* timeline = GetPicture()->GetTimeline();

    // Set the scroll system correctly
    CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
    SetScrollSizes(MM_TEXT, sizeTotal);

    //// TODO: Drawing code goes here
    Pen pen(Color::Black, 1);
    /*graphics.DrawRectangle(&pen, 10, 10, 200, 60);*/

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 12);

    SolidBrush brush(Color::Black);
    //graphics.DrawString(L"Timeline!",  // String to draw
    //    -1,         // String length, -1 means it figures it out 
    //    &font,      // The font to use
    //    PointF(15, 15),   // Where to draw
    //    &brush);    // The brush to draw the text with

    //CString time = CTime::GetCurrentTime().Format("%H:%M:%S");
    //graphics.DrawString(time,  // String to draw
    //    -1,         // String length, -1 means it figures it out 
    //    &font,      // The font to use
    //    PointF(15, 40),   // Where to draw
    //    &brush);    // The brush to draw the text with


    CRect rect;
    GetClientRect(&rect);
    int hit = rect.Height();
    int wid = rect.Width();
    auto x = timeline->GetFrameRate();
    for (int i = 0; i <timeline->GetNumFrames()+1; i++)
    {

        if ((i % x) == 0)
        {
            //graphics.FillRectangle(&brush, BorderLeft + TickSpacing * i, hit / 2-10, 2, TickLong);
            graphics.DrawLine(&pen, BorderLeft + TickSpacing * i,
                hit / 2 - 10, BorderLeft + TickSpacing * i, hit / 2 - 10 +TickLong);
            int number = i / x;
            CString a;
            a.Format(L"%d", number);
            graphics.DrawString(a, -1, &font, PointF(REAL(BorderLeft + TickSpacing * i -12),REAL( hit / 2 + 10)), &brush);
            
        }
        else
        {
            graphics.DrawLine(&pen, BorderLeft + TickSpacing * i,
                hit / 2 - 10, BorderLeft + TickSpacing * i, hit / 2 - 10 + TickShort);

        }
        graphics.DrawImage(mPointer.get(), Gdiplus::REAL(BorderLeft - mPointer->GetWidth()/2 + TickSpacing * timeline->GetCurrentTime() * x), Gdiplus::REAL(hit / 2 - 10));
    }
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \return FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle a press of the keyframe set button on the toolbar
*/
void CViewTimeline::OnEditSetkeyframe()
{
    for (auto actor : *GetPicture())
    {
        actor->SetKeyframe();
    }
}

 /** Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
     // TODO: Add your command handler code here
     std::shared_ptr<CPicture> picture = GetPicture();

     picture->GetTimeline()->RemoveKeyframe();

     picture->SetAnimationTime(picture->GetCurrTime());
 }


 // Doxygen sometimes gets confused by these message 
 // maps, since they look like functions. I've found
 // it helps to move them to the end of the file.
 BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	 ON_WM_CREATE()
	 ON_WM_ERASEBKGND()
	 ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	 ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
     ON_WM_MOUSEMOVE()
     ON_WM_LBUTTONDOWN()
 END_MESSAGE_MAP()

 /**
 * Force an update of this window when the picture changes.
 */
 void CViewTimeline::UpdateObserver()
 {
     Invalidate();
     UpdateWindow();
 }

 void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
 {
     // Convert mouse coordinates to logical coordinates
     CClientDC dc(this);
     OnPrepareDC(&dc);
     dc.DPtoLP(&point);

     if (nFlags & MK_LBUTTON)
     {
         if (mMovingPointer)
         {
             double time = (double(point.x - (BorderLeft - mPointer->GetWidth() / 2)) /
                 double(TickSpacing * GetPicture()->GetTimeline()->GetFrameRate()));
             if (point.x < BorderLeft)
                 GetPicture()->SetAnimationTime(0);
             else if (time > GetPicture()->GetTimeline()->GetDuration())
                 GetPicture()->SetAnimationTime(GetPicture()->GetTimeline()->GetDuration());
             else
                 GetPicture()->SetAnimationTime(time);

         }
     }

     __super::OnMouseMove(nFlags, point);
 }


 void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
 {
     // TODO: Add your message handler code here and/or call default
         // Convert mouse coordinates to logical coordinates
     CClientDC dc(this);
     OnPrepareDC(&dc);
     dc.DPtoLP(&point);

     int x = point.x;

     // Get the timeline
     CTimeline* timeline = GetPicture()->GetTimeline();
     int pointerX = (int)(timeline->GetCurrentTime() *
         timeline->GetFrameRate() * TickSpacing + BorderLeft);

     mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 &&
         x <= pointerX + (int)mPointer->GetWidth() / 2;

     /*if (mMovingPointer)
     {
         int xx = 0;
     }*/

     __super::OnLButtonDown(nFlags, point);
 }
