#include "keyboard_buffer.h"

KeyboardBuffer& KeyboardBuffer::GetInstance()
{
    static KeyboardBuffer kb_buffer = KeyboardBuffer();
    return kb_buffer;
}

KeyboardBuffer::KeyboardBuffer() :
    handle_(GetStdHandle(STD_INPUT_HANDLE)),
    key_pressed_(keyboardbuffer::kNone)
{}

int KeyboardBuffer::WaitUntilInput(std::vector<int> allowed_input)
{
    while (true)
    {
        ReadInput();
        for (int user_input : allowed_input)
        {
            if (GetInput() == static_cast<WORD>(user_input))
            {
                return user_input;
            }
        }
    }
}

void KeyboardBuffer::ReadInput()
{
    key_pressed_ = keyboardbuffer::kNone;

    PeekConsoleInput(handle_, &buffer_, 1, &events_);
    if (!(events_ > 0))
    {
        return;
    }

    ReadConsoleInput(handle_, &buffer_, 1, &events_);
    if (!buffer_.Event.KeyEvent.bKeyDown)
    {
        return;
    }

    key_pressed_ = buffer_.Event.KeyEvent.wVirtualKeyCode;
}

WORD KeyboardBuffer::GetInput()
{
    return key_pressed_;
}
