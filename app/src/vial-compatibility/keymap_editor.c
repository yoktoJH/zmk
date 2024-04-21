#include "keymap_editor.h"

int find_binding_name(char *name) {

    int size = sizeof(all_names) / sizeof(char *);
    for (size_t i = 0; i < size; i++) {
        if (strcmp(name, all_names[i]) == 0) {
            return i;
        }
    }
    // this should never happen
    return -1;
}

void init_storage_array() {

    for (size_t i = 0; i < ZMK_KEYMAP_LAYERS_LEN; i++) {
        for (size_t j = 0; j < ZMK_KEYMAP_LEN; j++) {
            zmk_keymap_storage[i][j].index = find_binding_name(zmk_keymap[i][j].behavior_dev);
            zmk_keymap_storage[i][j].param1 = zmk_keymap[i][j].param1;
            zmk_keymap_storage[i][j].param2 = zmk_keymap[i][j].param2;
        }
    }
}

void save_key_mapping(int layer, int key) {
    char path[] = "vial/__/___";
    path[5] = '0' + layer % 10;
    path[6] = '0' + layer / 10;
    
    path[8] = '0' + key%10;
    path[9] = '0' + key/10%10;
    path[10] = '0' + key/10/10%10;
    
    int ret = settings_runtime_set(path, zmk_keymap_storage[layer][key],sizeof(struct zmk_behavior_binding_storage));
    if (ret != 0){
        LOG_ERR("failed to save keybind layer: %d, key %d",layer,key);
    }

}