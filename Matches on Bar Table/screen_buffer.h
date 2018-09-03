#ifndef SCREEN_BUFFER_H
#define SCREEN_BUFFER_H

namespace screenbuffer
{
    void SetCursorPosition(const int& x, const int& y);
    void GetCursorPosition(int* x, int* y);
    int GetCursorRow();
    void ClearScreen();
    void ClearRow();
    void InvertColors();
}

#endif // SCREEN_BUFFER_H