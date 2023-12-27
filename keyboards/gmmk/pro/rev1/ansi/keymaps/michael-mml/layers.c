
#include QMK_KEYBOARD_H
#include "def.h"

static void disable_side_leds(uint8_t led_min, uint8_t led_max) {
    int LEFT_SIDE_LED_INDICES[8]  = {SIDE_LED_LEFT_0, SIDE_LED_LEFT_1, SIDE_LED_LEFT_2, SIDE_LED_LEFT_3, SIDE_LED_LEFT_4, SIDE_LED_LEFT_5, SIDE_LED_LEFT_6, SIDE_LED_LEFT_7};
    int RIGHT_SIDE_LED_INDICES[8] = {SIDE_LED_RIGHT_0, SIDE_LED_RIGHT_1, SIDE_LED_RIGHT_2, SIDE_LED_RIGHT_3, SIDE_LED_RIGHT_4, SIDE_LED_RIGHT_5, SIDE_LED_RIGHT_6, SIDE_LED_RIGHT_7};
    for (int index = 0; index < 8; index++) {
        RGB_MATRIX_INDICATOR_SET_COLOR(LEFT_SIDE_LED_INDICES[index], 0, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(RIGHT_SIDE_LED_INDICES[index], 0, 0, 0);
    }
}

static void set_numpad_colour(uint8_t led_min, uint8_t led_max) {
    int ROW_OPERATIONS[4] = {SEVEN, EIGHT, NINE, ZERO};
    int ROW_7_8_9[4]      = {U, I, O, P};
    int ROW_4_5_6[4]      = {J, K, L, SEMICOLON_COLON};
    int ROW_1_2_3[4]      = {M, COMMA_LEFT_BRACKET, PERIOD_RIGHT_BRACKET, FORWARD_SLASH_QUESTION_MARK};
    for (int col = 0; col < 4; col++) {
        // cannot use RGB_MATRIX_INDICATOR_SET_COLOR here, possibly related to LEDs in the buffer?
        rgb_matrix_set_color(ROW_OPERATIONS[col], 255, 0, 0);
        rgb_matrix_set_color(ROW_7_8_9[col], 0, 255, 0);
        rgb_matrix_set_color(ROW_4_5_6[col], 0, 0, 255);
        rgb_matrix_set_color(ROW_1_2_3[col], 255, 255, 0);
    }
}

void determine_rgb_per_layer(uint8_t led_min, uint8_t led_max) {
    bool isCapsLockEnabled = host_keyboard_led_state().caps_lock;
    bool isNumLockEnabled  = host_keyboard_led_state().num_lock;
    switch (get_highest_layer(layer_state)) {
        case WIN: {
            if (isCapsLockEnabled) {
                RGB_MATRIX_INDICATOR_SET_COLOR(CAPS, 255, 0, 0);
            }
            if (isNumLockEnabled) {
                RGB_MATRIX_INDICATOR_SET_COLOR(SEVEN, 30, 252, 131);
            }
            disable_side_leds(led_min, led_max);
            break;
        }
        case WIN_FN: {
            rgb_matrix_set_color_all(30, 252, 131);
            set_numpad_colour(led_min, led_max);
            break;
        }
        case MAC: {
            if (isCapsLockEnabled) {
                RGB_MATRIX_INDICATOR_SET_COLOR(CAPS, 0, 30, 255);
            }
            if (isNumLockEnabled) {
                RGB_MATRIX_INDICATOR_SET_COLOR(SEVEN, 207, 207, 207);
            }
            disable_side_leds(led_min, led_max);
            break;
        }
        case MAC_FN: {
            rgb_matrix_set_color_all(207, 207, 207);
            set_numpad_colour(led_min, led_max);
            break;
        }
        default:
            break;
    }
}
