///scr_init();
//init game data
global.entity_activation_range = 800; //total activation range for entities
global.entity_activation_border = global.entity_activation_range-96; //range server will send packers
global.entity_deactivation_border = global.entity_activation_range-64; //range puppets will unload
global.forced_movement_decelerator = 0.925;
global.forced_movement_minimum_cutoff = 0.30;
global.client_top_gui_window = noone; //stores the id of the highest gui element
global.client_top_gui_window_setthisframe = noone; //prevent multiple depthchecks allowing a click in the same frame.
global.place_grab_range = 108;

//drag through uis
global.inventory_drag_entity = -1;
global.inventory_drag_entity_object = -1;
global.inventory_drag_objid = noone;

//client auto disconnect
global.server_alive = false;
global.timeout_time_max = 10;
global.timeout_time = global.timeout_time_max;

//console output
global.console_log[0] = "";
global.console_log[1] = "";
global.console_log[2] = "";
global.console_log[3] = "";
global.console_log[4] = "";
global.console_log[5] = "";
global.console_log[6] = "";
global.console_log[7] = "";
global.console_log[8] = "";
global.console_log[9] = "";

//gui
display_set_gui_size(576,324);

//set default socketing
global.client_socket = network_create_socket(network_socket_tcp);
global.max_server_players = 32;
network_set_config(network_config_connect_timeout, 1000);
