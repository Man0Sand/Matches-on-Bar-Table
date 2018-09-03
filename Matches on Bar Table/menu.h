#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include "menuitems.h"
#include "cl_selector.h"
#include "I_keyboard_buffer.h"


class cl_menu
{
public:
	cl_menu(I_KeyboardBuffer& kb_buffer, std::vector<cl_menuitem*>* p_menuitems, std::string menu_name);
	virtual ~cl_menu();
	void run_menu();

private:
    I_KeyboardBuffer& kb_buffer_;
    cl_menuitem* m_p_active_menuitem;
    std::vector<cl_menuitem*> m_menuitems;
	std::string m_menu_name;
    cl_selector_pointer<cl_menuitem*> m_menuitem_selection;
};

#endif // MENU_H