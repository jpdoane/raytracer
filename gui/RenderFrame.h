#pragma once
#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/statusbr.h>
#include "Display.h"
#include "Rt.h"

#include <fstream>
#include <jsoncpp/json/json.h>


//wxDECLARE_EVENT(myEVT_NEW_IMAGE_AVAILABLE, wxThreadEvent);
wxDECLARE_EVENT(myEVT_NEW_IMAGE_AVAILABLE, wxCommandEvent);

class RenderFrame : public wxFrame, public wxThreadHelper
{
    bool closing; //set when we start to close down, to prevent further events from using invalid data
    std::string config_filename;

    Display *drawPane;
    Rt* rt;

    unsigned char* imageData;
    unsigned int Nx;
    unsigned int Ny;

    wxPoint mouse_last_pos;
    wxClientDC* dc;

public:
    RenderFrame(wxApp *handler, const std::string& config_filename);
    ~RenderFrame();

protected:
    virtual wxThread::ExitCode Entry();
    wxApp *handler;

    void emitNewImage(int current_ray, int total_rays); //callback from render object to indicate new image is available
    //void updateImage(wxThreadEvent& event);
    void updateImage(wxCommandEvent& event);
    void OnMouse(wxMouseEvent& event);
    void OnClose(wxCloseEvent& event);

    bool configRender();
    bool startRender();
    void stopRender();

    wxDECLARE_EVENT_TABLE();
};
