#pragma once

#define SECONDS * 1000
#define MINUTES * 60 SECONDS

enum xanimos_layers {
    _ALPHA,
    _SYMBOLS,
    _NUMBERS,
    _FUNCTION,
    _GIT,
    _DEV,
    _MODS,
    _GAMING,
    _LAYERSEL,
    _MOUSE,
    _UNKOWN
};

enum macro_keycodes {
    MD_BOOT = SAFE_RANGE,
    X_MSJIG,
    X_AF1_1,
    X_ENC1,
    X_ENC2,
};

enum git_keycodes {
    // Git Commands
    G_INIT = X_ENC2 + 1,    // git init
    G_CLONE,                // git clone
    G_ADD,                  // git add
    G_DIFF,                 // git diff
    G_RESET,                // git reset --soft
    G_BRANH,                // git branch list
    G_CHECK,                // git checkout
    G_CHECKB,               // git checkout -b
    G_REMTE,                // git remote add
    G_FETCH,                // git fetch
    G_PULL,                 // git pull
    G_PUPST,                // git pull upstream
    G_PUSH,                 // git push
    G_PSORG,                // git push -u origin
    G_PSFWL,                // git push --force-with-lease
    G_COMM,                 // git commit
    G_COMSG,                // git commit -m ": [ADO-]"
    G_STAT,                 // git status
    G_LOG,                  // git log
    G_STSH,                 // git stash
    G_STLS,                 // git stash list
    G_STSP,                 // git stash pop
    G_STSW,                 // git stash show
    G_RSTS,                 // git restore --staged
    G_RVRT,                 // git revert
    G_MAIN,                 // main
    G_UPSTM,                // upstream
    G_ORIGN,                // origin
    G_HEAD,                 // HEAD~
};

#define GIT_KEYCODE_START G_INIT
#define GIT_KEYCODE_END G_HEAD

enum dev_keycodes {
    D_NPMR = GIT_KEYCODE_END + 1,
    D_NPMI,
    D_NPMU,
    D_DKR,
    D_DKE,
    D_DKCUP,
    D_DKCDN,
    D_DKCBD,
    D_DKCSP,
    D_DKCST,
    D_START,
    D_LINT,
    D_STYLE,
    D_REPRT
};

#define DEV_KEYCODE_START D_NPMR
#define DEV_KEYCODE_END D_REPRT

#define LAY_SEL     TO(_LAYERSEL)
#define M_FUNC      MO(_FUNCTION)
#define C_A_DEL     LCA(KC_DEL)
#define TD_A_MOD    TD(AL_MOD)
#define TD_C_MOD    TD(CTL_MOD)
#define TD_H_E      TD(HOME_END)
#define SFT_ENT     S(KC_ENT)
#define C_S_ESC     C(S(KC_ESC))
#define SFT_TAB     S(KC_TAB)
#define ALT_TAB     A(KC_TAB)
#define CTL_TAB     C(KC_TAB)
#define T_C_PDN     CTL_T(KC_PGDN)
#define T_S_F12     SFT_T(KC_F12)
#define T_A_END     ALT_T(KC_END)
#define ___x___     KC_NO
#define T_C_x__     CTL_T(KC_NO)
#define T_S_x__     SFT_T(KC_NO)
#define XMH_CTL     TD(MH_CTL)
#define XMH_ALT     TD(MH_ALT)
#define XMH_SFT     TD(MH_SFT)
#define XMH_GUI     TD(MH_GUI)


#define ________________QWERTY_L1__________________ KC_Q, KC_W, KC_E, KC_R, KC_T
#define ________________QWERTY_L2__________________ KC_A, KC_S, KC_D, KC_F, KC_G
#define ________________QWERTY_L3__________________ KC_Z, KC_X, KC_C, KC_V, KC_B
#define ___________QWERTY_L3_MOD_TOGGLE____________ SFT_T(KC_Z), CTL_T(KC_X) ,ALT_T(KC_C), KC_V, KC_B
#define ________________QWERTY_R1__________________ KC_Y, KC_U, KC_I, KC_O, KC_P
#define ________________QWERTY_R2__________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define ________________QWERTY_R3__________________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define ___________QWERTY_R3_MOD_TOGGLE____________ KC_N, KC_M, ALT_T(KC_COMM), CTL_T(KC_DOT), SFT_T(KC_SLSH)

#define __________________GIT_L1___________________ G_PUPST, G_PULL, G_PUSH, G_PSORG, G_PSFWL
#define __________________GIT_L2___________________ G_ADD, G_STAT, G_DIFF, G_FETCH, G_LOG
#define __________________GIT_L3___________________ G_CHECKB, G_CHECK, G_COMM, G_COMSG, G_BRANH
#define __________________GIT_R1___________________ G_INIT, G_CLONE, G_REMTE, G_RESET, G_RSTS
#define __________________GIT_R2___________________ G_STLS, G_STSH, G_STSP, G_STSW, G_RVRT
#define __________________GIT_R3___________________ G_UPSTM, G_MAIN, G_ORIGN, _______, G_HEAD

#define __________________DEV_L1___________________ ___x___, D_NPMI, D_NPMU, D_NPMR, ___x___
#define __________________DEV_L2___________________ D_DKCSP, D_DKCST, D_DKCUP, D_DKCDN, D_DKCBD
#define __________________DEV_L3___________________ D_DKR, D_DKE, ___x___, ___x___, ___x___
#define __________________DEV_R1___________________ ___x___, ___x___, ___x___, ___x___, ___x___
#define __________________DEV_R2___________________ ___x___, D_START, D_LINT , D_STYLE, D_REPRT
#define __________________DEV_R3___________________ ___x___, ___x___, ___x___, ___x___, ___x___

#ifdef OLED_ENABLE
    typedef struct layer_reset_struct {
        uint32_t last_key_press;
        bool is_led_off;
        bool has_reset;
    } layer_reset_t;

    extern layer_reset_t reset_layer;

    oled_rotation_t oled_init_km(oled_rotation_t rotation);
    bool oled_task_km(void);
    bool oled_render_logo_km(void);
#endif

bool process_record_km(uint16_t keycode, keyrecord_t *record);
