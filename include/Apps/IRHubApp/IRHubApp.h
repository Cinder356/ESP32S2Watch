#ifndef _IR_HUB_APP_H
#define _IR_HUB_APP_H

#include "Apps/AbstractApp.h"
#include "Managers/SDManager.h"
#include "Static/SDPaths.h"
#include "Static/Screen.h"
#include "UI/UISolutions/SelectionList.h"
#include "UI/Wrappers/Window.h"

#include "IRMainMenuPage.h"

namespace Apps::IRHub
{
    class IRHubApp : public Apps::AbstractApp
    {
    private:
        UI::Wrappers::Window *_window_ptr;

    public:
        // ~IRHubApp();
        void start() override;
        void close() override;
        void update() override;
        uint16_t *get_icon() const override;
    };
}

#endif