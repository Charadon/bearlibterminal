/*
 * Main.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: Cfyz
 */

#include "Common.hpp"
#include <vector>
#include <string>
#include <vector>
#include <set>

struct TestEntry
{
	const char* name;
	void (*func)();
};

TERMINAL_TAKE_CARE_OF_WINMAIN

int main()
{
	terminal_open();
	auto reset = []()
	{
		terminal_set("window: size=80x25, cellsize=auto, title='Omni: menu'; font: default");
		terminal_color("white");
	};

	std::vector<TestEntry> entries =
	{
		{"Basic output", TestBasicOutput},
		{"Default font", TestDefaultFont},
		{"Tilesets", TestTilesets},
		{"Sprites", TestSprites},
		{"Manual cellsize", TestManualCellsize},
		{"Auto-generated tileset", TestAutoGenerated},
		{"Multiple fonts", TestMultipleFonts},
		{"Font viewer", nullptr}, // NYI
		{"Layers", TestLayers},
		{"Extended 1: basics", TestExtendedBasics},
		{"Extended 2: inter-layer animation", TestExtendedInterlayer},
		{"Extended 3: smooth scroll", TestExtendedSmoothScroll},
		{"Dynamic sprites", TestDynamicSprites},
		{"Synchronous rendering", nullptr}, // NYI
		{"Custom rendering", nullptr}, // NYI
		{"Input 1: keyboard", TestKeyboard},
		{"Input 2: mouse", TestMouse},
		{"Input 3: text input", TestTextInput}
	};

	reset();

	for (bool proceed=true; proceed;)
	{
		terminal_clear();
		for (size_t i=0; i<entries.size(); i++)
		{
			char shortcut = i < 9? '1'+i: 'a'+(i-9);
			terminal_printf(2, 1+i, "[color=orange]%c.[/color] %s%s", shortcut, entries[i].func? "": "[color=gray]", entries[i].name);
		}
		terminal_printf(2, 23, "[color=orange]ESC.[/color] Exit");
		terminal_refresh();

		do
		{
			int key = terminal_read();

			if (key == TK_ESCAPE || key == TK_CLOSE)
			{
				proceed = false;
			}
			else if ((key >= TK_1 && key <= TK_9) || (key >= TK_A && key <= TK_Z))
			{
				int index = key >= TK_A? 9+(key-TK_A): (key-TK_1);
				if (index >= 0 && index < entries.size() && entries[index].func)
				{
					entries[index].func();
					reset();
				}
			}
		}
		while (proceed && terminal_has_input());
	}
	terminal_close();
	return 0;
}
