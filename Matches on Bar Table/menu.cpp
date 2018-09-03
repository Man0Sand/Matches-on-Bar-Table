#include <iostream>

#include "menu.h"

#include "screen_buffer.h"

cl_menu::cl_menu(I_KeyboardBuffer& kb_buffer, std::vector<cl_menuitem*>* p_menuitems, std::string menu_name):
kb_buffer_(kb_buffer),
m_p_active_menuitem(*p_menuitems->begin()),
m_menuitems(*p_menuitems),
m_menu_name(menu_name),
m_menuitem_selection(p_menuitems, &*p_menuitems->begin())
{
}

cl_menu::~cl_menu()
{
}

void cl_menu::run_menu()
{
	bool exit_menu = false;
	
	while(!exit_menu)
	{
        screenbuffer::ClearScreen();
        for (cl_menuitem* menuitem : m_menuitems)
        {
            if (menuitem == m_p_active_menuitem)
            {
                screenbuffer::InvertColors();
                std::cout << menuitem->get_display_text() << "\n";
                screenbuffer::InvertColors();
            }
            else
            {
                std::cout << menuitem->get_display_text() << "\n";
            }
        }
        
        int input = kb_buffer_.WaitUntilInput({ keyboardbuffer::kArrowDown, keyboardbuffer::kArrowUp, keyboardbuffer::kEnter });
        if (input == keyboardbuffer::kEnter)
		{
			exit_menu = m_p_active_menuitem->enter_pressed();
		}
		else if (input == keyboardbuffer::kArrowUp)
		{
            m_p_active_menuitem = *m_menuitem_selection.previous();
		}
		else if (input == keyboardbuffer::kArrowDown)
		{
            m_p_active_menuitem = *m_menuitem_selection.next();
		}
	}
}

