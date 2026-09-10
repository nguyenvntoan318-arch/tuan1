#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

/* Goi button_update moi khoang 1 ms. 20 mau giong nhau moi xac nhan. */
#define BUTTON_STABLE_SAMPLES 20u

typedef struct {
    uint8_t last_raw;
    uint8_t stable;
    uint8_t count;
    uint8_t armed;
    uint8_t seen_idle;
} Button;

static inline void button_init(Button *b)
{
    b->last_raw = 1u;
    b->stable = 1u;
    b->count = 0u;
    b->armed = 0u;
    b->seen_idle = 0u;
}

/* raw = 0: dang nhan; raw = 1: dang nha.
 * Tra ve 1 DUY NHAT khi vua hoan thanh mot lan nhan roi nha.
 * Neu giu nut tu luc cap nguon, lan nha dau tien khong duoc tinh.
 */
static inline uint8_t button_update(Button *b, uint8_t raw)
{
    if (raw != b->last_raw) {
        b->last_raw = raw;
        b->count = 1u;
    } else if (b->count < BUTTON_STABLE_SAMPLES) {
        ++b->count;
    }

    if (b->count < BUTTON_STABLE_SAMPLES) {
        return 0u;
    }

    if (raw == b->stable) {
        if (raw == 1u) {
            b->seen_idle = 1u;
        }
        return 0u;
    }

    b->stable = raw;
    if (raw == 0u) {
        if (b->seen_idle != 0u) {
            b->armed = 1u;
        }
    } else {
        b->seen_idle = 1u;
        if (b->armed != 0u) {
            b->armed = 0u;
            return 1u;
        }
    }
    return 0u;
}

#endif


