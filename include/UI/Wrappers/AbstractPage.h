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