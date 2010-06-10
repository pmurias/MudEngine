#ifndef _MudTextBox
#define _MudTextBox

#include <OGRE/Ogre.h>

namespace Mud {

    class TextBox {
    public:

        Ogre::OverlayElement *textArea;

        TextBox(
            const char *id, 
            float x, 
            float y, 
            float w, 
            float h, 
            const char *font, 
            const char *fontSize, 
            Ogre::ColourValue colour
        );

        void SetPosition(float x, float y);
        void SetCaption(const char *str);
        const char *GetCaption();
        void Show();
        void Hide();

    };
}

#endif

