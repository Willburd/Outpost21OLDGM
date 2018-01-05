///scr_server_entity_flag_updateall();
for (var im = 0; im<ds_list_size(list_entities); im += 1) {
    if scr_ds_map_verify(list_entities[| im]) {
        //mark all player flags as update forced!
        scr_item_updateflag_allplayers(im,true);
    }
}
