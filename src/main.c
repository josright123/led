#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    int id = 0; // mod[3] = {0, 1, 2};
    printk("Hello World! Blinky sample\n");

    bool led_state = false;

    if (!gpio_is_ready_dt(&led))
    {
        return 0;
    }

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0)
    {
        return 0;
    }

    while (1)
    {
        if (gpio_pin_toggle_dt(&led) < 0)
        {
            return 0;
        }

        led_state = !led_state;

        printk("LED state: %s\n", led_state ? "ON" : "OFF");

        switch (id)
        {
        case 0:
            printk("Hello World! Blinky sample\n");
            k_sleep(K_MSEC(1000));
            break;
        case 1:
            printk("Hello World! Blinky sample\n");
            k_sleep(K_MSEC(250));
            break;
        case 2:
            printk("Hello World! Blinky sample\n");
            k_sleep(K_MSEC(250));
            break;
        case 3:
            printk("Hello World! Blinky sample\n");
            k_sleep(K_MSEC(1500));
            break;
        default:
            break;
        }
        id = (id + 1) % 4;
    }

    return 0;
}
