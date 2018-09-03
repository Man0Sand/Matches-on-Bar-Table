#include "main_menu.h"

#include "keyboard_buffer.h"

int main(void)
{
    MainMenu main_menu = MainMenu(KeyboardBuffer::GetInstance());
    main_menu.run();

    return 0;
}
