#include "Display.h"

Display::Display(wxFrame* parent, int width, int height)
: wxPanel(parent), image_w(width), image_h(height),
display_w(width), display_h(height)
{    
    image.Create( image_w, image_h, true);
    bmp = wxBitmap( image );
    Refresh();
}

Display::Display(wxFrame* parent, unsigned char* data, int width, int height)
: wxPanel(parent), image_w(width), image_h(height),
display_w(width), display_h(height)
{
    updateImage(data);
}

void Display::updateImage(unsigned char* data)
{
    image.Create( image_w, image_h, data, true);
    bmp = wxBitmap( image.Scale( display_w, display_h /*, wxIMAGE_QUALITY_HIGH*/ ) );
    Refresh();
}


/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void Display::paintEvent(wxPaintEvent& /*evt*/)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}


/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void Display::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void Display::render(wxDC&  dc)
{
    int neww, newh;
    dc.GetSize( &neww, &newh );
    
    if( neww != display_w || newh != display_h )
    {
        bmp = wxBitmap( image.Scale( neww, newh /*, wxIMAGE_QUALITY_HIGH*/ ) );
        display_w = neww;
        display_h = newh;
    }

    dc.DrawBitmap( bmp, 0, 0, false );
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void Display::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}

BEGIN_EVENT_TABLE(Display, wxPanel)
// some useful events
/*
 EVT_MOTION(wxImagePanel::mouseMoved)
 EVT_LEFT_UP(wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxImagePanel::keyPressed)
 EVT_KEY_UP(wxImagePanel::keyReleased)
 EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(Display::paintEvent)
//Size event
EVT_SIZE(Display::OnSize)
END_EVENT_TABLE()

