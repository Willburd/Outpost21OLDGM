///scr_init_securitylevels();
global.list_security_levels = ds_list_create();

//enum for easy basic setting data
enum enum_security_basic {
    staff,
    first_custom_entry,
}

///base security levels cannot be removed!!
/****************
    Implimentation notes:
    All players simply have a security list that says what their security level is.
    It simply stores true or false for that list entry.
    So there are security levels for all areas * number of security levels in that area.
****************/



//staff doors allows all entry except for if you lack any security stuff.
var temp_map = ds_map_create();
temp_map[? "name"] = "Staff";
temp_map[? "color"] = c_ltgray;
//add data to security
global.list_security_levels[| enum_security_basic.staff ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, enum_security_basic.staff );


///entries under here will be acceptable to delete, the ones above here are present, but i might not even allow deleting normally....

//cargo
var i = enum_security_basic.first_custom_entry; //start at end of basic enum!
var temp_map = ds_map_create();
temp_map[? "name"] = "Cargo";
temp_map[? "color"] = c_fuchsia;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//communications
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Comms";
temp_map[? "color"] = c_lime;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//science
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Science";
temp_map[? "color"] = c_teal;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//medical
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Medical";
temp_map[? "color"] = c_red;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//engineering
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Engineering";
temp_map[? "color"] = c_yellow;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//security
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Security";
temp_map[? "color"] = c_black;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//atmospherics
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Atmo";
temp_map[? "color"] = c_blue;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//hydrophonics
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Hydrophonics";
temp_map[? "color"] = c_aqua;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//Filtration
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Filtration";
temp_map[? "color"] = c_olive;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );

//Management
i += 1;
var temp_map = ds_map_create();
temp_map[? "name"] = "Management";
temp_map[? "color"] = c_orange;
//add data to security
global.list_security_levels[| i ] = temp_map;
ds_list_mark_as_map(global.list_security_levels, i );
