#ifndef SELECTOR_H
#define SELECTOR_H

#include <stdexcept>
#include <vector>

template <class T>
class Selector
{
public:
    Selector() :
        p_first_element_(nullptr),
        p_last_element_(nullptr),
        p_active_element_(nullptr)
    {
    }

    Selector(std::vector<T>* p_elements, T* p_initial_element)
    {
        if (!p_elements || !p_initial_element)
        {
            throw std::invalid_argument("Received a null pointer!");
        }
        if (p_elements->empty())
        {
            throw std::invalid_argument("Received an empty container!");
        }
        
        p_first_element_ = &p_elements->front();
        p_last_element_ = &p_elements->back();
        
        p_active_element_ = nullptr;
        for (T* p_element = p_first_element_; p_element != p_last_element_ + 1; ++p_element)
        {
            if (p_element == p_initial_element)
            {
                p_active_element_ = p_initial_element;
            }
        }
        if (!p_active_element_)
        {
            throw std::invalid_argument("Initial element does not point to given container!");
        }
    }

    void operator++()
    {
        if (p_active_element_ == p_last_element_)
        {
            p_active_element_ = p_first_element_;
        }
        else
        {
            ++p_active_element_;
        }
    }
    
    void operator--()
    {
        if (p_active_element_ == p_first_element_)
        {
            p_active_element_ = p_last_element_;
        }
        else
        {
            --p_active_element_;
        }
    }

    T operator->()
    {
        return *p_active_element_;
    }

    T* GetPointer()
    {
        return p_active_element_;
    }

    T GetValue()
    {
        return *p_active_element_;
    }

private:
    typename std::vector<T>::pointer p_first_element_;
    typename std::vector<T>::pointer p_last_element_;
    T* p_active_element_;
};

#endif // SELECTOR_H
