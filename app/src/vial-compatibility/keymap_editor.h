#pragma once
// requires CONFIG_SETTINGS_RUNTIME
// there is a potential to use a custom handler or something like that,
// but that is a worsť case scenario if CONFIG_SETTINGS_RUNTIME doesnt work
//#define CONFIG_SETTINGS_RUNTIME
#include <zephyr/settings/settings.h>
//#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>

#include "keymap.c"

#include <dt-bindings/zmk/keys.h>

bool loaded=false;

/*
struct zmk_behavior_binding_storage {
    uint32_t index;
    uint32_t param1;
    uint32_t param2;
};*/



//struct zmk_behavior_binding_storage zmk_keymap_storage[ZMK_KEYMAP_LAYERS_LEN][ZMK_KEYMAP_LEN];

void init_storage_array();

int change_mapping( int layer, uint32_t position,char* behaviour_dev,uint32_t param1,uint32_t param2);

int find_binding_name(char * name);