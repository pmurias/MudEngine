#ifndef _MudConsole
#define _MudConsole

#include <MudTextBox.h>

#include <vector>
#include <cstdio>
#include <cstdarg>

namespace Mud {

    /** Runtime, on-screen console class */
    class Console {
    public:
        std::vector<TextBox *> consoleLines;

        /** Initializes console with a number of maximum output lines
         * @param quantity Number of maximum output lines
         * @param fontName Name of font resource
         * @param fontSize Size of the font as string
         * @param colour Text output colour
         */
        void CreateLines(int quantity, const char *fontName, const char *fontSize, Ogre::ColourValue colour);
        /** Prints new line to the console
         * @param fmt Regular format string
         */
        void Print(const char *fmt, ...);
 
        /// Shows console
        void Show();
        /// Hides console
        void Hide();
    };
}

#endif

