///scr_init();
//init game data
global.player_light = 0;
global.weather_severity = 0;
global.entity_activation_range = 500; //total activation range for entities
//global.entity_activation_border = global.entity_activation_range-96; //range server will send packers
//global.entity_deactivation_border = global.entity_activation_range-64; //range puppets will unload
global.forced_movement_decelerator = 0.925;
global.forced_movement_minimum_cutoff = 0.30;
global.client_top_gui_window = noone; //stores the id of the highest gui element
global.client_top_gui_window_setthisframe = noone; //prevent multiple depthchecks allowing a click in the same frame.
global.place_grab_range = 108;
global.map_size = 16384;
global.map_xlimit = global.map_size-10;
global.map_ylimit = global.map_size-10;
global.maximum_movement = 20;
global.construction_mode = false;
global.server_processing_cycle = 1;

global.client_loading = true;
global.client_loading_wall_total = 0;
global.client_loading_progress = 0;
global.player_startx = 0;
global.player_starty = 0;
global.last_load_distance = 0; //distance of the furthest loaded entity
global.text_input_repeater = 0;
global.client_grab_entity = -1;
global.door_opening_duration = 120;



//serverside landing pad
enum enum_landingpad_setting {
    public,
    freight,
    private,
}

//options data filename
global.config_file_path = 'game_data.ini';
global.serverdata_file_path = 'server_data.ini';

//weather effects
global.player_indoors = false;

//shadowsurface
global.shadow_surface = -1;

//saving map data!
global.map_saved_constructions = ds_map_create();

//remote load map data
global.max_map_load_entities = 0;
global.map_loading_lock_thread[ 0] = false;

//drag through uis
global.inventory_drag_entity = -1;
global.inventory_drag_entity_object = -1;
global.inventory_drag_objid = noone;
global.inv_sprite_list = ds_list_create();

//equiped items
global.equiped_entity = -1;
global.equiped_object = noone;
global.equiped_ammo = -1;

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
network_set_config(network_config_connect_timeout, 4000);

//sub inits
scr_init_stats();
scr_init_securitylevels();
scr_init_objectnames();
scr_init_craftingrequirements();
scr_init_objectsprites();
scr_init_crafting_stations();
