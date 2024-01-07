#include "debug.h"
#include <hardware/gpio.h>
#include <pico/stdlib.h>

void blinkPattern(int pin, int blinks, int duration)
{
    for (int i = 0; i < blinks; i++)
    {
        gpio_put(pin, 1);
        sleep_ms(duration);
        gpio_put(pin, 0);
        sleep_ms(duration);
    }
}

void debugError(err_t errorCode)
{
    const int shortDuration = 100;  // Short blink duration in ms
    const int mediumDuration = 300; // Medium blink duration in ms
    const int longDuration = 600;   // Long blink duration in ms

    switch (errorCode)
    {
    case ERR_OK: // 1 short blink
        blinkPattern(PICO_DEFAULT_LED_PIN, 1, shortDuration);
        break;
    case ERR_MEM: // 2 short blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 2, shortDuration);
        break;
    case ERR_BUF: // 3 short blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 3, shortDuration);
        break;
    case ERR_TIMEOUT: // 4 short blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 4, shortDuration);
        break;
    case ERR_RTE: // 5 short blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 5, shortDuration);
        break;
    case ERR_INPROGRESS: // 1 medium blink
        blinkPattern(PICO_DEFAULT_LED_PIN, 1, mediumDuration);
        break;
    case ERR_VAL: // 2 medium blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 2, mediumDuration);
        break;
    case ERR_WOULDBLOCK: // 3 medium blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 3, mediumDuration);
        break;
    case ERR_USE: // 4 medium blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 4, mediumDuration);
        break;
    case ERR_ISCONN: // 5 medium blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 5, mediumDuration);
        break;
    case ERR_ABRT: // 1 long blink
        blinkPattern(PICO_DEFAULT_LED_PIN, 1, longDuration);
        break;
    case ERR_RST: // 2 long blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 2, longDuration);
        break;
    case ERR_CLSD: // 3 long blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 3, longDuration);
        break;
    case ERR_CONN: // 4 long blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 4, longDuration);
        break;
    case ERR_ARG: // 5 long blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 5, longDuration);
        break;
    // ... Add more cases if there are other error codes you need to handle
    default:
        // Default pattern for unknown errors - 5 very long blinks
        blinkPattern(PICO_DEFAULT_LED_PIN, 5, longDuration * 2);
        break;
    }
}
