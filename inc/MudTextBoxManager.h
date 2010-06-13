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

        /** Creates and retursn new TextBox object
         * @param id Unique overlay element ID
         * @param x Horizontal position in pixels
         * @param y Position position in pixels
         * @param w Width in pixels
         * @param h Height in pixels
         * @param font Font resource name
         * @param fontSize Font size as string
         * @param colour Text colour
         */
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

        /// Removes TextBox from manager and overlay
        void RemoveTextBox(const char *id);    
    };

}

#endif
