#include "RenderFrame.h"

RenderFrame::RenderFrame(wxApp *handler,  const std::string& config_filename)
: wxFrame(NULL, wxID_ANY, wxT("RayTracer: " + config_filename), wxPoint(50,50), wxDefaultSize,wxDEFAULT_FRAME_STYLE),
closing(false), config_filename(config_filename), rt(NULL), imageData(NULL),
handler(handler)
{    
    try
    {
        CreateStatusBar(); 	
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        drawPane = new Display( this, 10,10);
        sizer->Add(drawPane, 1, wxEXPAND);
        SetSizer(sizer);

        //bind events

        //mouse click
        drawPane->Bind(wxEVT_LEFT_DOWN, &RenderFrame::OnClick, this);

        if(!startRender()) return;
        //Nx, Ny set from config

    }
    catch(const std::exception& e)
    {
        std::cerr << "Unhandled Exception" << std::endl;            
        std::cerr << e.what() << '\n';
        return;
    }
} 

RenderFrame::~RenderFrame()
{
}

bool RenderFrame::startRender()
{
    //stop any current rendering process
    stopRender();

    //delete previous rt object
    if(rt) delete rt;
    if(imageData) delete[] imageData;

    //(re)read config file
    Json::Value rtConfig;
    try
    {
        // read config file into json object
        std::ifstream configFile(config_filename);
        if(!configFile.is_open())
            throw std::runtime_error("Error opening config file " + config_filename);

        configFile >> rtConfig;
        configFile.close();

        //parse config to get inmage size
        Nx = rtConfig["image"]["width"].asUInt();
        Ny = rtConfig["image"]["height"].asUInt();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error Parsing " << config_filename << std::endl;            
        std::cerr << e.what() << '\n';
        return false;
    }

    rt = new Rt(rtConfig);
    if(!rt->isValid())
    {
        std::cerr << "Error initializing RayTracer" << std::endl;            
        return false;
    }

    imageData = new unsigned char[Nx*Ny*3];

    if(!drawPane->manual_resize)
    {
        drawPane->updateImageSize(Nx,Ny);
        SetClientSize(wxSize(Nx,Ny));        
    }

    //set callback for redrawing image
    rt->imageUpdate = std::bind(&RenderFrame::emitNewImage, this, std::placeholders::_1, std::placeholders::_2);

    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        std::cerr << "Error starting worker thread" << std::endl;            
        return false;
    }
    // go!
    return GetThread()->Run() == wxTHREAD_NO_ERROR;
}

//start rendering image in new thread
wxThread::ExitCode RenderFrame::Entry()
{
    rt->render();
    return (wxThread::ExitCode)0;     // success
}

//callback from render object.
//this will be called from render thread, so just emit an event to be processed by main thread
void RenderFrame::emitNewImage(int current_ray, int total_rays)
{
    wxCommandEvent* event = new wxCommandEvent(myEVT_NEW_IMAGE_AVAILABLE);
    event->SetString("Rendering: " + std::to_string(current_ray) + "/" + std::to_string(total_rays));
    wxQueueEvent(this, event);
}

// void RenderFrame::updateImage(wxThreadEvent& /*event*/)
void RenderFrame::updateImage(wxCommandEvent& event)
{
    if(closing) return;
    rt->copyImage(imageData); //copy data from render object.  This call is threadsafe
    drawPane->updateImage(imageData,Nx,Ny);

    SetStatusText(event.GetString());

    Update();
}

void RenderFrame::stopRender()
{
    if(!rt) return;
    rt->cancelRender();
    GetThread()->Wait();
}

void RenderFrame::OnClick(wxMouseEvent& /*event*/)
{
    startRender();
}

void RenderFrame::OnClose(wxCloseEvent& /*event*/)
{
    closing = true;
    stopRender();
    if(rt) delete rt;
    if(imageData) delete[] imageData;
    Destroy();
}

//wxDEFINE_EVENT(myEVT_NEW_IMAGE_AVAILABLE, wxThreadEvent);
wxDEFINE_EVENT(myEVT_NEW_IMAGE_AVAILABLE, wxCommandEvent);

wxBEGIN_EVENT_TABLE(RenderFrame, wxFrame)
//    EVT_THREAD(wxID_ANY, myEVT_NEW_IMAGE_AVAILABLE, RenderFrame::updateImage)

    EVT_COMMAND(wxID_ANY, myEVT_NEW_IMAGE_AVAILABLE, RenderFrame::updateImage)
//    EVT_THREAD(myEVT_NEW_IMAGE_AVAILABLE, RenderFrame::updateImage)
    EVT_CLOSE(RenderFrame::OnClose)
wxEND_EVENT_TABLE()
