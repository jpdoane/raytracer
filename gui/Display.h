#pragma once

#include <wx/wx.h>

class Display : public wxPanel
{
    wxImage image;
    wxBitmap bmp;
    int image_w, image_h;
    int display_w, display_h;
    
public:
    bool manual_resize; //if unset, resize on render based on image dimensions. else, keep manual size

    Display(wxFrame* parent, int width, int height);
    Display(wxFrame* parent, unsigned char* data, int width, int height);

    //void updateImage(wxImage::RGBValue* data, int width, int height);
    void updateImage(unsigned char* data, int h, int w);
    void updateImageSize(int h, int w);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);
    void OnSize(wxSizeEvent& event);

    inline int getW() const { return display_w; }
    inline int getH() const { return display_h; }

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
