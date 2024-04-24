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

void copy_to_storage_array(int layer, int key) {
    zmk_keymap_storage[layer][key].index = find_binding_name(zmk_keymap[layer][key].behavior_dev);
    zmk_keymap_storage[layer][key].param1 = zmk_keymap[layer][key].param1;
    zmk_keymap_storage[layer][key].param2 = zmk_keymap[layer][key].param2;
}

void copy_from_storage_array(int layer, int key) {
    zmk_keymap[layer][key].behavior_dev = all_names[zmk_keymap_storage[layer][key].index];
    zmk_keymap[layer][key].param1 = zmk_keymap_storage[layer][key].param1;
    zmk_keymap[layer][key].param2 = zmk_keymap_storage[layer][key].param2;
}

void init_storage_array() {

    for (size_t i = 0; i < ZMK_KEYMAP_LAYERS_LEN; i++) {
        for (size_t j = 0; j < ZMK_KEYMAP_LEN; j++) {
            copy_to_storage_array(i, j);
        }
    }
}

/*
static int vial_settings_cb(const char *name, size_t len, settings_read_cb read_cb,
                                      void *cb_arg, void *param) {
    const char *next;
    if (settings_name_steq(name, "state", &next) && !next) {
        if (len != sizeof()) {
            return -EINVAL;
        }

        //int rc = read_cb(cb_arg, &state, sizeof(state));
        //return MIN(rc, 0);
    }
    return -ENOENT;
}*/

void load_key_mapping(int layer, int key) {
    char path[] = "vial/__/___";
    path[5] = '0' + layer % 10;
    path[6] = '0' + layer / 10;

    path[10] = '0' + key % 10;
    path[9] = '0' + key / 10 % 10;
    path[8] = '0' + key / 10 / 10 % 10;

    int ret = settings_runtime_get(path, &(zmk_keymap_storage[layer][key]),
                                   sizeof(struct zmk_behavior_binding_storage));
    if (ret != sizeof(struct zmk_behavior_binding_storage)) {
        LOG_ERR("failed to save keybind layer: %d, key %d", layer, key);
        return;
    }
    copy_from_storage_array(layer, key);
}

void save_key_mapping(int layer, int key) {

    copy_to_storage_array(layer, key);
    char path[] = "vial/__/___";
    path[5] = '0' + layer % 10;
    path[6] = '0' + layer / 10;

    path[10] = '0' + key % 10;
    path[9] = '0' + key / 10 % 10;
    path[8] = '0' + key / 10 / 10 % 10;

    int ret = settings_runtime_set(path, &(zmk_keymap_storage[layer][key]),
                                   sizeof(struct zmk_behavior_binding_storage));
    if (ret != 0) {
        LOG_ERR("failed to save keybind layer: %d, key %d", layer, key);
    }
}

int vial_init() {
    int ret = settings_runtime_get("vial/00/000", &(zmk_keymap_storage[0][0]),
                                   sizeof(struct zmk_behavior_binding_storage));
    if (ret != sizeof(struct zmk_behavior_binding_storage)) {
        LOG_DBG("settings not yet initialized");
        for (size_t i = 0; i < ZMK_KEYMAP_LAYERS_LEN; i++) {
            for (size_t j = 0; j < ZMK_KEYMAP_LEN; j++) {
                save_key_mapping(i, j);
            }
        }
        return 0;
    }
    for (size_t i = 0; i < ZMK_KEYMAP_LAYERS_LEN; i++) {
        for (size_t j = 0; j < ZMK_KEYMAP_LEN; j++) {
            load_key_mapping(i, j);
        }
    }
}

//   SYS_INIT(zmk_backlight_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);