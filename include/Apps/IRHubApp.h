#ifndef _IR_HUB_APP_H
#define _IR_HUB_APP_H

#include "Apps/AbstractApp.h"
#include "Managers/SDManager.h"
#include "Static/SDPaths.h"
#include "Static/Screen.h"
#include "UI/UISolutions/SelectionList.h"
#include "UI/Wrappers/Page.h"

namespace Apps
{
    class IRHubApp : public Apps::AbstractApp
    {
    private:
        UI::Wrappers::Page *_page;
        // UI::UISolutions::SelectionList *_selection_list;

    public:
        // ~IRHubApp();
        void start() override;
        void close() override;
        void update(ButtonEvents button_events) override;
        uint16_t *get_icon() const override;
    };
}

#endif