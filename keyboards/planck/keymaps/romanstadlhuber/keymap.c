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

#define QMK_KEYBOARD_H "planck.h"  // why do it this way?

#include QMK_KEYBOARD_H
#include "muse.h"  // ok..
#include "keymap.h"
#include "quantum.h"
#include "config.h"
#include "keymap_german.h"
#include "sendstring_german.h"

// to satisfy the linter
#ifndef MATRIX_ROWS
#    define MATRIX_ROWS 4
#endif

#ifndef MATRIX_COLS
#    define MATRIX_COLS 12
#endif

/**
 * SUMMARY: the planck_layers defines an enumeration for the layers
 * operated by the keyboard
 */
enum planck_layers {
    _BASE,    // NEO 2
    _CODE,    // regular coding
    _NUMPAD,
};

enum planck_keycodes {
    _JS_LAMBDA = SAFE_RANGE,   // "" => "for use in JS lambda expressions
    _FS_ASSIGN,   // " <- " for assignments to mutables in F#
    _FS_RPIP,     // for use in F# code to pipe from left to right " |> "
    _FS_AFTER,    // F#s function chaining "after" operator " << "
    _FS_THEN,     // F#s function chaining "then operator" " >> "
    _RARRW,       // right pointing single arrow " -> " for pointers or F# expressions
    _FS_FUN,      // create an inline lambda epression with a single argument "(fun x -> y)"
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | ESC  |   X  |   V  |   L  |   C  |   W  |   K  |   H  |   G  |   F  |   Q  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | TAB  |   U  |   I  |   A  |   E  |   O  |   S  |   N  |   R  |   T  |   D  |  Y   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Ü  |   Ö  |   Ä  |   P  |   Z  |   B  |   M  |   ,  |   .  |   J  |  ß   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | CAPS |  GUI | Alt  | CTRL | MO   |    Space    |Enter | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT_planck_grid(
      KC_ESC,       DE_X,     DE_V,     DE_L,     DE_C,       DE_W,     DE_K,     DE_H,                 DE_G,     DE_F,       DE_Q,     KC_BSPC,
      KC_TAB,       DE_U,     DE_I,     DE_A,     DE_E,       DE_O,     DE_S,     DE_N,                 DE_R,     DE_T,       DE_D,     DE_Y,
      KC_LSFT,      DE_UE,    DE_OE,    DE_AE,    DE_P,       DE_Z,     DE_B,     DE_M,                 DE_COMM,  DE_DOT,     DE_J,     DE_SS,
      KC_CAPSLOCK,  KC_LGUI,  KC_LCTRL, KC_LALT,  MO(_CODE),  KC_SPC,   KC_SPC,   LT(_CODE, KC_ENTER),  KC_LEFT,  KC_DOWN,    KC_UP,    KC_RGHT
                                ),

    /* Code
     * ,-----------------------------------------------------------------------------------.
     * | ESC  |  <-  |  =>  |  ->  |  |>  |   `  |   '  |   "  |  <<  |  >>  | fun  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | TAB> |   [  |   ]  |   {  |   }  |   <  |   >  |   (  |   )  |   _  |   &  |  |   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  MO  |   /  |   ,  |   ~  |   *  |   -  |   +  |   =  |   ;  |   .  |   :  |  \   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   %  |  ^   |   #  |   @  |  MO  |    Space    |Enter | Start|PG-DWN|PG-UP | End  |
     * `-----------------------------------------------------------------------------------'
     */
    [_CODE] = LAYOUT_planck_grid(
      KC_ESC,       _FS_ASSIGN, _JS_LAMBDA, _RARRW,   _FS_RPIP,    DE_GRV,    DE_QUOT,  DE_DQUO,                _FS_AFTER,  _FS_THEN,   _FS_FUN,      KC_BSPC,
      KC_TAB,       DE_LBRC,    DE_RBRC,    DE_LCBR,  DE_RCBR,     DE_LABK,   DE_RABK,  DE_LPRN,                DE_RPRN,    DE_UNDS,    DE_AMPR,      DE_PIPE,
      MO(_NUMPAD),  DE_SLSH,    DE_TILD,    KC_DLR,   DE_ASTR,     DE_MINS,   DE_PLUS,  DE_EQL,                 DE_SCLN,    DE_DOT,     DE_COLN,      DE_BSLS,
      DE_PERC,      DE_CIRC,    DE_HASH,    DE_AT,    MO(_CODE),   KC_SPC,    KC_SPC,   LT(_NUMPAD, KC_ENTER),  KC_HOME,    KC_PGDN,    KC_PGUP,      KC_END
    ),

    /* Numpad
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |   ,  |   7  |   8  |   9  | BKSP |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |   .  |   4  |   5  |   6  | PRNT |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |   0  |   1  |   2  |   3  | SHFT |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |    SPACE    | |>|| | PREV | VOLUP|VOLDWN| NEXT |
     * `-----------------------------------------------------------------------------------'
     */
    [_NUMPAD] = LAYOUT_planck_grid(
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    DE_COMM,              DE_7,                 DE_8,                 DE_9,               KC_BSPC,
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    DE_DOT,               DE_4,                 DE_5,                 DE_6,               KC_PSCR,
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    DE_0,                 DE_1,                 DE_2,                 DE_3,               KC_RSHIFT,
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_SPC,   KC_SPC,   KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_PREV_TRACK,  KC_AUDIO_VOL_DOWN,    KC_AUDIO_VOL_UP,    KC_MEDIA_NEXT_TRACK
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
    /* [_DVORAK] = LAYOUT_planck_grid(
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
        KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
        BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ), */

    /* Lower
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
    /* [_LOWER] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
    ), */

    /* Raise
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
    /* [_RAISE] = LAYOUT_planck_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ), */

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
    /* [_PLOVER] = LAYOUT_planck_grid(
        KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
        XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
    ), */

    /* Adjust (Lower + Raise)
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
    /* [_ADJUST] = LAYOUT_planck_grid(
        _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
        _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  PLOVER,  _______,
        _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
    ) */

};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

/* layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
} */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
      case _FS_ASSIGN:
        if(record->event.pressed)
          SEND_STRING(" <- ");
      break;

      case _JS_LAMBDA:
        if(record->event.pressed)
          SEND_STRING(" => ");
      break;

      case _RARRW:
        if(record->event.pressed)
          SEND_STRING(" -> ");
      break;

      case _FS_RPIP:
        if(record->event.pressed)
          SEND_STRING(" |> ");
      break;

      case _FS_AFTER:
        if(record->event.pressed)
          SEND_STRING(" << ");
      break;

      case _FS_THEN:
        if(record->event.pressed)
          SEND_STRING(" >> ");
      break;

      case _FS_FUN:
        if(record->event.pressed)
          SEND_STRING("(fun x -> y)");
      break;
    }
    return true;
}

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

/* void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
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
} */

/* void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
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
} */

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

/* bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
} */
