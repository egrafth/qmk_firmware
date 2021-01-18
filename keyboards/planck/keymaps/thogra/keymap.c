/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "special.h"

// Definitions
enum planck_layers {
  _QWERTY_GER,
  _COLEMAK,
  _DVORAK,
  _LOWER_GER,
  _RAISE_GER,
  _ADJUST_GER,
  _PLOVER,
  _QWERTY_US,
  _LOWER_US,
  _RAISE_US,
  _ADJUST_US
};

enum planck_keycodes {
  QWERTY_GER = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  QWERTY_US,
  
  GER_SHIFT,
  GER_2,
  GER_3,
  GER_6,
  GER_7,
  GER_8,
  GER_9,
  GER_0,
  GER_AE,
  GER_AMPR,
  GER_ASTR,
  GER_AT,
  GER_BSLS,
  GER_BSPC,
  GER_CIRC,
  GER_COLON,
  GER_COMMA,
  GER_DLR,
  GER_DOT,
  GER_EQL,
  GER_LBRC,
  GER_LCBR,
  GER_LPRN,
  GER_MINUS,
  GER_OE,
  GER_PIPE,
  GER_PLUS,
  GER_QUOTE,
  GER_RBRC,
  GER_RCBR,
  GER_RPRN,
  GER_SS,
  GER_SLSH,
  GER_TILD,
  GER_UE,
  GER_UNDS,
  _GER_LAST
};

// Define the keycodes for an us layout but using german os
const Key ger2      = {KC_2,    MOD_NONE,  KC_Q,    MOD_ALTGR};
const Key ger3      = {KC_3,    MOD_NONE,  KC_BSLS, MOD_NONE};
const Key ger6      = {KC_6,    MOD_NONE,  KC_GRV,  MOD_NONE};
const Key ger7      = {KC_7,    MOD_NONE,  KC_6,    MOD_SHIFT};
const Key ger8      = {KC_8,    MOD_NONE,  KC_RBRC, MOD_SHIFT};
const Key ger9      = {KC_9,    MOD_NONE,  KC_8,    MOD_SHIFT};
const Key ger0      = {KC_0,    MOD_NONE,  KC_9,    MOD_SHIFT};
const Key gerAE     = {KC_QUOT, MOD_NONE,  KC_QUOT, MOD_SHIFT};
const Key gerAMPR   = {KC_6,    MOD_SHIFT, 0,       MOD_NONE};
const Key gerASTR   = {KC_RBRC, MOD_SHIFT, 0,       MOD_NONE};
const Key gerAT     = {KC_Q,    MOD_ALTGR, 0,       MOD_NONE};
const Key gerBSLS   = {KC_MINS, MOD_ALTGR, 0,       MOD_NONE};
const Key gerBSpace = {KC_BSPC, MOD_NONE,  KC_DEL,  MOD_NONE};
const Key gerCirc   = {KC_GRV,  MOD_NONE,  0,       MOD_NONE};
const Key gerComma  = {KC_COMM, MOD_NONE,  KC_NUBS, MOD_NONE};
const Key gerColon  = {KC_COMM, MOD_SHIFT, KC_DOT,  MOD_SHIFT};
const Key gerDlr    = {KC_4,    MOD_SHIFT, KC_E,    MOD_ALTGR};
const Key gerDot    = {KC_DOT,  MOD_NONE,  KC_NUBS, MOD_SHIFT};
const Key gerEQL    = {KC_0,    MOD_SHIFT, KC_RCBR, MOD_NONE};
const Key gerLBRC   = {KC_8,    MOD_ALTGR, 0,       MOD_NONE};
const Key gerLCBR   = {KC_7,    MOD_ALTGR, KC_8,    MOD_ALTGR};
const Key gerLPRN   = {KC_8,    MOD_SHIFT, KC_8,    MOD_ALTGR};
const Key gerMinus  = {KC_SLSH, MOD_NONE,  KC_SLSH, MOD_SHIFT};
const Key gerOE     = {KC_SCLN, MOD_NONE,  KC_SCLN, MOD_SHIFT};
const Key gerPipe   = {KC_NUBS, MOD_ALTGR, 0,       MOD_NONE};
const Key gerPlus   = {KC_RBRC, MOD_NONE,  0,       MOD_NONE};
const Key gerQuote  = {KC_NUHS, MOD_SHIFT, KC_2,    MOD_SHIFT};
const Key gerRBRC   = {KC_9,    MOD_ALTGR, 0,       MOD_NONE};
const Key gerRCBR   = {KC_0,    MOD_ALTGR, KC_9,    MOD_ALTGR};
const Key gerRPRN   = {KC_9,    MOD_SHIFT, KC_9,    MOD_ALTGR};
const Key gerSS     = {KC_MINS, MOD_NONE,  KC_MINS, MOD_NONE};
const Key gerSLSH   = {KC_7,    MOD_SHIFT, KC_MINS, MOD_SHIFT};
const Key gerTilde  = {KC_RBRC, MOD_ALTGR, 0,       MOD_NONE};
const Key gerUE     = {KC_LBRC, MOD_NONE,  KC_LBRC, MOD_SHIFT};
const Key gerUNDS   = {KC_SLSH, MOD_SHIFT, 0,       MOD_NONE};

#define LOWER_GER MO(_LOWER_GER)
#define RAISE_GER MO(_RAISE_GER)
#define LOWER_US MO(_LOWER_US)
#define RAISE_US MO(_RAISE_US)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty - German
 * ,----------------------------------------------------------------------------------------------------.
 * | Esc   |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | Bksp / Del |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------------|
 * | Tab   |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   | ; / : |   ' / "    |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------------|
 * | Shift |   Z   |   X   |   C   |   V   |   B   |   N   |   M   | , / < | . / > | / / ? |   Enter    |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------------|
 * | CAPS  | GUI   | App   | Alt   | Shift | Lower | Raise | Space | Ctrl  | Left  | Down  |   Right    |
 * `----------------------------------------------------------------------------------------------------'
 */
[_QWERTY_GER] = LAYOUT_planck_grid(
    KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,      KC_Z,      KC_U,    KC_I,      KC_O,    KC_P,      GER_BSPC,
    KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,      KC_G,      KC_H,      KC_J,    KC_K,      KC_L,    GER_COLON, GER_QUOTE,
    GER_SHIFT, KC_Y,    KC_X,    KC_C,    KC_V,      KC_B,      KC_N,      KC_M,    GER_COMMA, GER_DOT, GER_SLSH,  KC_ENT ,
    KC_CAPS,   KC_LGUI, KC_APP,  KC_LALT, GER_SHIFT, LOWER_GER, RAISE_GER, KC_SPC,  KC_LCTL,   KC_LEFT, KC_DOWN,   KC_RGHT
),

/* Qwerty - US
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |Shift |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY_US] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    RGB_TOG, KC_LCTL, KC_LALT, KC_LSFT, LOWER_US, KC_LSFT, KC_SPC,  RAISE_US, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,     KC_G,    KC_J,    KC_L,     KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,     KC_D,    KC_H,    KC_N,     KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_K,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER_US, KC_SPC,  KC_SPC,  RAISE_US, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,     KC_Y,    KC_F,    KC_G,     KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_TAB,                                KC_A,    KC_O,    KC_E,    KC_U,     KC_I,    KC_D,    KC_H,     KC_T,    KC_N,    KC_S,    KC_SLSH,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,     KC_X,    KC_B,    KC_M,     KC_W,    KC_V,    KC_Z,    KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER_US, KC_SPC,  KC_SPC,  RAISE_US, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower - German
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |      |      | Pg Up|  Up  | Home |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  F5  |  F6  |  F7  |  F8  |      |      | Left | Down | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  F9  |  F10 |  F11 |  F12 |      |      | Pg Dn|      | End  |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS | OS   | APP  | Alt  | Shift| Lower| Raise| Space| Ctrl |      | Up   |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER_GER] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,   XXXXXXX,   KC_PGUP, KC_UP,   KC_HOME, XXXXXXX, GER_BSPC,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,   XXXXXXX,   KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,   XXXXXXX,   KC_PGDN, XXXXXXX, KC_END,  XXXXXXX, KC_ENT,
    _______, _______, _______, _______, _______, LOWER_GER, RAISE_GER, _______, _______, XXXXXXX, KC_UP,   XXXXXXX
),

/* Lower - US
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER_US] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise - German
 * ,----------------------------------------------------------------------------------------------------.
 * | !     | @     | $ / € | [     | {     | (     | )     | }     | ]     | #     | &     | |          |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------------|
 * | _     | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 0     |            |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------------|
 * | _     |       |       |       |       |       |       |       |       |       |       |   Enter    |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+------------|
 * |       | GUI   | Alt   | Ctrl  | Lower | Shift | Space | Raise | Left  | Down  |  Up   |   Right    |
 * `----------------------------------------------------------------------------------------------------'
 */
[_RAISE_GER] = LAYOUT_planck_grid(
    KC_EXLM,  GER_AT,  GER_DLR, GER_LBRC, GER_LCBR,  GER_LPRN,  GER_RPRN,  GER_RCBR, GER_RBRC, KC_NUBS,   GER_AMPR, GER_PIPE,
    GER_UNDS, KC_1,    GER_2,   GER_3,    KC_4,      KC_5,      GER_6,     GER_7,    GER_8,    GER_9,     GER_0,    GER_BSLS,
    GER_TILD, GER_AE,  GER_OE,  GER_UE,   GER_SS,    KC_PERC,   GER_CIRC,  GER_EQL,  GER_PLUS, GER_MINUS, GER_ASTR, GER_SLSH,
    _______,  _______, _______, KC_LALT,  GER_SHIFT, LOWER_GER, RAISE_GER, KC_SPC,   KC_LCTL,  _______,   KC_UP,    _______
),

/* Raise - US
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE_US] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust German (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |RGB Tog|RGBMod|      |      |      |      |      |      |      |      |      |Reset |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * | HUE+  | HUE- |      |      |      |      |      |Qwerty|Colemk|Dvorak|Plover|Debug |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * | SAT+  | SAT- |      |      |      |      |      |      |      | Vol+ | Vol- | Mute |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * | INT+  | INT- |      |      |      |             |      |      | Prev | Play | Next |
 * `------------------------------------------------------------------------------------'
 */
[_ADJUST_GER] = LAYOUT_planck_grid(
    RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY_GER, QWERTY_US, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
    RGB_HUI, RGB_HUD, XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK,    DVORAK,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,
    RGB_SAI, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, PLOVER,     XXXXXXX,   XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE,
    RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, _______, _______,    XXXXXXX,   XXXXXXX, XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD
),

/* Adjust US (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST_US] = LAYOUT_planck_grid(
    RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY_GER, QWERTY_US, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
    RGB_HUI, RGB_HUD, XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK,    DVORAK,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,
    RGB_SAI, RGB_SAD, XXXXXXX, XXXXXXX, XXXXXXX, PLOVER,     XXXXXXX,   XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE,
    RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, _______, _______,    XXXXXXX,   XXXXXXX, XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER_GER, _RAISE_GER, _ADJUST_GER);
  state = update_tri_layer_state(state, _LOWER_US,  _RAISE_US,  _ADJUST_US);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) 
  {
    case QWERTY_GER:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY_GER);
      }
      return false;
      break;
    case QWERTY_US:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY_US);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE_GER);
        layer_off(_RAISE_US);
        layer_off(_LOWER_GER);
        layer_off(_LOWER_US);
        layer_off(_ADJUST_GER);
        layer_off(_ADJUST_US);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
	  
    /* Special key codes so that the keyboard behaves as a US keyboard even if os assumes GER */
    case GER_SHIFT:
      pressedShift(record);
      return false;
	
    case GER_2:
      pressed(ger2, record);
      return false;

    case GER_3:
      pressed(ger3, record);
      return false;

    case GER_6:
      pressed(ger6, record);
      return false;

    case GER_7:
      pressed(ger7, record);
      return false;

    case GER_8:
      pressed(ger8, record);
      return false;

    case GER_9:
      pressed(ger9, record);
      return false;

    case GER_0:
      pressed(ger0, record);
      return false;

    case GER_AE:
      pressed(gerAE, record);
      return false;
      
    case GER_AMPR:
      pressed(gerAMPR, record);
      return false;
      
    case GER_ASTR:
      pressed(gerASTR, record);
      return false;
      
    case GER_AT:
      pressed(gerAT, record);
      return false;
      
    case GER_BSLS:
      pressed(gerBSLS, record);
      return false;

    case GER_BSPC:
      pressed(gerBSpace, record);
      return false;

    case GER_CIRC:
      pressed(gerCirc, record);
      return false;

    case GER_COLON:
      pressed(gerColon, record);
      return false;

    case GER_COMMA:
      pressed(gerComma, record);
      return false;

    case GER_DLR:
      pressed(gerDlr, record);
      return false;

    case GER_DOT:
      pressed(gerDot, record);
      return false;

    case GER_EQL:
      pressed(gerEQL, record);
      return false;

    case GER_LBRC:
      pressed(gerLBRC, record);
      return false;

    case GER_LCBR:
      pressed(gerLCBR, record);
      return false;

    case GER_LPRN:
      pressed(gerLPRN, record);
      return false;

    case GER_MINUS:
      pressed(gerMinus, record);
      return false;

    case GER_OE:
      pressed(gerOE, record);
      return false;

    case GER_PIPE:
      pressed(gerPipe, record);
      return false;

    case GER_PLUS:
      pressed(gerPlus, record);
      return false;

    case GER_QUOTE:
      pressed(gerQuote, record);
      return false;

    case GER_RBRC:
      pressed(gerRBRC, record);
      return false;

      case GER_RCBR:
      pressed(gerRCBR, record);
      return false;

    case GER_RPRN:
      pressed(gerRPRN, record);
      return false;

    case GER_SLSH:
      pressed(gerSLSH, record);
      return false;

    case GER_SS:
      pressed(gerSS, record);
      return false;

    case GER_TILD:
      pressed(gerTilde, record);
      return false;
      
    case GER_UE:
      pressed(gerUE, record);
      return false;

    case GER_UNDS:
      pressed(gerUNDS, record);
      return false;
  };
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE_GER) || IS_LAYER_ON(_RAISE_US)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST_GER);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST_GER);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE_GER:
    case LOWER_GER:
    case RAISE_US:
    case LOWER_US:
      return false;
    default:
      return true;
  }
}
