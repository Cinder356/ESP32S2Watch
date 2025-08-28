#include "Managers/IRManager/IRReceiver.h"

namespace Managers::IRManager
{
    volatile uint32_t IRReceiver::_last_time;
    volatile uint16_t IRReceiver::_raw_buf[RAW_BUFFER_SIZE];
    volatile uint16_t IRReceiver::_raw_len;
    volatile bool IRReceiver::_is_receiving;
    volatile bool IRReceiver::_interrupt_enabled;

    void IRReceiver::handle_ir_signal()
    {
        if (!_interrupt_enabled)
            return;
        static uint16_t index = 0;
        uint32_t current_time = micros();
        uint32_t pulse = current_time - _last_time;
        _last_time = current_time;
        if (pulse < MAX_IR_PULSE)
        {
            // надо mux
            if (_is_receiving)
            {
                _raw_buf[index++] = (uint16_t)pulse;
                _raw_len = index;
            }
        }
        else
        {
            if (_is_receiving)
            {
                _is_receiving = false;
                _raw_buf[index++] = (uint16_t)pulse;
                _raw_len = index;
            }
            else
            {
                _is_receiving = true;
                index = 0;
            }
        }
    }

    void IRReceiver::begin()
    {
        _last_time = 0;
        _raw_len = 0;
        _is_receiving = false;
        _interrupt_enabled = false;
        pinMode(IR_RECEIVER_PIN, INPUT);
        attachInterrupt(IR_RECEIVER_PIN, handle_ir_signal, CHANGE);
        disable();
    }

    void IRReceiver::end()
    {
        detachInterrupt(IR_RECEIVER_PIN);
    }

    void IRReceiver::enable()
    {
        _interrupt_enabled = true;
        Serial.println("IRReceiver was enabled");
    }

    void IRReceiver::disable()
    {
        _interrupt_enabled = false;
        Serial.println("IRReceiver was disabled");
    }

    bool IRReceiver::decode(irsignal_t *result)
    {
        if (_raw_len >= MIN_IR_PULSES_AMOUNT && _last_time + PULSE_TIMEOUT < micros())
        {
            disable();
            uint16_t buf_len = _raw_len;
            if (result->raw_data != nullptr)
                delete[] result->raw_data;
            result->raw_data = new uint16_t[buf_len];
            result->raw_len = buf_len;
            for (uint16_t i = 0; i < buf_len; i++)
                result->raw_data[i] = _raw_buf[i];
            _is_receiving = false;
            _raw_len = 0;
            Serial.println("IR data was built");
            return true;
        }
        return false;
    }
}