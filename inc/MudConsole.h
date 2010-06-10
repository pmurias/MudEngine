#ifndef _MudConsole
#define _MudConsole

#include <MudTextBox.h>

#include <vector>
#include <cstdio>
#include <cstdarg>

namespace Mud {

    class Console {
    public:
        std::vector<TextBox *> consoleLines;

        void CreateLines(int quantity, const char *fontName, const char *fontSize, Ogre::ColourValue colour);
        void Print(const char *fmt, ...);

        void Show();
        void Hide();
    };
}

#endif

