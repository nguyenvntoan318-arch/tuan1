#include <stdint.h>
#include "button.h"

/* Thanh ghi la o dieu khien phan cung tai dia chi co dinh.
 * Khong su dung HAL, STD/SPL, Arduino hoac CMSIS.
 * stdint.h chi dinh nghia kieu so nguyen, khong cau hinh ngoai vi.
 */
#define REG32(address) (*(volatile uint32_t *)(address))

#define RCC_APB2ENR REG32(0x40021018u)
#define GPIOA_CRL   REG32(0x40010800u)
#define GPIOA_IDR   REG32(0x40010808u)
#define GPIOA_BSRR  REG32(0x40010810u)
#define GPIOC_CRH   REG32(0x40011004u)
#define GPIOC_BSRR  REG32(0x40011010u)

#define SYST_CSR    REG32(0xE000E010u)
#define SYST_RVR    REG32(0xE000E014u)
#define SYST_CVR    REG32(0xE000E018u)

/* Startup rieng khong doi clock: sau reset, STM32F103 dung HSI 8 MHz.
 * SysTick la bo dem thoi gian trong chip. Khong bat ngat.
 * Neu sua clock, phai sua gia tri 8000 tuong ung.
 */
static void delay_1ms(void)
{
    SYST_CSR = 0u;
    SYST_RVR = 8000u - 1u;
    SYST_CVR = 0u;
    SYST_CSR = 5u;  /* ENABLE=1, CLKSOURCE=CPU, TICKINT=0 */
    while ((SYST_CSR & (1u << 16)) == 0u) {
    }
    SYST_CSR = 0u;
}

static void gpio_init(void)
{
    /* Bat clock cho cong A (bit 2) va cong C (bit 4). */
    RCC_APB2ENR |= (1u << 2) | (1u << 4);
    (void)RCC_APB2ENR;

    /* PA0: dau vao co dien tro keo len ben trong.
     * Khong nhan = 1. Nhan nut noi PA0 voi GND = 0.
     */
    GPIOA_BSRR = 1u;
    GPIOA_CRL = (GPIOA_CRL & ~0xFu) | 0x8u;

    /* PC13: LED tren Blue Pill thong dung sang khi muc 0.
     * Dat muc 1 truoc khi chuyen sang dau ra de LED khoi dau tat.
     * Output push-pull 2 MHz; nhom bit cua PC13 bat dau tai bit 20.
     */
    GPIOC_BSRR = 1u << 13;
    GPIOC_CRH = (GPIOC_CRH & ~(0xFu << 20)) | (0x2u << 20);
}

static void led_write(uint8_t on)
{
    if (on != 0u) {
        GPIOC_BSRR = 1u << (13u + 16u); /* PC13 = 0: sang */
    } else {
        GPIOC_BSRR = 1u << 13;         /* PC13 = 1: tat */
    }
}

int main(void)
{
    Button button;
    uint8_t led_on = 0u;
    gpio_init();
    button_init(&button);

    while (1) {
        delay_1ms();
        uint8_t raw = (uint8_t)(GPIOA_IDR & 1u);
        if (button_update(&button, raw) != 0u) {
            led_on ^= 1u; /* 0 thanh 1; 1 thanh 0 */
            led_write(led_on);
        }
    }
}
