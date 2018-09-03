#ifndef KEYBOARD_BUFFER_MOCK
#define KEYBOARD_BUFFER_MOCK

#include "I_keyboard_buffer.h"

class KeyboardBufferMock : public I_KeyboardBuffer
{
public:
    KeyboardBufferMock(std::vector<int> user_inputs):
    user_inputs_(user_inputs),
    p_active_user_input(&user_inputs_.front())
    {}

    int WaitUntilInput(std::vector<int> allowed_input) override
    {
        int user_input = *p_active_user_input;

        if (p_active_user_input == &user_inputs_.back())
        {
            p_active_user_input = &user_inputs_.front();
        }
        else
        {
            ++p_active_user_input;
        }

        return user_input;
    }

private:
    std::vector<int> user_inputs_;
    int* p_active_user_input;
};

#endif // KEYBOARD_BUFFER_MOCK
