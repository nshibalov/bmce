#include "core/keyboard.h"


#include <SDL.h>


namespace bmce
{


unsigned int sdl_keycode_to_vk(unsigned int key_code)
{
    switch (key_code)
    {
        case SDLK_RETURN: return bmce::Keyboard::VK_RETURN;
        case SDLK_ESCAPE: return bmce::Keyboard::VK_ESCAPE;
        case SDLK_BACKSPACE: return bmce::Keyboard::VK_BACKSPACE;
        case SDLK_TAB: return bmce::Keyboard::VK_TAB;
        case SDLK_SPACE: return bmce::Keyboard::VK_SPACE;
        case SDLK_EXCLAIM: return bmce::Keyboard::VK_EXCLAIM;
        case SDLK_QUOTEDBL: return bmce::Keyboard::VK_QUOTEDBL;
        case SDLK_HASH: return bmce::Keyboard::VK_HASH;
        case SDLK_PERCENT: return bmce::Keyboard::VK_PERCENT;
        case SDLK_DOLLAR: return bmce::Keyboard::VK_DOLLAR;
        case SDLK_AMPERSAND: return bmce::Keyboard::VK_AMPERSAND;
        case SDLK_QUOTE: return bmce::Keyboard::VK_QUOTE;
        case SDLK_LEFTPAREN: return bmce::Keyboard::VK_LEFTPAREN;
        case SDLK_RIGHTPAREN: return bmce::Keyboard::VK_RIGHTPAREN;
        case SDLK_ASTERISK: return bmce::Keyboard::VK_ASTERISK;
        case SDLK_PLUS: return bmce::Keyboard::VK_PLUS;
        case SDLK_COMMA: return bmce::Keyboard::VK_COMMA;
        case SDLK_MINUS: return bmce::Keyboard::VK_MINUS;
        case SDLK_PERIOD: return bmce::Keyboard::VK_PERIOD;
        case SDLK_SLASH: return bmce::Keyboard::VK_SLASH;
        case SDLK_0: return bmce::Keyboard::VK_0;
        case SDLK_1: return bmce::Keyboard::VK_1;
        case SDLK_2: return bmce::Keyboard::VK_2;
        case SDLK_3: return bmce::Keyboard::VK_3;
        case SDLK_4: return bmce::Keyboard::VK_4;
        case SDLK_5: return bmce::Keyboard::VK_5;
        case SDLK_6: return bmce::Keyboard::VK_6;
        case SDLK_7: return bmce::Keyboard::VK_7;
        case SDLK_8: return bmce::Keyboard::VK_8;
        case SDLK_9: return bmce::Keyboard::VK_9;
        case SDLK_COLON: return bmce::Keyboard::VK_COLON;
        case SDLK_SEMICOLON: return bmce::Keyboard::VK_SEMICOLON;
        case SDLK_LESS: return bmce::Keyboard::VK_LESS;
        case SDLK_EQUALS: return bmce::Keyboard::VK_EQUALS;
        case SDLK_GREATER: return bmce::Keyboard::VK_GREATER;
        case SDLK_QUESTION: return bmce::Keyboard::VK_QUESTION;
        case SDLK_AT: return bmce::Keyboard::VK_AT;
        case SDLK_LEFTBRACKET: return bmce::Keyboard::VK_LEFTBRACKET;
        case SDLK_BACKSLASH: return bmce::Keyboard::VK_BACKSLASH;
        case SDLK_RIGHTBRACKET: return bmce::Keyboard::VK_RIGHTBRACKET;
        case SDLK_CARET: return bmce::Keyboard::VK_CARET;
        case SDLK_UNDERSCORE: return bmce::Keyboard::VK_UNDERSCORE;
        case SDLK_BACKQUOTE: return bmce::Keyboard::VK_BACKQUOTE;
        case SDLK_a: return bmce::Keyboard::VK_A;
        case SDLK_b: return bmce::Keyboard::VK_B;
        case SDLK_c: return bmce::Keyboard::VK_C;
        case SDLK_d: return bmce::Keyboard::VK_D;
        case SDLK_e: return bmce::Keyboard::VK_E;
        case SDLK_f: return bmce::Keyboard::VK_F;
        case SDLK_g: return bmce::Keyboard::VK_G;
        case SDLK_h: return bmce::Keyboard::VK_H;
        case SDLK_i: return bmce::Keyboard::VK_I;
        case SDLK_j: return bmce::Keyboard::VK_J;
        case SDLK_k: return bmce::Keyboard::VK_K;
        case SDLK_l: return bmce::Keyboard::VK_L;
        case SDLK_m: return bmce::Keyboard::VK_M;
        case SDLK_n: return bmce::Keyboard::VK_N;
        case SDLK_o: return bmce::Keyboard::VK_O;
        case SDLK_p: return bmce::Keyboard::VK_P;
        case SDLK_q: return bmce::Keyboard::VK_Q;
        case SDLK_r: return bmce::Keyboard::VK_R;
        case SDLK_s: return bmce::Keyboard::VK_S;
        case SDLK_t: return bmce::Keyboard::VK_T;
        case SDLK_u: return bmce::Keyboard::VK_U;
        case SDLK_v: return bmce::Keyboard::VK_V;
        case SDLK_w: return bmce::Keyboard::VK_W;
        case SDLK_x: return bmce::Keyboard::VK_X;
        case SDLK_y: return bmce::Keyboard::VK_Y;
        case SDLK_z: return bmce::Keyboard::VK_Z;

        case SDLK_CAPSLOCK: return bmce::Keyboard::VK_CAPSLOCK;
        case SDLK_F1: return bmce::Keyboard::VK_F1;
        case SDLK_F2: return bmce::Keyboard::VK_F2;
        case SDLK_F3: return bmce::Keyboard::VK_F3;
        case SDLK_F4: return bmce::Keyboard::VK_F4;
        case SDLK_F5: return bmce::Keyboard::VK_F5;
        case SDLK_F6: return bmce::Keyboard::VK_F6;
        case SDLK_F7: return bmce::Keyboard::VK_F7;
        case SDLK_F8: return bmce::Keyboard::VK_F8;
        case SDLK_F9: return bmce::Keyboard::VK_F9;
        case SDLK_F10: return bmce::Keyboard::VK_F10;
        case SDLK_F11: return bmce::Keyboard::VK_F11;
        case SDLK_F12: return bmce::Keyboard::VK_F12;

        case SDLK_PRINTSCREEN: return bmce::Keyboard::VK_PRINTSCREEN;
        case SDLK_SCROLLLOCK: return bmce::Keyboard::VK_SCROLLLOCK;
        case SDLK_PAUSE: return bmce::Keyboard::VK_PAUSE;
        case SDLK_INSERT: return bmce::Keyboard::VK_INSERT;
        case SDLK_HOME: return bmce::Keyboard::VK_HOME;
        case SDLK_PAGEUP: return bmce::Keyboard::VK_PAGEUP;
        case SDLK_DELETE: return bmce::Keyboard::VK_DELETE;
        case SDLK_END: return bmce::Keyboard::VK_END;
        case SDLK_PAGEDOWN: return bmce::Keyboard::VK_PAGEDOWN;
        case SDLK_RIGHT: return bmce::Keyboard::VK_RIGHT;
        case SDLK_LEFT: return bmce::Keyboard::VK_LEFT;
        case SDLK_DOWN: return bmce::Keyboard::VK_DOWN;
        case SDLK_UP: return bmce::Keyboard::VK_UP;

        case SDLK_NUMLOCKCLEAR: return bmce::Keyboard::VK_NUMLOCKCLEAR;
        case SDLK_KP_DIVIDE: return bmce::Keyboard::VK_KP_DIVIDE;
        case SDLK_KP_MULTIPLY: return bmce::Keyboard::VK_KP_MULTIPLY;
        case SDLK_KP_MINUS: return bmce::Keyboard::VK_KP_MINUS;
        case SDLK_KP_PLUS: return bmce::Keyboard::VK_KP_PLUS;
        case SDLK_KP_ENTER: return bmce::Keyboard::VK_KP_ENTER;
        case SDLK_KP_1: return bmce::Keyboard::VK_KP_1;
        case SDLK_KP_2: return bmce::Keyboard::VK_KP_2;
        case SDLK_KP_3: return bmce::Keyboard::VK_KP_3;
        case SDLK_KP_4: return bmce::Keyboard::VK_KP_4;
        case SDLK_KP_5: return bmce::Keyboard::VK_KP_5;
        case SDLK_KP_6: return bmce::Keyboard::VK_KP_6;
        case SDLK_KP_7: return bmce::Keyboard::VK_KP_7;
        case SDLK_KP_8: return bmce::Keyboard::VK_KP_8;
        case SDLK_KP_9: return bmce::Keyboard::VK_KP_9;
        case SDLK_KP_0: return bmce::Keyboard::VK_KP_0;
        case SDLK_KP_PERIOD: return bmce::Keyboard::VK_KP_PERIOD;

        case SDLK_APPLICATION: return bmce::Keyboard::VK_APPLICATION;
        case SDLK_POWER: return bmce::Keyboard::VK_POWER;
        case SDLK_KP_EQUALS: return bmce::Keyboard::VK_KP_EQUALS;
        case SDLK_F13: return bmce::Keyboard::VK_F13;
        case SDLK_F14: return bmce::Keyboard::VK_F14;
        case SDLK_F15: return bmce::Keyboard::VK_F15;
        case SDLK_F16: return bmce::Keyboard::VK_F16;
        case SDLK_F17: return bmce::Keyboard::VK_F17;
        case SDLK_F18: return bmce::Keyboard::VK_F18;
        case SDLK_F19: return bmce::Keyboard::VK_F19;
        case SDLK_F20: return bmce::Keyboard::VK_F20;
        case SDLK_F21: return bmce::Keyboard::VK_F21;
        case SDLK_F22: return bmce::Keyboard::VK_F22;
        case SDLK_F23: return bmce::Keyboard::VK_F23;
        case SDLK_F24: return bmce::Keyboard::VK_F24;
        case SDLK_EXECUTE: return bmce::Keyboard::VK_EXECUTE;
        case SDLK_HELP: return bmce::Keyboard::VK_HELP;
        case SDLK_MENU: return bmce::Keyboard::VK_MENU;
        case SDLK_SELECT: return bmce::Keyboard::VK_SELECT;
        case SDLK_STOP: return bmce::Keyboard::VK_STOP;
        case SDLK_AGAIN: return bmce::Keyboard::VK_AGAIN;
        case SDLK_UNDO: return bmce::Keyboard::VK_UNDO;
        case SDLK_CUT: return bmce::Keyboard::VK_CUT;
        case SDLK_COPY: return bmce::Keyboard::VK_COPY;
        case SDLK_PASTE: return bmce::Keyboard::VK_PASTE;
        case SDLK_FIND: return bmce::Keyboard::VK_FIND;
        case SDLK_MUTE: return bmce::Keyboard::VK_MUTE;
        case SDLK_VOLUMEUP: return bmce::Keyboard::VK_VOLUMEUP;
        case SDLK_VOLUMEDOWN: return bmce::Keyboard::VK_VOLUMEDOWN;
        case SDLK_KP_COMMA: return bmce::Keyboard::VK_KP_COMMA;
        case SDLK_KP_EQUALSAS400: return bmce::Keyboard::VK_KP_EQUALSAS400;

        case SDLK_ALTERASE: return bmce::Keyboard::VK_ALTERASE;
        case SDLK_SYSREQ: return bmce::Keyboard::VK_SYSREQ;
        case SDLK_CANCEL: return bmce::Keyboard::VK_CANCEL;
        case SDLK_CLEAR: return bmce::Keyboard::VK_CLEAR;
        case SDLK_PRIOR: return bmce::Keyboard::VK_PRIOR;
        case SDLK_RETURN2: return bmce::Keyboard::VK_RETURN2;
        case SDLK_SEPARATOR: return bmce::Keyboard::VK_SEPARATOR;
        case SDLK_OUT: return bmce::Keyboard::VK_OUT;
        case SDLK_OPER: return bmce::Keyboard::VK_OPER;
        case SDLK_CLEARAGAIN: return bmce::Keyboard::VK_CLEARAGAIN;
        case SDLK_CRSEL: return bmce::Keyboard::VK_CRSEL;
        case SDLK_EXSEL: return bmce::Keyboard::VK_EXSEL;

        case SDLK_KP_00: return bmce::Keyboard::VK_KP_00;
        case SDLK_KP_000: return bmce::Keyboard::VK_KP_000;
        case SDLK_THOUSANDSSEPARATOR:
            return bmce::Keyboard::VK_THOUSANDSSEPARATOR;
        case SDLK_DECIMALSEPARATOR: return bmce::Keyboard::VK_DECIMALSEPARATOR;
        case SDLK_CURRENCYUNIT: return bmce::Keyboard::VK_CURRENCYUNIT;
        case SDLK_CURRENCYSUBUNIT: return bmce::Keyboard::VK_CURRENCYSUBUNIT;
        case SDLK_KP_LEFTPAREN: return bmce::Keyboard::VK_KP_LEFTPAREN;
        case SDLK_KP_RIGHTPAREN: return bmce::Keyboard::VK_KP_RIGHTPAREN;
        case SDLK_KP_LEFTBRACE: return bmce::Keyboard::VK_KP_LEFTBRACE;
        case SDLK_KP_RIGHTBRACE: return bmce::Keyboard::VK_KP_RIGHTBRACE;
        case SDLK_KP_TAB: return bmce::Keyboard::VK_KP_TAB;
        case SDLK_KP_BACKSPACE: return bmce::Keyboard::VK_KP_BACKSPACE;
        case SDLK_KP_A: return bmce::Keyboard::VK_KP_A;
        case SDLK_KP_B: return bmce::Keyboard::VK_KP_B;
        case SDLK_KP_C: return bmce::Keyboard::VK_KP_C;
        case SDLK_KP_D: return bmce::Keyboard::VK_KP_D;
        case SDLK_KP_E: return bmce::Keyboard::VK_KP_E;
        case SDLK_KP_F: return bmce::Keyboard::VK_KP_F;
        case SDLK_KP_XOR: return bmce::Keyboard::VK_KP_XOR;
        case SDLK_KP_POWER: return bmce::Keyboard::VK_KP_POWER;
        case SDLK_KP_PERCENT: return bmce::Keyboard::VK_KP_PERCENT;
        case SDLK_KP_LESS: return bmce::Keyboard::VK_KP_LESS;
        case SDLK_KP_GREATER: return bmce::Keyboard::VK_KP_GREATER;
        case SDLK_KP_AMPERSAND: return bmce::Keyboard::VK_KP_AMPERSAND;
        case SDLK_KP_DBLAMPERSAND: return bmce::Keyboard::VK_KP_DBLAMPERSAND;
        case SDLK_KP_VERTICALBAR: return bmce::Keyboard::VK_KP_VERTICALBAR;
        case SDLK_KP_DBLVERTICALBAR:
            return bmce::Keyboard::VK_KP_DBLVERTICALBAR;
        case SDLK_KP_COLON: return bmce::Keyboard::VK_KP_COLON;
        case SDLK_KP_HASH: return bmce::Keyboard::VK_KP_HASH;
        case SDLK_KP_SPACE: return bmce::Keyboard::VK_KP_SPACE;
        case SDLK_KP_AT: return bmce::Keyboard::VK_KP_AT;
        case SDLK_KP_EXCLAM: return bmce::Keyboard::VK_KP_EXCLAM;
        case SDLK_KP_MEMSTORE: return bmce::Keyboard::VK_KP_MEMSTORE;
        case SDLK_KP_MEMRECALL: return bmce::Keyboard::VK_KP_MEMRECALL;
        case SDLK_KP_MEMCLEAR: return bmce::Keyboard::VK_KP_MEMCLEAR;
        case SDLK_KP_MEMADD: return bmce::Keyboard::VK_KP_MEMADD;
        case SDLK_KP_MEMSUBTRACT: return bmce::Keyboard::VK_KP_MEMSUBTRACT;
        case SDLK_KP_MEMMULTIPLY: return bmce::Keyboard::VK_KP_MEMMULTIPLY;
        case SDLK_KP_MEMDIVIDE: return bmce::Keyboard::VK_KP_MEMDIVIDE;
        case SDLK_KP_PLUSMINUS: return bmce::Keyboard::VK_KP_PLUSMINUS;
        case SDLK_KP_CLEAR: return bmce::Keyboard::VK_KP_CLEAR;
        case SDLK_KP_CLEARENTRY: return bmce::Keyboard::VK_KP_CLEARENTRY;
        case SDLK_KP_BINARY: return bmce::Keyboard::VK_KP_BINARY;
        case SDLK_KP_OCTAL: return bmce::Keyboard::VK_KP_OCTAL;
        case SDLK_KP_DECIMAL: return bmce::Keyboard::VK_KP_DECIMAL;
        case SDLK_KP_HEXADECIMAL: return bmce::Keyboard::VK_KP_HEXADECIMAL;

        case SDLK_LCTRL: return bmce::Keyboard::VK_LCTRL;
        case SDLK_LSHIFT: return bmce::Keyboard::VK_LSHIFT;
        case SDLK_LALT: return bmce::Keyboard::VK_LALT;
        case SDLK_LGUI: return bmce::Keyboard::VK_LGUI;
        case SDLK_RCTRL: return bmce::Keyboard::VK_RCTRL;
        case SDLK_RSHIFT: return bmce::Keyboard::VK_RSHIFT;
        case SDLK_RALT: return bmce::Keyboard::VK_RALT;
        case SDLK_RGUI: return bmce::Keyboard::VK_RGUI;

        case SDLK_MODE: return bmce::Keyboard::VK_MODE;

        case SDLK_AUDIONEXT: return bmce::Keyboard::VK_AUDIONEXT;
        case SDLK_AUDIOPREV: return bmce::Keyboard::VK_AUDIOPREV;
        case SDLK_AUDIOSTOP: return bmce::Keyboard::VK_AUDIOSTOP;
        case SDLK_AUDIOPLAY: return bmce::Keyboard::VK_AUDIOPLAY;
        case SDLK_AUDIOMUTE: return bmce::Keyboard::VK_AUDIOMUTE;
        case SDLK_MEDIASELECT: return bmce::Keyboard::VK_MEDIASELECT;
        case SDLK_WWW: return bmce::Keyboard::VK_WWW;
        case SDLK_MAIL: return bmce::Keyboard::VK_MAIL;
        case SDLK_CALCULATOR: return bmce::Keyboard::VK_CALCULATOR;
        case SDLK_COMPUTER: return bmce::Keyboard::VK_COMPUTER;
        case SDLK_AC_SEARCH: return bmce::Keyboard::VK_AC_SEARCH;
        case SDLK_AC_HOME: return bmce::Keyboard::VK_AC_HOME;
        case SDLK_AC_BACK: return bmce::Keyboard::VK_AC_BACK;
        case SDLK_AC_FORWARD: return bmce::Keyboard::VK_AC_FORWARD;
        case SDLK_AC_STOP: return bmce::Keyboard::VK_AC_STOP;
        case SDLK_AC_REFRESH: return bmce::Keyboard::VK_AC_REFRESH;
        case SDLK_AC_BOOKMARKS: return bmce::Keyboard::VK_AC_BOOKMARKS;

        case SDLK_BRIGHTNESSDOWN: return bmce::Keyboard::VK_BRIGHTNESSDOWN;
        case SDLK_BRIGHTNESSUP: return bmce::Keyboard::VK_BRIGHTNESSUP;
        case SDLK_DISPLAYSWITCH: return bmce::Keyboard::VK_DISPLAYSWITCH;
        case SDLK_KBDILLUMTOGGLE: return bmce::Keyboard::VK_KBDILLUMTOGGLE;
        case SDLK_KBDILLUMDOWN: return bmce::Keyboard::VK_KBDILLUMDOWN;
        case SDLK_KBDILLUMUP: return bmce::Keyboard::VK_KBDILLUMUP;
        case SDLK_EJECT: return bmce::Keyboard::VK_EJECT;
        case SDLK_SLEEP: return bmce::Keyboard::VK_SLEEP;
        case SDLK_APP1: return bmce::Keyboard::VK_APP1;
        case SDLK_APP2: return bmce::Keyboard::VK_APP2;

        case SDLK_AUDIOREWIND: return bmce::Keyboard::VK_AUDIOREWIND;
        case SDLK_AUDIOFASTFORWARD: return bmce::Keyboard::VK_AUDIOFASTFORWARD;
    };

    return bmce::Keyboard::VK_UNKNOWN;
}


} // namespace bmce
