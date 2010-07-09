#include <MudConsole.h>
#include <MudCore.h>

namespace Mud {

    void Console::CreateLines(int quantity, const char *fontName, const char *fontSize, Ogre::ColourValue colour) {
        char name[255];
        for (int i = 0; i < quantity; i++) {

            sprintf(name, "consoleLine%d", i);
            TextBox *line = Core::GetInstance().textBoxManager.CreateTextBox(
                name, 11, 11 + (12 * i), 800, 30, fontName, fontSize, Ogre::ColourValue(0,0,0)
            );
            sprintf(name, "shadowLine%d", i);
            TextBox *shadow = Core::GetInstance().textBoxManager.CreateTextBox(
				name, 10, 10 + (12 * i), 800, 30, fontName, fontSize, colour
			);

            consoleLines.push_back(line);
            consoleLines.push_back(shadow);
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

        for (size_t i = 0; i < consoleLines.size() - 2; i++) {
            consoleLines[i]->SetCaption(consoleLines[i + 2]->GetCaption());
            consoleLines[i+1]->SetCaption(consoleLines[i + 2]->GetCaption());
        }
        consoleLines[consoleLines.size() - 2]->SetCaption(out);
        consoleLines[consoleLines.size() - 1]->SetCaption(out);
    }

    void Console::Show() {
        for (size_t i = 0; i < consoleLines.size(); i++) {
            consoleLines[i]->Show();
        }
    }

    void Console::Hide() {
        for (int i = 0; i < consoleLines.size(); i++) {
            consoleLines[i]->Hide();
        }
    }

}
