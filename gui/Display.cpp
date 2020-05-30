#include "Display.h"

Display::Display(wxFrame* parent, int width, int height)
: wxPanel(parent), image_w(width), image_h(height),
display_w(width), display_h(height),manual_resize(false)
{    
    image.Create( image_w, image_h, true);
    bmp = wxBitmap( image );
    Refresh();
}

Display::Display(wxFrame* parent, unsigned char* data, int width, int height)
: wxPanel(parent), display_w(width), display_h(height)
{
    updateImage(data,width,height);
}

void Display::updateImage(unsigned char* data, int w, int h)
{
    image_w = w;
    image_h = h;
    image.Create( image_w, image_h, data, true);
    bmp = wxBitmap( image.Scale( display_w, display_h /*, wxIMAGE_QUALITY_HIGH*/ ) );
    Refresh();
}

void Display::updateImageSize(int w, int h)
{
    image_w = w;
    image_h = h;
    image.Create( image_w, image_h, true);
    bmp = wxBitmap( image );
    Refresh();
}


void Display::paintEvent(wxPaintEvent& /*evt*/)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

void Display::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

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

void Display::OnSize(wxSizeEvent& event)
{
    manual_resize = true;
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

