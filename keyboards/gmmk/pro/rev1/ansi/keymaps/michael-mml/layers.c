
#include QMK_KEYBOARD_H
#include "def.h"

static void disable_side_leds(uint8_t led_min, uint8_t led_max, int *leftSideLedIndices, int *rightSideLedIndices) {
    for (int ledIndex = 0; ledIndex < 8; ledIndex++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(leftSideLedIndices[ledIndex], 0, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(rightSideLedIndices[ledIndex], 0, 0, 0);
    }
}

void determine_rgb_per_layer(uint8_t led_min, uint8_t led_max) {
    int  LEFT_SIDE_LED_INDICES[8]  = {67, 70, 73, 76, 80, 83, 87, 91};
    int  RIGHT_SIDE_LED_INDICES[8] = {68, 71, 74, 77, 81, 84, 88, 92};
    bool isCapsLockEnabled         = host_keyboard_led_state().caps_lock;
    bool isNumLockEnabled          = host_keyboard_led_state().num_lock;
    switch (get_highest_layer(layer_state)) {
        case WIN: {
            if (isCapsLockEnabled) {
                RGB_MATRIX_INDICATOR_SET_COLOR(3, 255, 0, 0);
            }
            if (isNumLockEnabled) {
                RGB_MATRIX_INDICATOR_SET_COLOR(40, 30, 252, 131);
            }
            disable_side_leds(led_min, led_max, LEFT_SIDE_LED_INDICES, RIGHT_SIDE_LED_INDICES);
            break;
        }
        case WIN_FN: {
            rgb_matrix_set_color_all(30, 252, 131);
            break;
        }
        case MAC: {
            if (isCapsLockEnabled) {
                RGB_MATRIX_INDICATOR_SET_COLOR(3, 0, 30, 255);
            }
            if (isNumLockEnabled) {
                RGB_MATRIX_INDICATOR_SET_COLOR(40, 207, 207, 207);
            }
            disable_side_leds(led_min, led_max, LEFT_SIDE_LED_INDICES, RIGHT_SIDE_LED_INDICES);
            break;
        }
        case MAC_FN: {
            rgb_matrix_set_color_all(207, 207, 207);
            break;
        }
        default:
            break;
    }
}
