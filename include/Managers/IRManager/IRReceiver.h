#ifndef _IR_RECEIVER_H
#define _IR_RECEIVER_H

#include <Arduino.h>
#include <esp32-hal-timer.h>
#include "Static/Pins.h"

namespace Managers::IRManager
{
    const uint16_t MAX_IR_PULSE = 15'000;  // micro seconds
    const uint16_t PULSE_TIMEOUT = 60'000; // micro seconds
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

#pragma region esp_hal_timer
// const uint16_t MAX_IR_PULSE = 60e3; // micro seconds
// const uint16_t BUFFER_SIZE = 128;

// struct irsignal_t
// {
//     uint16_t *raw_data;
//     uint16_t raw_len;
//     // uint64_t code;

//     ~irsignal_t()
//     {
//         if (raw_data != nullptr)
//             delete[] raw_data;
//     }
// };

// class IRReceiver
// {
// private:
//     static hw_timer_t *_timer_ptr;
//     static volatile bool _signal_state;
//     static volatile uint16_t _raw_buff[];
//     static volatile uint16_t _raw_len;
//     static volatile bool _data_is_ready;
//     static volatile bool _is_enabled;

//     static void IRAM_ATTR on_timer();

// public:
//     IRReceiver() = delete;
//     ~IRReceiver() = delete;
//     static void begin();
//     static void enable();
//     static void disable();
//     static bool decode(irsignal_t &result);
// };
#pragma endregion

// class IRReceiver
// {
// private:
//     const static uint8_t _SIGNAL_TIMEOUT_MS = 130;

//     static hw_timer_t *_timer; // = nullptr
//     static volatile bool _data_is_ready;
//     static volatile bool _signal_state;        // = false
//     static volatile uint16_t _ir_data[100];    // Массив для хранения длительности импульсов
//     static int16_t _index;                     // = 0
//     static volatile uint32_t last_signal_time; // = 0

//     static void IRAM_ATTR on_timer(void);

// public:
//     static IRReceiver *_instance_ptr;

//     IRReceiver() = delete;
//     ~IRReceiver() = delete;
//     static void begin();
//     static void start_listen();
//     static void stop_listen();
//     static bool decode(irsignal_t &ir_signal);
// };