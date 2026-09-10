
typedef unsigned int uint32_t;


#define RCC_APB2ENR   (*(volatile uint32_t *)0x40021018)
#define AFIO_MAPR     (*(volatile uint32_t *)0x40010004) 
#define GPIOA_CRL     (*(volatile uint32_t *)0x40010800) 
#define GPIOA_CRH     (*(volatile uint32_t *)0x40010804) 
#define GPIOA_IDR     (*(volatile uint32_t *)0x40010808) 
#define GPIOA_ODR     (*(volatile uint32_t *)0x4001080C) 

int main(void) {
  
    RCC_APB2ENR |= (1 << 2) | (1 << 0);

    
    AFIO_MAPR |= (2 << 24);

   
    GPIOA_CRL = 0x88888888;
    
   
    GPIOA_CRH = 0x22222222;

    while (1) {
        
        GPIOA_ODR = ((~GPIOA_IDR & 0xFF) << 8) | 0xFF;
    }
}
