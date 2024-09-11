#ifndef _ABSTRACT_PAGE_H
#define _ABSTRACT_PAGE_H

namespace UI::Wrappers
{
    class AbstractPage
    {
    public:
        virtual void open() = 0;
        virtual void update() = 0;
    };
}
#endif

/*
-----| ex.h |-----

#ifndef ...
#define ...

#include "UI/Wrappers/AbstractPage.h"
#include "UI/Wrappers/Window.h"

namespace Apps::...::Pages
{
    class ... : public AbstractPage
    {
    private:
        Window *_window_ptr;

    public:
        ...(Window *window_ptr);
        void open() override;
        void update() override;
    };
}

#endif


-----| ex.cpp |-----

#include "Apps/.../AllPages.h"

namespace Apps::...::Pages
{
    ...::...(Window *window_ptr) : _window_ptr(window_ptr) {}

    void ...::open()
    {
    }

    void ...::update()
    {
    }
}

*/