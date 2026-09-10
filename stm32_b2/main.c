#include <stdint.h>

#define RCC_BASE      0x40021000
#define GPIOA_BASE    0x40010800

#define RCC_APB2ENR   (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOA_CRL     (*(volatile uint32_t *)(GPIOA_BASE + 0x00)) // Quáº£n lĂ½ PA0 - PA7
#define GPIOA_ODR     (*(volatile uint32_t *)(GPIOA_BASE + 0x0C)) // Xuáº¥t dá»¯ liá»‡u

// HĂ m táº¡o trá»… (delay) tÆ°Æ¡ng Ä‘á»‘i
void delay(volatile uint32_t count) {
    while(count--) {
        // Chá»�
    }
}

int main(void) {
    // Cáº¥p xung nhá»‹p cho Port A (Náº±m á»Ÿ Bit 2 cá»§a thanh ghi APB2ENR)
    RCC_APB2ENR |= (1 << 2);

    // Cáº¥u hĂ¬nh Ä‘á»“ng loáº¡t PA0 Ä‘áº¿n PA7 lĂ  Output Push-pull, tá»‘c Ä‘á»™ 2MHz
    // Thanh ghi CRL cĂ³ 32 bit, chia Ä‘á»�u cho 8 chĂ¢n (má»—i chĂ¢n 4 bit).
    // GiĂ¡ trá»‹ 0x2 (0010) lĂ  cáº¥u hĂ¬nh output. Viáº¿t 0x22222222 sáº½ cáº¥u hĂ¬nh cáº£ 8 chĂ¢n.
    GPIOA_CRL = 0x22222222;

    while (1) {
        // VĂ²ng láº·p 1: Cháº¡y tá»« PA0 Ä‘áº¿n PA7 (TrĂ¡i sang Pháº£i)
        for (int i = 0; i <= 7; i++) {
            // DĂ¹ng mask 0xFFFFFF00 Ä‘á»ƒ xĂ³a sáº¡ch 8 bit tháº¥p (PA0-PA7) vá»� 0
            // Sau Ä‘Ă³ dĂ¹ng phĂ©p OR (|) Ä‘á»ƒ kĂ©o duy nháº¥t bit thá»© i lĂªn 1
            GPIOA_ODR = (GPIOA_ODR & 0xFFFFFF00) | (1 << i);
            delay(300000); 
        }

        // VĂ²ng láº·p 2: Cháº¡y ngÆ°á»£c tá»« PA6 lĂ¹i vá»� PA1 (Pháº£i sang TrĂ¡i)
        // LÆ°u Ă½: Cháº¡y tá»« 6 vá»� 1 Ä‘á»ƒ trĂ¡nh viá»‡c LED á»Ÿ 2 biĂªn (PA7 vĂ  PA0) bá»‹ sĂ¡ng láº·p láº¡i 2 láº§n
        for (int i = 6; i >= 1; i--) {
            GPIOA_ODR = (GPIOA_ODR & 0xFFFFFF00) | (1 << i);
            delay(300000);
        }
    }
}
