#include <MudTextBoxManager.h>

namespace Mud {

    void TextBoxManager::Init() {
        overlay = Ogre::OverlayManager::getSingletonPtr()->create("textBoxManagerOverlay");

        panel = static_cast<Ogre::OverlayContainer *>(
            Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "textBoxManagerPanel"));
        panel->setDimensions(1.0, 1.0);
        panel->setPosition(0.0, 0.0);
        
        overlay->add2D(panel);
        overlay->show();
    }

    TextBox *TextBoxManager::CreateTextBox(
        const char *id, 
        float x, 
        float y, 
        float w, 
        float h, 
        const char *font, 
        const char *fontSize, 
        Ogre::ColourValue colour
    ) {
        TextBox *textBox = new TextBox(id, x, y, w, h, font, fontSize, colour);
        panel->addChild(textBox->textArea);
        AddSafeElement(id, textBox);
        return textBox;
    }

    void TextBoxManager::RemoveTextBox(const char *id) {
        TextBox *textBox = GetSafeElement(id);
        panel->removeChild(id);
        Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(textBox->textArea);
        map.erase(id);
    }
}

