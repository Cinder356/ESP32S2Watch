#ifndef _IR_HUB_APP_H
#define _IR_HUB_APP_H

#include "Apps/AbstractApp.h"
#include "Managers/SDManager.h"
#include "Static/SDPaths.h"
#include "Static/Screen.h"
#include "UI/UISolutions/SelectionList.h"
#include "UI/Wrappers/Window.h"

#include "MainMenuPage.h"

namespace Apps::IRHub
{
    class IRHubApp : public Apps::AbstractApp
    {
    private:
        UI::Wrappers::Window *_window;

    public:
        // ~IRHubApp();
        void start() override;
        void close() override;
        void update() override;
        uint16_t *get_icon() const override;
    };

    // class FirstPage : public UI::Wrappers::AbstractPage
    // {
    // private:
    //     UI::Wrappers::Window *_window;

    //     void redirect();

    // public:
    //     FirstPage();
    //     void open() override;
    //     void update() override;
    // };

    //     class SecondPage : public UI::Wrappers::AbstractPage
    // {
    // private:
    //     UI::Wrappers::Window *_window;

    // public:
    //     SecondPage(UI::Wrappers::Window *window);
    //     void open() override;
    //     void update() override;
    // };
}

#endif