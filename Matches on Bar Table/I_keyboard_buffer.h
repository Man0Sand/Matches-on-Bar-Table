#ifndef I_KEYBOARD_BUFFER_H
#define I_KEYBOARD_BUFFER_H

#include <vector>

namespace keyboardbuffer
{
    const int kNone = 0;
    const int kArrowUp = 38;
    const int kArrowDown = 40;
    const int kArrowLeft = 37;
    const int kArrowRight = 39;
    const int kSpace = 32;
    const int kEnter = 13;
    const int kEsc = 27;
    const int kBackspace = 8;
    const int kE = 69;
    const int kOne = 49;
    const int kTwo = 50;
    const int kThree = 51;
}

class I_KeyboardBuffer
{
public:
    virtual int WaitUntilInput(std::vector<int> allowed_input) = 0;
    virtual ~I_KeyboardBuffer() = default;
};

#endif // I_KEYBOARD_BUFFER_H
