/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

char wpm_str[10];

enum layers {
    _DVORAK = 0,
    _QWERTY,
    _LOWER,
    _RAISE,
    _NAV,
    _ADJUST,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Dvorak
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | Tab    | ' "  | , <  | . >  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |  /  ?  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   O  | E/GUI| U/ALT|   I  |                              |   D  | H/ALT| T/GUI|   N  |   S  |  -  _  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift | ; :  |   Q  |   J  |   K  |   X  | ESC  | CAPS |  |      |      |   B  |   M  |   W  |   V  |   Z  |  \  |  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | MUTE | Del  | Raise| Space| Bspc |  | Sym  | Space| Lower|Srceen| Play/|
 *                        |      |      |      |      |      |  |      |      |      | shot | Pause|
 *                        `----------------------------------'  `----------------------------------'
 */
    [_DVORAK] = LAYOUT(
     KC_TAB , KC_QUOTE, KC_COMM,  KC_DOT            ,   KC_P            , KC_Y      ,                                                 KC_F,   KC_G              ,  KC_C              ,   KC_R ,  KC_L , KC_SLSH,
     KC_LCTL, KC_A    , KC_O   ,  MT(MOD_LGUI, KC_E), MT(MOD_LALT, KC_U), KC_I      ,                                                 KC_D,   MT(MOD_LALT, KC_H),  MT(MOD_LGUI, KC_T),   KC_N ,  KC_S , KC_MINS,
     KC_LSFT, KC_SCLN , KC_Q   ,  KC_J              ,   KC_K            , KC_X      , KC_ESC, KC_CAPS,     _______, _______         , KC_B,   KC_M              ,  KC_W              ,   KC_V ,  KC_Z , KC_BSLS,
                                  KC_MUTE           , KC_DEL            , MO(_RAISE), KC_SPC, KC_BSPC,     KC_ENT , LT(_NAV, KC_SPC), MO(_LOWER), KC_PSCR, KC_MPLY
    ),
    [_QWERTY] = LAYOUT(
        _______, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_PIPE, 
        _______, KC_A, KC_S, MT(MOD_LGUI, KC_D), MT(MOD_LALT, KC_F), KC_G, KC_H, MT(MOD_LALT, KC_J), MT(MOD_LGUI, KC_K), KC_L, KC_SCLN, KC_QUOT, 
        _______, KC_Z, KC_X, KC_C, KC_V, KC_B, _______, _______, _______, _______, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Lower Layer: Numpad, Media
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F7   | F8   | F9   | F10  |      |                              | / ?  | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | F4   | F5   | F6   | F11  |      |                              | *    | 4 $  | 5 %  | 6 ^  | , <  | +      |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | F1   | F2   | F3   | F12  |      |      |      |  |      |      | 0 )  | 1 !  | 2 @  | 3 #  | = +  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
        _______, KC_F7, KC_F8, KC_F9  , KC_F10 , _______,                                     KC_SLSH, KC_7, KC_8, KC_9, KC_MINS, _______, 
        _______, KC_F4, KC_F5, KC_F6  , KC_F11 , _______,                                     KC_ASTR, KC_4, KC_5, KC_6, KC_COMM, KC_PLUS, 
        _______, KC_F1, KC_F2, KC_F3  , KC_F12 , _______, _______, _______,     _______, _______, KC_0,    KC_1, KC_2, KC_3, KC_EQL,  _______, 
                               _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),
/*
 * Raise Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  ]   |  )   |  }   |  |   |                              |      |  _   |  €   |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  [   |  (   |  {   |  `   |                              |   +  |  -   |  /   |  *   |  %   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  $   |  @   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   | '  " |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
        KC_ESC , KC_EXLM, KC_RBRC, KC_RPRN, KC_RCBR, KC_PIPE,                                         _______, KC_UNDS, ALGR(KC_5), _______, _______, _______, 
        _______, KC_HASH, KC_LBRC, KC_LPRN, KC_LCBR, KC_GRV,                                          KC_PLUS, KC_MINS, KC_SLSH   , KC_ASTR, KC_PERC, _______, 
        _______, KC_PERC, KC_CIRC, KC_DLR,  KC_AT,   KC_TILD, _______, _______,     _______, _______, KC_AMPR, KC_EQL , KC_COMM   , KC_DOT,  KC_QUOT, _______, 
                                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),
/*
 * Navigation Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      | PgUp | Home | End  | PgDn | ScrlLk |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |   m3 | Left | Down | Up   | Right| CapsLk |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |   m1 |mLeft |mDown |  mUp |mRight|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                         _______, KC_PGUP, KC_HOME, KC_END , KC_PGDN, _______, 
        _______, _______, _______, _______, _______, _______,                                         MS_BTN3, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_CAPS, 
        _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, MS_BTN1, MS_LEFT, MS_DOWN, MS_UP  , MS_RGHT, _______, 
                                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
),
/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, DF(_DVORAK), _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, DF(_QWERTY), _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU,  RM_NEXT, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV,  _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

void keyboard_post_init_user(void) {
    // Call the post init code.

    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_sethsv_noeeprom(0, 150, 255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 2);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    // switch(biton32(state)) {
    //   case _DVORAK:
    //     rgblight_sethsv_noeeprom(HSV_CYAN);
    //     break;
    //   case _QWERTY:
    //     rgblight_sethsv_noeeprom(HSV_RED);
    //     break;
    //   case _LOWER:
    //     rgblight_sethsv_noeeprom(HSV_GREEN);
    //     break;
    //   case _RAISE:
    //     rgblight_sethsv_noeeprom(HSV_ORANGE);
    //     break;
    //   case _NAV:
    //     rgblight_sethsv_noeeprom(HSV_PINK);
    //     break;
    //   case _ADJUST:
    //     rgblight_sethsv_noeeprom(HSV_MAGENTA);
    //     break;
    //   default:
    //     rgblight_sethsv_noeeprom(HSV_YELLOW);
    //     break;

    // }
    return state;
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_status(void) {
    // QMK Logo and version information
    // clang-format off
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    // clang-format on

    oled_write_P(qmk_logo, false);
    oled_write_P(PSTR("Kyria "), false);
#    if defined(KEYBOARD_splitkb_kyria_rev1)
    oled_write_P(PSTR("rev1\n\n"), false);
#    elif defined(KEYBOARD_splitkb_kyria_rev2)
    oled_write_P(PSTR("rev2\n\n"), false);
#    elif defined(KEYBOARD_splitkb_kyria_rev3)
    oled_write_P(PSTR("rev3\n\n"), false);
#    endif
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _DVORAK:
            oled_write_P(PSTR("DVORAK\n"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
}

#    ifdef WPM_DISPLAY
// WPM-responsive animation stuff here
#        define IDLE_FRAMES 5
#        define IDLE_SPEED 10 // below this wpm value your animation will idle

// #define PREP_FRAMES 1 // uncomment if >1

#        define TAP_FRAMES 2
#        define TAP_SPEED 60 // above this wpm value typing animation to trigger

#        define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#        define ANIM_SIZE 636 // number of bytes in array, minimize for adequate firmware size, max is 1024
#        define LINE_SIZE 128

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;
uint8_t  current_tap_frame  = 0;

#        define FRAME_SIZE 636
static const uint16_t PROGMEM diff_regions_boundaries[9] = {58, 58, 58, 84, 92, 100, 120, 152, 174};
static const uint16_t PROGMEM diff_regions[174]          = {2, 8, 9, 15, 16, 22, 23, 25, 26, 32, 58, 79, 125, 128, 132, 159, 177, 186, 190, 192, 201, 202, 203, 205, 206, 216, 219, 253, 258, 261, 262, 285, 286, 289, 304, 308, 315, 320, 321, 347, 365, 380, 386, 389, 390, 413, 414, 451, 493, 508, 512, 543, 621, 625, 626, 631, 632, 636, 58, 69, 71, 74, 75, 79, 177, 181, 183, 187, 190, 192, 201, 202, 203, 205, 206, 216, 304, 308, 315, 320, 323, 330, 334, 338, 51, 53, 69, 76, 177, 183, 304, 307, 69, 70, 71, 77, 177, 181, 304, 307, 51, 53, 69, 76, 177, 183, 185, 188, 206, 217, 304, 307, 310, 321, 322, 323, 336, 345, 441, 451, 51, 53, 69, 76, 86, 90, 95, 97, 177, 183, 185, 188, 206, 210, 214, 218, 219, 227, 304, 307, 310, 321, 322, 323, 346, 355, 416, 417, 441, 451, 477, 480, 51, 53, 69, 76, 177, 183, 206, 217, 304, 307, 315, 319, 336, 345, 433, 441, 448, 452, 565, 572, 576, 584};
static const uint16_t PROGMEM diff_bytes_boundaries[9]   = {336, 336, 336, 397, 415, 429, 492, 570, 639};
static const char PROGMEM     diff_bytes[639]            = {126, 126, 24, 60,  102, 66, 12, 28, 112, 112, 28, 12, 116, 116, 20,  20, 124, 104, 124, 124, 112, 120, 44,  36,  124, 124, 128, 64, 64,  32, 32, 32, 32,  16,  16,  16,  16, 16, 8, 8,   4,   4,   4,   8,   48,  64,  128, 128, 128, 128, 192, 96,  48,  24,  12, 132, 198, 98,  35,  51,  17,  145, 113, 241, 113, 145, 17,  51, 35,  98,  198, 132, 12,  24,  48, 96,  192, 24,  100, 130, 2,   2,   2,  2,  2,  1,  128, 128, 128, 48, 48,  192, 193, 193, 194, 4, 8, 16, 32, 64, 128, 128, 128, 128, 128, 64, 64,  64,  64, 32,  32,  32, 32, 16, 16,  16,  16,  8,   8,   8,   8,  8, 196, 4, 196, 4,   196, 2, 194, 2,   194, 1,   1,   1,   1,   252, 15,  1,   248, 14,  31,  109, 140, 148, 148, 164, 166, 249, 224, 255, 224, 249, 166, 164, 148, 148, 140, 109, 31, 14,
                                                            248, 1,   15, 252, 192, 56, 4,  3,  12,  12,  12, 13, 1,   64,  160, 33, 34,  18,  17,  17,  17,  9,   8,   8,   8,   8,   4,   4,  8,   8,  16, 16, 16,  16,  16,  17,  15, 1,  1, 170, 170, 255, 255, 195, 191, 127, 3,   127, 191, 195, 255, 255, 170, 170, 31, 120, 192, 15,  56,  124, 219, 152, 20,  20,  18,  50,  207, 3,  255, 3,   207, 50,  18,  20,  20, 152, 219, 124, 56,  15,  192, 120, 31, 16, 16, 16, 16,  8,   8,   8,  8,   8,   4,   4,   4,   4, 4, 2,  3,  2,  2,   1,   1,   1,   1,   1,  1,   2,   2,  4,   4,   8,  8,  8,  8,   8,   7,   2,   130, 135, 31, 7, 159, 7, 28,  7,   159, 7, 159, 7,   2,   130, 32,  16,  16,  16,  17,  11,  14,  12,  24,  16,  49,  35,  98,  102, 68,  68,  71,  71,  71,  68,  68,  102, 98,  35,  49,  16,  24, 12,
                                                            6,   3,   1,  7,   8,   8,  23, 15, 1,   2,   1,  15, 15,  2,   5,   8,  0,   128, 128, 64,  64,  64,  64,  32,  32,  32,  32,  4,  2,   2,  24, 96, 128, 0,   60,  194, 1,  1,  4, 4,   2,   1,   0,   0,   0,   96,  96,  129, 130, 130, 132, 8,   16,  32,  64, 128, 0,   128, 112, 25,  6,   24,  24,  24,  27,  3,   34,  36, 20,  18,  18,  18,  11,  5,   5,  9,   9,   128, 128, 8,   4,   2,   1,  1,  2,  12, 30,  225, 0,   0,  1,   1,   128, 112, 12,  8, 4, 2,  2,  2,  4,   56,  28,  226, 1,   1,  128, 112, 12, 128, 128, 8,  4,  2,  1,   1,   2,   12,  30,  225, 0,  0, 1,   1, 129, 128, 128, 0, 1,   225, 26,  6,   9,   49,  53,  1,   138, 124, 128, 112, 12,  24,  6,   5,   152, 153, 132, 195, 124, 65,  65,  64,  32,  4,   4,   4,   4,   2,   2,  2,
                                                            1,   1,   0,  0,   0,   0,  0,  0,  0,   0,   0,  0,  128, 128, 8,   4,  2,   1,   1,   2,   12,  248, 248, 248, 248, 128, 128, 30, 225, 0,  0,  1,  1,   129, 128, 128, 0,  1,  1, 2,   67,  135, 7,   1,   184, 188, 190, 159, 95,  95,  79,  76,  128, 112, 12, 24,  6,   5,   152, 153, 132, 67,  124, 65,  65,  64,  32,  61, 124, 252, 252, 252, 252, 252, 60, 12,  63,  0,   0,   0,   0,   0,   0,  0,  0,  0,  0,   1,   3,   3,  128, 128, 8,   4,   2,   1, 1, 2,  12, 30, 225, 0,   0,   1,   1,   0,  1,   225, 26, 6,   9,   49, 53, 1,  138, 124, 128, 112, 12,  0,   0,  0, 1,   4, 4,   4,   4,   2, 2,   2,   1,   1,   122, 122, 121, 121, 121, 121, 57,  49,  136, 136, 135, 128, 48,  120, 124, 254, 255, 63,  7,   255, 255, 127, 127, 63,  62,  28,  24};

void write_frame(const uint16_t *regions, const uint16_t regions_len, const char *diff, const uint16_t diff_len) {
    uint16_t diff_index = 0;
    for (uint16_t region_index = 0; region_index < regions_len; region_index += 2) {
        uint16_t start = pgm_read_word_near(regions + region_index);
        uint16_t end   = pgm_read_word_near(regions + region_index + 1);
        oled_write_raw_range_P(diff + diff_index, start, end);
        diff_index += end - start;
    }
}

void write_frame_diff(const uint16_t region_begin, const uint16_t region_end, const uint16_t bytes_begin) {
    uint16_t diff_index = 0;
    for (uint16_t region_index = region_begin; region_index < region_end; region_index += 2) {
        uint16_t start = pgm_read_word_near(&diff_regions[region_index]);
        uint16_t end   = pgm_read_word_near(&diff_regions[region_index + 1]);
        oled_write_raw_range_P(&diff_bytes[bytes_begin + diff_index], start, end);
        diff_index += end - start;
    }
}

void write_base_frame(void) {
    oled_clear();
    const uint16_t region_begin = 0;
    const uint16_t region_end   = pgm_read_word_near(&diff_regions_boundaries[0]);
    const uint16_t bytes_begin  = 0;
    write_frame_diff(region_begin, region_end, bytes_begin);
}

void write_frame_at_index(int index) {
    write_base_frame();
    const uint16_t region_begin = pgm_read_word_near(&diff_regions_boundaries[index]);
    const uint16_t region_end   = pgm_read_word_near(&diff_regions_boundaries[index + 1]);
    const uint16_t bytes_begin  = pgm_read_word_near(&diff_bytes_boundaries[index]);
    write_frame_diff(region_begin, region_end, bytes_begin);
}

static void render_anim(void) {
    void animation_phase(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            int index          = abs(IDLE_FRAMES - 1 - current_idle_frame);
            write_frame_at_index(index);
        }
        if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
            int index = IDLE_FRAMES;
            write_frame_at_index(index);
        }
        if (get_current_wpm() >= TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            int index         = IDLE_FRAMES + 1 + abs(TAP_FRAMES - 1 - current_tap_frame);
            write_frame_at_index(index);
        }
    }

    if (get_current_wpm() != 0) {
        oled_on(); // not essential but turns on animation OLED with any alpha keypress

        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}
#    else
static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 128, 192, 224, 240, 112, 120, 56,  60,  28, 30, 14, 14, 14, 7,  7,   7,   7,   7,  7, 7,   7,   7, 7,  7,   7,   7,   7,  7,  7,  14, 14, 14,  30,  28,  60,  56,  120, 112, 240, 224, 192, 128, 128, 0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   192, 224, 240, 124, 62,  31,  15,  7,   3,   1,   128, 192, 224, 240, 120, 56,  60, 28, 30, 14, 14, 7,   7,   135, 231, 127, 31,  255, 255, 31,  127, 231, 135, 7,  7,  14,
                                              14, 30, 28,  60,  56,  120, 240, 224, 192, 128, 1,   3,   7,   15,  31,  62,  124, 240, 224, 192, 0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   240, 252, 255, 31,  7,   1,  0,   0,   192, 240, 252, 254, 255, 247, 243, 177, 176, 48,  48,  48,  48,  48,  48,  48,  120, 254, 135, 1,   0,   0,   255, 255, 0,   0,   1,   135, 254, 120, 48,  48,  48, 48, 48,  48,  48,  176, 177, 243, 247, 255, 254, 252, 240, 192, 0,   0,   1,   7,   31,  255, 252, 240, 0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,
                                              0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  255, 255, 255, 0,   0,   0,   0,   0,   254, 255, 255, 1,   1,   7,  30, 120, 225, 129, 131, 131, 134, 134, 140, 140, 152, 152, 177, 183, 254, 248, 224, 255, 255, 224, 248, 254, 183, 177, 152, 152, 140, 140, 134, 134, 131, 131, 129, 225, 120, 30, 7,   1,   1,   255, 255, 254, 0,   0,   0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   255, 255, 0,   0,   192, 192, 48,  48,  0,   0,   240, 240, 0,   0,   0,   0,   0,  0,  240, 240, 0,   0,   240, 240, 192, 192, 48,  48,  48,  48,  192, 192, 0,   0,   48,  48,  243, 243, 0,  0,  0,  0,  0,  0,   48,  48,  48,  48,  48,  48,  192, 192, 0,   0,   0,   0,  0,  0,
                                              0,  0,  255, 255, 255, 0,   0,   0,   0,   0,   127, 255, 255, 128, 128, 224, 120, 30,  135, 129, 193, 193, 97, 97, 49, 49, 25, 25, 141, 237, 127, 31, 7, 255, 255, 7, 31, 127, 237, 141, 25, 25, 49, 49, 97, 97,  193, 193, 129, 135, 30,  120, 224, 128, 128, 255, 255, 127, 0,  0,  0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   63,  63,  3,   3,   12,  12,  48,  48,  0,   0,   0,   0,   51,  51,  51,  51,  51,  51,  15,  15,  0,   0,   63,  63,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   48,  48,  63,  63,  48,  48,  0,   0,   12,  12,  51,  51,  51,  51,  51,  51,  63,  63,  0,   0,   0,   0,   0,   0,   0,   0,  0,  15,  63,  255, 248, 224, 128, 0,   0,   3,   15,  63,  127, 255, 239, 207, 141, 13,  12,  12,  12,  12, 12, 12, 12, 30, 127, 225, 128, 0,   0,   255, 255, 0,   0,   128, 225, 127, 30, 12, 12,
                                              12, 12, 12,  12,  12,  13,  141, 207, 239, 255, 127, 63,  15,  3,   0,   0,   128, 224, 248, 255, 63,  15,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   7,   15,  62, 124, 248, 240, 224, 192, 128, 1,   3,   7,   15,  30,  28,  60,  56,  120, 112, 112, 224, 224, 225, 231, 254, 248, 255, 255, 248, 254, 231, 225, 224, 224, 112, 112, 120, 56, 60, 28,  30,  15,  7,   3,   1,   128, 192, 224, 240, 248, 124, 62,  15,  7,   3,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,
                                              0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   3,   7,   15, 14, 30,  28,  60,  56,  120, 112, 112, 112, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 112, 112, 112, 120, 56,  60,  28,  30,  14,  15,  7,  3,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}
#    endif

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
#    ifdef WPM_DISPLAY
        render_anim();
        oled_set_cursor(0, 6);
        sprintf(wpm_str, "       WPM: %03d", get_current_wpm());
        oled_write(wpm_str, false);
#    else
        render_kyria_logo();
#    endif
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _NAV:
            // Mouse wheel up, down
            if (clockwise) {
                tap_code(MS_WHLU);
            } else {
                tap_code(MS_WHLD);
            }
            break;
        case _ADJUST:
            // Screen brightness control
            if (clockwise) {
                tap_code(KC_BRIGHTNESS_DOWN);
            } else {
                tap_code(KC_BRIGHTNESS_UP);
            }
            break;
        default:
            // Volume control
            if (clockwise) {
                tap_code(KC_VOLD);
            } else {
                tap_code(KC_VOLU);
            }
            break;
    }
    return false;
}
#endif
