///scr_init_crafting_stations();

/************
    Mass Fabricator Bench
************/
var i = 0;
global.crafting_array[i,0] = global.obj_names[| obj_machine_STC];
global.crafting_array[i,1] = obj_machine_STC;

i += 1;
global.crafting_array[i,0] = global.obj_names[| obj_puppet_blueprint];;
global.crafting_array[i,1] = obj_puppet_blueprint;

i += 1;
global.crafting_array[i,0] = global.obj_names[| obj_puppet_parts_wires];
global.crafting_array[i,1] = obj_puppet_parts_wires;

i += 1;
global.crafting_array[i,0] = global.obj_names[| obj_puppet_parts_fabarray];
global.crafting_array[i,1] = obj_puppet_parts_fabarray;



/************
    Electro Assembler
************/
var i = 0;
global.electro_crafting_array[i,0] = global.obj_names[| obj_puppet_parts_wires];
global.electro_crafting_array[i,1] = obj_puppet_parts_wires;

i += 1;
global.electro_crafting_array[i,0] = global.obj_names[| obj_puppet_conduit];
global.electro_crafting_array[i,1] = obj_puppet_conduit;

i += 1;
global.electro_crafting_array[i,0] = global.obj_names[| obj_machine_indoorlamp];
global.electro_crafting_array[i,1] = obj_machine_indoorlamp;



/*****************
    BluePrinter
*****************/
var i = 0;
global.blueprint_array[i,0] = global.obj_names[| obj_machine_genorator];
global.blueprint_array[i,1] = obj_puppet_blueprint_genorator;

i += 1;
global.blueprint_array[i,0] = global.obj_names[| obj_machine_chargingstation];
global.blueprint_array[i,1] = obj_puppet_blueprint_chargingstation;

i += 1;
global.blueprint_array[i,0] = global.obj_names[| obj_machine_fabricator];
global.blueprint_array[i,1] = obj_puppet_blueprint_fabricator;

i += 1;
global.blueprint_array[i,0] = global.obj_names[| obj_machine_elecassem];
global.blueprint_array[i,1] = obj_puppet_blueprint_elecassem;

i += 1;
global.blueprint_array[i,0] = global.obj_names[| obj_machine_blueprinter];
global.blueprint_array[i,1] = obj_puppet_blueprint_printer;

i += 1;
global.blueprint_array[i,0] = global.obj_names[| obj_machine_outdoorlamp];
global.blueprint_array[i,1] = obj_puppet_blueprint_outdoorlamp;
