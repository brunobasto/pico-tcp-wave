#include <hardware/gpio.h>
#include <pico-usbnet/TCP.h>
#include <pico-usbnet/USBNetwork.h>
#include <pico-adc/AdcStream.h>
#include "debug.h"

#define CAPTURE_DEPTH TCP_MSS

TCP tcp;
uint8_t readyId = 0;
bool hasData = false;
bool connected = false;

std::vector<dhcp_entry_t> dhcp = {
    {{0}, IPADDR4_INIT_BYTES(192, 168, 7, 3), 24 * 60 * 60},
};

USBNetwork network(
    IPADDR4_INIT_BYTES(192, 168, 7, 6),   // IP address
    IPADDR4_INIT_BYTES(255, 255, 255, 0), // Netmask
    IPADDR4_INIT_BYTES(192, 168, 7, 2),   // Gateway
    dhcp);

void acceptCallback(struct tcp_pcb *newpcb, err_t err)
{
    connected = 1;
    // blinkPattern(LED_PIN, 15, 25);
}

void closeCallback()
{
    connected = 0;
    // blinkPattern(LED_PIN, 15, 25);
}

void adcCallback(uint8_t id, uint8_t *buffer, int size)
{
    if (connected)
    {
        if (id == 0)
        {
            readyId = 0;
            hasData = true;
        }
        else if (id == 1)
        {
            readyId = 1;
            hasData = true;
        }
    }
}

int main()
{
    // Set up GPIO
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_init(26 + 0);
    gpio_set_dir(26 + 0, GPIO_IN);
    // gpio_set_pulls(26 + 0, false, true);

    // Set up network
    network.init();

    // Initialize TCP
    tcp.init();

    // Setup TCP callbacks
    tcp.onAccept(acceptCallback);
    tcp.onClose(closeCallback);
    tcp.onError([](err_t err) {
        // tcp.close();
        // debugError(err);
    });
    tcp.onSent([](err_t err) {
        hasData = false;
    });

    // Start listening
    tcp.bind(IP_ADDR_ANY, 5555);
    tcp.listen();

    AdcStream<uint8_t> adcStream({0}, CAPTURE_DEPTH);
    adcStream.registerCallback(adcCallback);
    adcStream.startCapture();

    bool failed = false;

    while (true)
    {
        network.work();

        if (connected && hasData)
        {
            err_t err = ERR_OK;

            if (tcp.getAvailableSize() < CAPTURE_DEPTH)
            {
                continue;
            }
            else if (readyId == 0)
            {
                err = tcp.send(adcStream.getBufferA(), CAPTURE_DEPTH);
                hasData = false;
            }
            else if (readyId == 1)
            {
                err = tcp.send(adcStream.getBufferB(), CAPTURE_DEPTH);
                hasData = false;
            }
            if (err != ERR_OK)
            {
                if (err == ERR_MEM)
                {
                    // debugError(err);
                }
                else
                {
                    connected = false;
                    failed = true;
                    debugError(err);
                    tcp.close();
                    // break;
                }
            }
        }
    }

    return 0;
}
