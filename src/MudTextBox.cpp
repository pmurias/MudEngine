#include <MudTextBox.h>

namespace Mud {

    TextBox::TextBox(
        const char *id, 
        float x, 
        float y, 
        float w, 
        float h, 
        const char *font, 
        const char *fontSize, 
        Ogre::ColourValue colour
    ) {
        textArea = Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("TextArea", id);

        textArea->setDimensions(w, h);
        textArea->setMetricsMode(Ogre::GMM_PIXELS);
        textArea->setPosition(x, y);
        textArea->setWidth(w);
        textArea->setHeight(h);
        textArea->setParameter("font_name", font);
        textArea->setParameter("char_height", fontSize);
        textArea->setColour(colour);        
    }

    void TextBox::SetPosition(float x, float y) {
        textArea->setPosition(x, y);
    }

    void TextBox::SetCaption(const char *str) {
        textArea->setCaption(str);
    }

    const char *TextBox::GetCaption() {
        return textArea->getCaption().asUTF8_c_str();
    }

    void TextBox::Show() {
        textArea->show();
    }

    void TextBox::Hide() {
        textArea->hide();
    }
}
