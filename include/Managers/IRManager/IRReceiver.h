#ifndef _IR_RECEIVER_H
#define _IR_RECEIVER_H

#include <Arduino.h>
#include <esp32-hal-timer.h>
#include "Static/Pins.h"

namespace Managers::IRManager
{
    const uint16_t MAX_IR_PULSE = 15000;  // micro seconds
    const uint16_t PULSE_TIMEOUT = 60000; // micro seconds
    const uint16_t RAW_BUFFER_SIZE = 128;
    const uint8_t MIN_IR_PULSES_AMOUNT = 10;

    struct irsignal_t
    {
        uint16_t *raw_data = nullptr;
        uint16_t raw_len = 0;
        // uint64_t code;

        ~irsignal_t()
        {
            if (raw_data != nullptr)
                delete[] raw_data;
        }
    };

    class IRReceiver
    {
    private:
        static volatile uint32_t _last_time;
        static volatile uint16_t _raw_buf[];
        static volatile uint16_t _raw_len;
        static volatile bool _is_receiving;
        static volatile bool _interrupt_enabled;
        // static volatile bool _

        static void IRAM_ATTR handle_ir_signal();

    public:
        IRReceiver() = delete;
        ~IRReceiver() = delete;
        static void begin();
        static void end();
        static void enable();
        static void disable();
        static bool decode(irsignal_t *result);
    };
};

#endif
