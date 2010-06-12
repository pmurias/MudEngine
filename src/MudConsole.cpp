#include <MudConsole.h>
#include <MudCore.h>

namespace Mud {

    void Console::CreateLines(int quantity, const char *fontName, const char *fontSize, Ogre::ColourValue colour) {
        char lineName[255];
        for (int i = 0; i < quantity; i++) {
            sprintf(lineName, "consoleLine%d", i);
            TextBox *line = Core::GetInstance().textBoxManager.CreateTextBox(
                lineName, 10, 10 + (12 * i), 800, 30, fontName, fontSize, colour
            );
            consoleLines.push_back(line);
        }
    }

    void Console::Print(const char *fmt, ...) {
        char out[4096];
        va_list args;
        if (fmt == NULL)
            out[0] = '\0';
        else {
            va_start(args, fmt);
            vsprintf(out, fmt, args);
            va_end(args);          
        }

        for (int i = 0; i < consoleLines.size() - 1; i++) {
            consoleLines[i]->SetCaption(consoleLines[i + 1]->GetCaption());
        }
        consoleLines[consoleLines.size() - 1]->SetCaption(out);        
    }

    void Console::Show() {
        for (int i = 0; i < consoleLines.size(); i++) {
            consoleLines[i]->Show();
        }
    }

    void Console::Hide() {
        for (int i = 0; i < consoleLines.size(); i++) {
            consoleLines[i]->Hide();
        }
    }

}
