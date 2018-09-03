#ifndef KEYBOARD_BUFFER_H
#define KEYBOARD_BUFFER_H

#include <Windows.h>

#include "I_keyboard_buffer.h"

class KeyboardBuffer : public I_KeyboardBuffer
{
public:
    static KeyboardBuffer& GetInstance();
    int WaitUntilInput(std::vector<int> allowed_input) override;

private:
    // Variables
    HANDLE handle_;
    DWORD events_;
    INPUT_RECORD buffer_;
    WORD key_pressed_;

    // Functions
    KeyboardBuffer();
    void ReadInput();
    WORD GetInput();
};

#endif // KEYBOARD_BUFFER_H
