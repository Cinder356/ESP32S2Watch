#include "Managers/IRManager/IRReceiver.h"

namespace Managers::IRManager
{
    volatile uint32_t IRReceiver::_last_time;
    volatile uint16_t IRReceiver::_raw_buf[RAW_BUFFER_SIZE];
    volatile uint16_t IRReceiver::_raw_len;
    volatile bool IRReceiver::_is_receiving;

    void IRReceiver::handle_ir_signal()
    {
        Serial.print('.');
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
        pinMode(IR_RECEIVER_PIN, INPUT);
        attachInterrupt(IR_RECEIVER_PIN, handle_ir_signal, CHANGE);
        disable();
        Serial.println("IRReceiver was begun");
    }

    void IRReceiver::end()
    {
        detachInterrupt(IR_RECEIVER_PIN);
        Serial.println("IRReceiver was ended");
    }

    void IRReceiver::enable()
    {
        enableInterrupt(IR_RECEIVER_PIN);
        Serial.println("IRReceiver was enabled");
    }

    void IRReceiver::disable()
    {
        disableInterrupt(IR_RECEIVER_PIN);
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

#pragma region esp_hal_timer
// hw_timer_t *IRReceiver::_timer_ptr;
// volatile bool IRReceiver::_signal_state;
// volatile uint16_t IRReceiver::_raw_buff[BUFFER_SIZE];
// volatile uint16_t IRReceiver::_raw_len;
// volatile bool IRReceiver::_data_is_ready;
// volatile bool IRReceiver::_is_enabled;
// portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

// void IRReceiver::on_timer()
// {
//     Serial.print(".");
//     if (!_is_enabled)
//         return;

//     static uint16_t index = 0;
//     static uint64_t last_time = 0;

//     bool current_signal = digitalRead(IR_RECEIVER_PIN);
//     // uint64_t time_space = timerReadMicros(_timer_ptr);
//     uint64_t current_time = micros();
//     uint64_t time_space = current_time - last_time;
//     last_time = current_time;
//     if (current_signal == _signal_state)
//     {
//         if (time_space > MAX_IR_PULSE) // receiving end
//         {
//             portENTER_CRITICAL_ISR(&mux);
//             _raw_len = index + 1;
//             _data_is_ready = true;
//             portEXIT_CRITICAL_ISR(&mux);
//             index = 0;
//             Serial.println("receiving end");
//         }
//         // timerStart(_timer_ptr);
//         return;
//     }
//     portENTER_CRITICAL_ISR(&mux);
//     _signal_state = current_signal;

//     if (time_space < MAX_IR_PULSE)
//     {
//         _raw_buff[index++] = (uint16_t)time_space; // мне кажется из-за приведения может быть проблема
//         Serial.printf("%d, ", time_space);
//     }
//     else // receiving start
//     {
//         Serial.println("receiving start");
//     }
//     portEXIT_CRITICAL_ISR(&mux);
//     // timerRestart(_timer_ptr);
// }

// void IRReceiver::begin()
// {
//     Serial.println("ir begin");
//     _data_is_ready = false;
//     _is_enabled = true;
//     _timer_ptr = timerBegin(1'000'000); // 1 MHz
//     timerAttachInterrupt(_timer_ptr, &IRReceiver::on_timer);
//     timerAlarm(_timer_ptr, 50, true, 0);
//     disable();
// }

// void IRReceiver::enable()
// {
//     Serial.println("ir enable");
//     portENTER_CRITICAL(&mux);
//     _is_enabled = true;
//     portEXIT_CRITICAL(&mux);
//     timerRestart(_timer_ptr);
// }

// void IRReceiver::disable()
// {
//     Serial.println("ir disable");
//     portENTER_CRITICAL(&mux);
//     _is_enabled = false;
//     portEXIT_CRITICAL(&mux);
//     timerStop(_timer_ptr);
// }

// bool IRReceiver::decode(irsignal_t &result)
// {
//     if (_data_is_ready)
//     {
//         Serial.println("building ir data");
// if (result.raw_data != nullptr)
//     delete[] result.raw_data;
// result.raw_data = new uint16_t[_raw_len];
// result.raw_len = _raw_len;
// for (uint16_t i = 0; i < _raw_len; i++)
//     result.raw_data[i] = _raw_buff[i];
// portENTER_CRITICAL(&mux);
// _data_is_ready = false;
// portEXIT_CRITICAL(&mux);
//         return true;
//     }
//     return false;
// }
#pragma endregion

// void IRReceiver::handleIRSignal() // надо через прерывание таймером делать, иначе я хз как корректно найти конец сигнала
// {
//     static uint16_t buffIndex = 0;
//
//     uint64_t currentTime = 0;
//     gptimer_get_raw_count(_gptimer, &currentTime);
//     _lastTime = currentTime;
//     if (_lastTime + IR_PULSE_TIMEOUT < currentTime && !_isReceiving) // receiving
//     {
//         _isReceiving = true;
//         buffIndex = 0;
//         return;
//     }
//     uint64_t pulseWidth = currentTime - _lastTime;
//     if (pulseWidth < 30000)
//         _rawBuff[buffIndex++] = pulseWidth;
// }

// void IRReceiver::begin()
// {
//     pinMode(IR_RECEIVER_PIN, INPUT);

//     _gptimer = NULL;
//     gptimer_config_t timer_config = {
//         .clk_src = GPTIMER_CLK_SRC_DEFAULT, // Используем стандартный источник тактирования
//         .direction = GPTIMER_COUNT_UP,      // Счетчик идет вверх
//         .resolution_hz = 1000000            // Разрешение таймера: 1 МГц (1 мкс)
//     };

//     ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &_gptimer)); // Инициализация таймера
//     ESP_ERROR_CHECK(gptimer_set_raw_count(_gptimer, 0));          // Настройка начального значения счетчика
//     ESP_ERROR_CHECK(gptimer_start(_gptimer));                     // Запуск таймера

//     // Привязка прерывания к пину IR
//     attachInterrupt(digitalPinToInterrupt(IR_RECEIVER_PIN), handleIRSignal, CHANGE);
// }

// void IRReceiver::on_timer(void)
// {
//     static unsigned long last_time = 0;
//     unsigned long current_time = micros();
//
//     // Считываем текущий сигнал с пина, подключенного к VC1838B
//     bool current_signal = digitalRead(IR_RECEIVER_PIN); // 14 — пример пина, подключите ваш пин
//
//     if (current_signal != _signal_state)
//     {
//         // Изменение состояния сигнала — зафиксировать длительность
//         _signal_state = current_signal;
//         _ir_data[_index++] = current_time - last_time;
//         last_time = current_time;
//         last_signal_time = current_time;
//
//         // Остановить запись при достижении лимита
//         if (_index >= 100)
//         {
//             _data_is_ready = true;
//             stop_listen();
//         }
//     }
//     if ((current_time - last_signal_time) > _SIGNAL_TIMEOUT_MS && _index > 0)
//     {
//         // Окончание передачи обнаружено
//         _data_is_ready = true;
//         stop_listen();
//     }
// }

// bool IRReceiver::decode(irsignal_t &ir_signal)
// {
//     if (_data_is_ready)
//     {
//         ir_signal.raw_data = _ir_data;
//         ir_signal.raw_len = _index;
//         _data_is_ready = false;
//         return true;
//     }
//     return false;
// }

// void IRReceiver::begin()
// {
//     pinMode(IR_RECEIVER_PIN, INPUT);
//     _timer = timerBegin(80);
//     timerAttachInterrupt(_timer, &IRReceiver::on_timer);
//     timerAlarm(_timer, 50, true, 0);
//     timerStop(_timer);
// }

// void IRReceiver::start_listen()
// {
//     timerRestart(_timer);
// }

// void IRReceiver::stop_listen()
// {
//     timerStop(_timer);
// }