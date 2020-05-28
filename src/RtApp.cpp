#include <wx/wx.h>
#include <wx/cmdline.h>
#include "Display.h"
#include "Rt.h"

#include <fstream>
#include <jsoncpp/json/json.h>

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
    // { wxCMD_LINE_SWITCH, "v", "verbose", "be verbose" },
    // { wxCMD_LINE_SWITCH, "q", "quiet",   "be quiet" },
    // { wxCMD_LINE_OPTION, "o", "output",  "output file" },
    // { wxCMD_LINE_OPTION, "i", "input",   "input dir" },
    // { wxCMD_LINE_OPTION, "s", "size",    "output block size", wxCMD_LINE_VAL_NUMBER },
    // { wxCMD_LINE_OPTION, "d", "date",    "output file date", wxCMD_LINE_VAL_DATE },

    { wxCMD_LINE_PARAM, NULL, NULL, "config_file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY },
    { wxCMD_LINE_NONE, NULL, NULL, NULL, wxCMD_LINE_VAL_NONE, 0 }
};



class RtApp: public wxApp
{
    
    wxFrame *frame;
    Display *drawPane;

    std::string config_filename;
    Rt* rt;

    unsigned int Nx;
    unsigned int Ny;


public:
    bool OnInit()
    {
        rt = NULL;

        // get config file from cmd line
        wxCmdLineParser parser(cmdLineDesc,argc,argv);
        if(parser.Parse())
            return false;
        config_filename = parser.GetParam().ToStdString();

        if(!configImage()) return false;

        try
        {        
            // make sure to call this first
            wxInitAllImageHandlers();
            
            wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

            long style = wxDEFAULT_FRAME_STYLE; // ^ wxRESIZE_BORDER;
            frame = new wxFrame(NULL, wxID_ANY, wxT("RayTracer: " + config_filename), wxPoint(50,50), wxSize(Nx,Ny),style);

            drawPane = new Display( frame, Nx, Ny);
            drawPane->Bind(wxEVT_LEFT_DOWN, &RtApp::OnClick, this);

            sizer->Add(drawPane, 1, wxEXPAND);
            frame->SetSizer(sizer);

            updateImage();

            frame->Show();
            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Unhandled Exception" << std::endl;            
            std::cerr << e.what() << '\n';
            return false;
        }
    } 

    int OnExit()
    {
        delete rt;
        return 0;
    }

    bool configImage()
    {
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

        if(rt) delete rt;
        rt = new Rt(rtConfig);
        if(!rt->isValid())
        {
            std::cerr << "Error initializing RayTracer" << std::endl;            
            return false;
        }
        return true;
    }


    void updateImage()
    {

        std::cout << "Rendering image...";
        fflush(stdout);
        rt->render();
        drawPane->updateImage( rt->getImage());        
        std::cout << " Complete" << std::endl;            

    }


    void OnClick(wxMouseEvent& /*event*/)
    {
        configImage();
        updateImage();
    }

};

IMPLEMENT_APP(RtApp)