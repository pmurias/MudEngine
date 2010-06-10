#ifndef _MudTextBoxManager
#define _MudTextBoxManager

#include <MudTextBox.h>
#include <MudHashmapManager.h>

#include <OGRE/Ogre.h>

namespace Mud {

    class TextBoxManager : public HashmapManager<TextBox *> {
    public:

        Ogre::Overlay *overlay;
        Ogre::OverlayContainer *panel;

        void Init();

        TextBox *CreateTextBox(
            const char *id, 
            float x, 
            float y, 
            float w, 
            float h, 
            const char *font, 
            const char *fontSize, 
            Ogre::ColourValue colour
        );
        void RemoveTextBox(const char *id);    
    };

}

#endif
