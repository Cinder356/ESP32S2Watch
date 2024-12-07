#include "Managers/IRManager/IRSender.h"

namespace Managers::IRManager
{
    void IRSender::mark(uint16_t duration)
    {
        uint32_t endTime = micros() + duration;
        while (micros() < endTime)
        {
            digitalWrite(IR_SENDER_PIN, HIGH);
            delayMicroseconds(PERIOD / 2);
            digitalWrite(IR_SENDER_PIN, LOW);
            delayMicroseconds(PERIOD / 2);
        }
    }

    void IRSender::space(uint16_t duration)
    {
        digitalWrite(IR_SENDER_PIN, LOW);
        delayMicroseconds(duration);
    }

    void IRSender::send_raw(uint16_t *data, uint16_t len)
    {
        for (int i = 0; i < len; i++)
        {
            if (i % 2 == 0)
                mark(data[i]);
            else
                space(data[i]);
        }
    }
}