#ifndef CL_SELECTOR_H
#define CL_SELECTOR_H

#include <vector>
#include <algorithm>

template <typename T>
class cl_selector
{
public:
    cl_selector(): m_p_selections(nullptr) {}
    
    cl_selector(std::vector<T>* p_selections, T* p_initial_selection):
        m_p_selections(p_selections),
        m_it_active_selection(m_p_selections->begin())
        {
        }

    T* next(void)
    {
        if (m_it_active_selection == m_p_selections->end() - 1)
        {
            m_it_active_selection = m_p_selections->begin();
        }
        else
        {
            ++m_it_active_selection;
        }

        return &*m_it_active_selection;
    }

    T* previous(void)
    {
        if (m_it_active_selection == m_p_selections->begin())
        {
            m_it_active_selection = m_p_selections->end() - 1;
        }
        else
        {
            --m_it_active_selection;
        }

        return &*m_it_active_selection;
    }

    T* current(void)
    {
        return &*m_it_active_selection;
    }

protected:
    std::vector<T>* m_p_selections;
    typename std::vector<T>::iterator m_it_active_selection;
};

template <typename T>
class cl_selector_value : public cl_selector<T>
{
public:
    cl_selector_value():
    cl_selector<T>()
    {
    }

    cl_selector_value(std::vector<T>* p_selections, T* p_initial_selection):
    cl_selector<T>(p_selections, p_initial_selection)
    {
        cl_selector<T>::m_it_active_selection = std::find(cl_selector<T>::m_p_selections->begin(), 
            cl_selector<T>::m_p_selections->end(), *p_initial_selection);
    }
};

template <typename T>
class cl_selector_pointer : public cl_selector<T>
{
public:

    cl_selector_pointer():
    cl_selector<T>()
    {
    }

    cl_selector_pointer(std::vector<T>* p_selections, T* p_initial_selection):
    cl_selector<T>(p_selections, p_initial_selection)
    {
        while (&*cl_selector<T>::m_it_active_selection != p_initial_selection)
        {
            ++cl_selector<T>::m_it_active_selection;
        }
    }
};

#endif // CL_SELECTOR_H
