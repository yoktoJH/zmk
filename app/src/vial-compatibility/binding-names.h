#include <devicetree.h>

#define BCKLIGHT "backlight"
#define BLUETOOTH "bluetooth"
#define CAPS_WORD "caps_word"
#define EXTPOWER "extpower"
#define GRESC "grave_escape"
#define KP "key_press"
#define KEY_REPEAT "key_repeat"
#define KT "key_toggle"
#define LT "layer_tap"
#define MO "momentary_layer" 
#define MKP "mouse_key_press"
#define NONE "none"
#define OUT "outputs"
#define SYSRESET "sysreset"
#define BOOTLOAD "bootload"
#define RGB_UG "rgb_ug"
#define ENC_KEY_PRESS "enc_key_press"
#define STICK_KEY "sticky_key"
#define STICK_LAYER "sticky_layer"
#define TO "to_layer"
#define TOG "toggle_layer"
#define TRANS "transparent"

// things that are not in app/dts/behaviors, idk why I guess because its controllerdependent

const char* all_names[] = {DT_FOREACH_CHILD_SEP(DT_PATH(behaviours),DT_NODE_FULL_NAME,(,))} ;
// TODO add macro stuff