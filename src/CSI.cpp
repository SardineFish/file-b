#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "CSI.h"

using namespace std;
void Screen::clear()
{
	printf("\e[2J");
}
void Screen::render(int **buffer, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int cell = *((int *)buffer + x * height + y);
			printBlock(cell);
		}
		printf("\n");
	}
}

Screen getScreen()
{
	Screen screen;
#ifdef TIOCGSIZE
	ttysize ts;
	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	screen.width = ts.ts_cols;
	screen.height = ts.ts_lines;
#elif defined(TIOCGWINSZ)
	winsize ts;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	screen.width = ts.ws_col;
	screen.height = ts.ws_row;
#endif
	return screen;
}
#ifdef __linux__
void resetColor()
{
	printf("\e[%d;%dm", F_DEFAULT, BG_DEFAULT);
}
void cursorUp(int n)
{
	printf("\e[%dA", n);
}
void cursorDown(int n)
{
	printf("\e[%dB", n);
}
void cursorForward(int n)
{
	printf("\e[%dC", n);
}
void cursorBack(int n)
{
	printf("\e[%dD", n);
}
void cursorNextLine(int n)
{
	printf("\e[%dE", n);
}
void cursorPreLine(int n)
{
	printf("\e[%dF", n);
}
void setCursorPos(int x, int y)
{
	printf("\e[%d;%dH", x, y);
}
void erase(int n)
{
	printf("\e[%dJ", n);
}
void eraseLine(int n)
{
	printf("\e[%dI", n);
}
void scrollUp(int n)
{
	printf("\e[%dS", n);
}
void scrollDown(int n)
{
	printf("\e[%dT", n);
}
void hideCursor()
{
	printf("\e[?25l");
}
void showCursor()
{
	printf("\e[?25h");
}

#elif _WIN32

void resetColor()
{
}
void cursorUp(int n)
{
}
void cursorDown(int n)
{
}
void cursorForward(int n)
{
}
void cursorBack(int n)
{
}
void cursorNextLine(int n)
{
}
void cursorPreLine(int n)
{
}
void setCursorPos(int x, int y)
{
}
void erase(int n)
{
}
void eraseLine(int n)
{
}
void scrollUp(int n)
{
}
void scrollDown(int n)
{
}
void hideCursor()
{
}
void showCursor()
{
}

#endif

void printBlock(const int color)
	{
		//char text[10];
		//sprintf(text,"%d",color);
		printText(F_DEFAULT, color, " ");
	}