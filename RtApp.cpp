#include <wx/wx.h>
#include "Display.h"
#include "Rt.h"


class RtApp: public wxApp
{
    
    wxFrame *frame;
    Display * drawPane;

    Rt* rt;

    unsigned int Nx;
    unsigned int Ny;


public:
    bool OnInit()
    {
        // make sure to call this first
        wxInitAllImageHandlers();
        
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        Nx = 600;
        Ny = 600;

        rt = new Rt(Nx, Ny);

        long style = wxDEFAULT_FRAME_STYLE; // ^ wxRESIZE_BORDER;
        frame = new wxFrame(NULL, wxID_ANY, wxT("Jon's RayTracer"), wxPoint(50,50), wxSize(Nx,Ny),style);

        drawPane = new Display( frame, Nx, Ny);
        //drawPane->Bind(wxEVT_LEFT_DOWN, &RtApp::OnClick, this);

        sizer->Add(drawPane, 1, wxEXPAND);
        frame->SetSizer(sizer);

        updateImage();

        frame->Show();
        return true;
    } 

    int OnExit()
    {
        delete rt;
        return 0;
    }

    void updateImage()
    {
        rt->render();
        drawPane->updateImage( rt->getImage());        
    }


    void OnClick(wxMouseEvent& /*event*/)
    {
        updateImage();
    }

};

IMPLEMENT_APP(RtApp)