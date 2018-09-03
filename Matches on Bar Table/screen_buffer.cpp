#include <Windows.h>

#include "screen_buffer.h"

namespace
{
    class ScreenBuffer
    {
    public:
        ScreenBuffer();
        ~ScreenBuffer();
        void SetCursorPosition(COORD coordinates);
        void ClearScreen();
        COORD GetCursorPosition();
        void ClearRow();
        void InvertColors();

    private:
        HANDLE handle_;
    };
    
    ScreenBuffer screen_buffer;
}

namespace screenbuffer
{
    void SetCursorPosition(const int& x, const int& y)
    {
        COORD coordinates = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        screen_buffer.SetCursorPosition(coordinates);
    }

    void GetCursorPosition(int* x, int* y)
    {
        COORD coordinates = screen_buffer.GetCursorPosition();
        *x = coordinates.X;
        *y = coordinates.Y;
    }

    int GetCursorRow()
    {
        int x, y;
        GetCursorPosition(&x, &y);
        return y;
    }

    void ClearScreen()
    {
        screen_buffer.ClearScreen();
    }

    void ClearRow()
    {
        screen_buffer.ClearRow();
    }

    void InvertColors()
    {
        screen_buffer.InvertColors();
    }
}

namespace
{
    ScreenBuffer::ScreenBuffer() :
        handle_(GetStdHandle(STD_OUTPUT_HANDLE))
    {
        CONSOLE_CURSOR_INFO cursor_info;
        GetConsoleCursorInfo(handle_, &cursor_info);
        cursor_info.bVisible = false;
        SetConsoleCursorInfo(handle_, &cursor_info);
    }

    ScreenBuffer::~ScreenBuffer()
    {
    }

    void ScreenBuffer::SetCursorPosition(COORD coordinates)
    {
        SetConsoleCursorPosition(handle_, coordinates);
    }

    void ScreenBuffer::ClearScreen()
    {
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(handle_, &buffer_info);
        
        DWORD number_of_cells = buffer_info.dwSize.X * buffer_info.dwSize.Y;
        TCHAR fill_character = ' ';
        COORD beginning_point = { 0,0 };
        DWORD number_of_inserted_characters;
        FillConsoleOutputCharacter(handle_, fill_character, number_of_cells, beginning_point, &number_of_inserted_characters);
        FillConsoleOutputAttribute(handle_, buffer_info.wAttributes, number_of_cells, beginning_point, &number_of_inserted_characters);

        SetCursorPosition(beginning_point);
    }

    COORD ScreenBuffer::GetCursorPosition()
    {
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(handle_, &buffer_info);
        return buffer_info.dwCursorPosition;
    }

    void ScreenBuffer::ClearRow()
    {
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(handle_, &buffer_info);

        DWORD number_of_cells = buffer_info.dwSize.X;
        TCHAR fill_character = ' ';
        COORD beginning_point = { 0, GetCursorPosition().Y };
        DWORD number_of_inserted_characters;
        FillConsoleOutputCharacter(handle_, fill_character, number_of_cells, beginning_point, &number_of_inserted_characters);

        SetCursorPosition(beginning_point);
    }

    void ScreenBuffer::InvertColors()
    {
        CONSOLE_SCREEN_BUFFER_INFO buffer_info;
        GetConsoleScreenBufferInfo(handle_, &buffer_info);
        WORD attributes = buffer_info.wAttributes;
        WORD background_attributes = (BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
        WORD text_attributes = (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
        WORD mask = background_attributes | text_attributes;
        WORD inverted_desired_bits = (attributes & mask)^mask;
        attributes &= ~mask;
        attributes |= inverted_desired_bits;
        SetConsoleTextAttribute(handle_, attributes);
    }
}
