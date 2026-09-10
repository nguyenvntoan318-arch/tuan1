
#include <stdint.h>

/* --- ĐỊNH NGHĨA CHÍNH XÁC ĐỊA CHỈ THANH GHI STM32F103 --- */
// 1. Khối RCC (Reset and Clock Control)
#define RCC_BASE        0x40021000UL
#define RCC_APB2ENR     (*((volatile uint32_t *)(RCC_BASE + 0x18)))

// 2. Khối GPIOC
#define GPIOC_BASE      0x40011000UL
#define GPIOC_CRH       (*((volatile uint32_t *)(GPIOC_BASE + 0x04)))
#define GPIOC_ODR       (*((volatile uint32_t *)(GPIOC_BASE + 0x0C)))
#define GPIOC_BSRR      (*((volatile uint32_t *)(GPIOC_BASE + 0x10)))

/* --- HÀM DELAY CHUẨN TRÁNH BIẾN TỐI ƯU CỦA GCC --- */
void delay_ms(volatile uint32_t ms) {
    while (ms--) {
        for (volatile uint32_t i = 0; i < 1500; i++) {
            __asm__("nop");
        }
    }
}

int main(void) {
    /* 1. Bật xung Clock cho PORT C (Bit 4: IOPCEN) */
    RCC_APB2ENR |= (1 << 4);

    /* 2. Cấu hình chân PC13 làm Output Push-Pull 2MHz
       - PC13 nằm ở bit 20 đến 23 của thanh ghi GPIOC_CRH.
       - Cần xóa sạch 4 bit [23:20] về 0, sau đó ghi 0b0010 (0x2) vào.
    */
    GPIOC_CRH &= ~(0xFUL << 20); // Xóa sạch cấu hình cũ của PC13
    GPIOC_CRH |=  (0x2UL << 20); // MODE13 = 10 (Output 2MHz), CNF13 = 00 (Push-Pull)

    // Tham số chu kỳ nhấp nháy (ms)
    uint32_t blink_period = 500; 

    while (1) {
        // Đảo trạng thái chân PC13 thông qua thanh ghi ODR (Bit 13)
        GPIOC_ODR ^= (1 << 13);
        
        delay_ms(blink_period);
    }

    return 0;
}
