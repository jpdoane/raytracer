#include <wx/wx.h>
#include <wx/cmdline.h>
#include "RenderFrame.h"

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
    { wxCMD_LINE_PARAM, NULL, NULL, "config_file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY },
    { wxCMD_LINE_NONE, NULL, NULL, NULL, wxCMD_LINE_VAL_NONE, 0 }
};

class RtApp: public wxApp
{
    RenderFrame *frame;
public:

    bool OnInit()
    {
        // get config file from cmd line
        wxCmdLineParser parser(cmdLineDesc,argc,argv);
        if(parser.Parse())
            return false;
        std::string config_filename = parser.GetParam().ToStdString();

        wxInitAllImageHandlers();
        frame = new RenderFrame(this,config_filename);
        frame->Show();
        return true;
    }
};

IMPLEMENT_APP(RtApp)