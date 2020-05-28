#pragma once

#include <wx/wx.h>

class Display : public wxPanel
{
    wxImage image;
    wxBitmap bmp;
    int image_w, image_h;
    int display_w, display_h;
    
public:
    Display(wxFrame* parent, int width, int height);
    Display(wxFrame* parent, unsigned char* data, int width, int height);

    //void updateImage(wxImage::RGBValue* data, int width, int height);
    void updateImage(unsigned char* data);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);
    void OnSize(wxSizeEvent& event);
    
    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */
    
    DECLARE_EVENT_TABLE()
};
