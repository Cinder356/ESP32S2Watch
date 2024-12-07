#ifndef _IR_SENDER_H
#define _IR_SENDER_H

#include <Arduino.h>
#include "Static/Pins.h"

namespace Managers::IRManager
{
    // Частота ИК-сигнала (в Гц)
    const uint16_t IR_FREQUENCY = 38000;            // Частота 38 кГц
    const uint16_t PERIOD = 1000000 / IR_FREQUENCY; // Период для частоты 38 кГц (в микросекундах)

    class IRSender
    {
    private:
        static void mark(uint16_t duration);
        static void space(uint16_t duration);

    public:
        static void send_raw(uint16_t *data, uint16_t len);
    };
}

#endif