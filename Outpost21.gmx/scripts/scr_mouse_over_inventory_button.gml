///scr_mouse_over_inventory_button();
var returner = false;
with obj_gamecontrol {
    var mouse_guix = device_mouse_x_to_gui(0);
    var mouse_guiy = device_mouse_y_to_gui(0);
    
    var tile_width = -96;
    var button_height = -32;
    var max_tiles = array_height_2d(hud_slot);
    
    for (var i=0; i<=max_tiles; i+=1) {
        if i < max_tiles {
            //draw each button
            if point_in_rectangle(mouse_guix,mouse_guiy,576+tile_width+tile_width+(i*tile_width),324+button_height,576+tile_width+(i*tile_width),324) returner = true;
        }
    }
}
return returner;
