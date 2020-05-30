#include <jsoncpp/json/json.h>
#include "Color.h"
#include <string.h>

class Image
{
    bool valid;
    unsigned int w,h;
    unsigned char* data;

    public:

    Image(const Json::Value& config);
    ~Image();

    inline unsigned char* get_data() { return data; }
    inline void copy_data(unsigned char* dest) { memcpy(dest,data,w*h*3); }

    void copyFromColorArray(Color* col);

    inline unsigned int get_width() const { return w; }
    inline unsigned int get_height() const { return h; }
    inline bool isValid() const {return valid;}
};
