///scr_init_craftingrequirements();
global.crafting_req = ds_list_create();
global.crafting_result = ds_list_create();

//living entities
var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet] = craftlist; 
global.crafting_result[| obj_puppet] = -1;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_player] = craftlist; 
global.crafting_result[| obj_puppet_player] = -1;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_arrivalshuttle] = craftlist; 
global.crafting_result[| obj_puppet_arrivalshuttle] = -1;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_borb] = craftlist; 
global.crafting_result[| obj_puppet_borb] = -1;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_laserpoint] = craftlist; 
global.crafting_result[| obj_puppet_laserpoint] = -1;



//food
var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_cup] = craftlist; 
global.crafting_result[| obj_puppet_cup] = obj_puppet_cup;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_coffeepack] = craftlist; 
global.crafting_result[| obj_puppet_coffeepack] = obj_puppet_coffeepack;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_coffee_hot] = craftlist; 
global.crafting_result[| obj_puppet_coffee_hot] = -1;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_coffee_microwaved] = craftlist; 
global.crafting_result[| obj_puppet_coffee_microwaved] = -1;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_coffee_cold] = craftlist; 
global.crafting_result[| obj_puppet_coffee_cold] = -1;



//clothing/equipment
var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_toolbelt] = craftlist; 
global.crafting_result[| obj_puppet_toolbelt] = obj_puppet_toolbelt;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_medbelt] = craftlist; 
global.crafting_result[| obj_puppet_medbelt] = obj_puppet_medbelt;

var craftlist = ds_list_create();
global.crafting_req[| obj_puppet_secbelt] = craftlist; 
global.crafting_result[| obj_puppet_secbelt] = obj_puppet_secbelt;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_hazardvest] = craftlist; 
global.crafting_result[| obj_puppet_hazardvest] = obj_puppet_hazardvest;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_hardhat] = craftlist; 
global.crafting_result[| obj_puppet_hardhat] = obj_puppet_hardhat;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_firehelmet] = craftlist; 
global.crafting_result[| obj_puppet_firehelmet] = obj_puppet_firehelmet;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_sechelmet] = craftlist; 
global.crafting_result[| obj_puppet_sechelmet] = obj_puppet_sechelmet;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_firesuit] = craftlist; 
global.crafting_result[| obj_puppet_firesuit] = obj_puppet_firesuit;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_secgasmask] = craftlist; 
global.crafting_result[| obj_puppet_secgasmask] = obj_puppet_secgasmask;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_gasmask] = craftlist; 
global.crafting_result[| obj_puppet_gasmask] = obj_puppet_gasmask;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_secarmor] = craftlist; 
global.crafting_result[| obj_puppet_secarmor] = obj_puppet_secarmor;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_riotarmor] = craftlist; 
global.crafting_result[| obj_puppet_riotarmor] = obj_puppet_riotarmor;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_bombarmor] = craftlist; 
global.crafting_result[| obj_puppet_bombarmor] = obj_puppet_bombarmor;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_weldgogs] = craftlist; 
global.crafting_result[| obj_puppet_weldgogs] = obj_puppet_weldgogs;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_goggles] = craftlist; 
global.crafting_result[| obj_puppet_goggles] = obj_puppet_goggles;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_nitrogloves] = craftlist; 
global.crafting_result[| obj_puppet_nitrogloves] = obj_puppet_nitrogloves;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_sterilmask] = craftlist; 
global.crafting_result[| obj_puppet_sterilmask] = obj_puppet_sterilmask;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_cleansuit_helmet] = craftlist; 
global.crafting_result[| obj_puppet_cleansuit_helmet] = obj_puppet_cleansuit_helmet;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_cleansuit_body] = craftlist; 
global.crafting_result[| obj_puppet_cleansuit_body] = obj_puppet_cleansuit_body;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_sunglasses] = craftlist; 
global.crafting_result[| obj_puppet_sunglasses] = obj_puppet_sunglasses;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_glasses_perscrip] = craftlist; 
global.crafting_result[| obj_puppet_glasses_perscrip] = obj_puppet_glasses_perscrip;



//tools
var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_crowbar] = craftlist; 
global.crafting_result[| obj_puppet_crowbar] = obj_puppet_crowbar;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_wirecutter] = craftlist; 
global.crafting_result[| obj_puppet_wirecutter] = obj_puppet_wirecutter;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_screwdriver] = craftlist; 
global.crafting_result[| obj_puppet_screwdriver] = obj_puppet_screwdriver;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_weldtool] = craftlist; 
global.crafting_result[| obj_puppet_weldtool] = obj_puppet_weldtool;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_wrench] = craftlist; 
global.crafting_result[| obj_puppet_wrench] = obj_puppet_wrench;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_laserrifle] = craftlist; 
global.crafting_result[| obj_puppet_laserrifle] = obj_puppet_laserrifle;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_powercell] = craftlist; 
global.crafting_result[| obj_puppet_powercell] = obj_puppet_powercell;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_securitycard] = craftlist; 
global.crafting_result[| obj_puppet_securitycard] = obj_puppet_securitycard;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_securitytool] = craftlist; 
global.crafting_result[| obj_puppet_securitytool] = obj_puppet_securitytool;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_flashlight] = craftlist; 
global.crafting_result[| obj_puppet_flashlight] = obj_puppet_flashlight;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_flare] = craftlist; 
global.crafting_result[| obj_puppet_flare] = obj_puppet_flare;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_radioA] = craftlist; 
global.crafting_result[| obj_puppet_radioA] = obj_puppet_radioA;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_umbrella] = craftlist; 
global.crafting_result[| obj_puppet_umbrella] = obj_puppet_umbrella;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_paper] = craftlist; 
global.crafting_result[| obj_puppet_paper] = obj_puppet_paper;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_pen] = craftlist; 
global.crafting_result[| obj_puppet_pen] = obj_puppet_pen;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_pencil] = craftlist; 
global.crafting_result[| obj_puppet_pencil] = obj_puppet_pencil;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_bucket] = craftlist; 
global.crafting_result[| obj_puppet_bucket] = obj_puppet_bucket;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_mop] = craftlist; 
global.crafting_result[| obj_puppet_mop] = obj_puppet_mop;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_fireex] = craftlist; 
global.crafting_result[| obj_puppet_fireex] = obj_puppet_fireex;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_fireaxe] = craftlist; 
global.crafting_result[| obj_puppet_fireaxe] = obj_puppet_fireaxe;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_stunbaton] = craftlist; 
global.crafting_result[| obj_puppet_stunbaton] = obj_puppet_stunbaton;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_pepperspray] = craftlist; 
global.crafting_result[| obj_puppet_pepperspray] = obj_puppet_pepperspray;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_taser] = craftlist; 
global.crafting_result[| obj_puppet_taser] = obj_puppet_taser;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_flashbang] = craftlist; 
global.crafting_result[| obj_puppet_flashbang] = obj_puppet_flashbang;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_emp] = craftlist; 
global.crafting_result[| obj_puppet_emp] = obj_puppet_emp;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_handcuffs] = craftlist; 
global.crafting_result[| obj_puppet_handcuffs] = obj_puppet_handcuffs;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_secflashlight] = craftlist; 
global.crafting_result[| obj_puppet_secflashlight] = obj_puppet_secflashlight;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_fluidspec] = craftlist; 
global.crafting_result[| obj_puppet_fluidspec] = obj_puppet_fluidspec;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_stethoscope] = craftlist; 
global.crafting_result[| obj_puppet_stethoscope] = obj_puppet_stethoscope;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_bandaid_box] = craftlist; 
global.crafting_result[| obj_puppet_bandaid_box] = obj_puppet_bandaid_box;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_bandaid] = craftlist; 
global.crafting_result[| obj_puppet_bandaid] = obj_puppet_bandaid;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_burnointment] = craftlist; 
global.crafting_result[| obj_puppet_burnointment] = obj_puppet_burnointment;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_disinfectant] = craftlist; 
global.crafting_result[| obj_puppet_disinfectant] = obj_puppet_disinfectant;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_antitoxin] = craftlist; 
global.crafting_result[| obj_puppet_antitoxin] = obj_puppet_antitoxin;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_epinephrine] = craftlist; 
global.crafting_result[| obj_puppet_epinephrine] = obj_puppet_epinephrine;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_syringe] = craftlist; 
global.crafting_result[| obj_puppet_syringe] = obj_puppet_syringe;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_hypoinject] = craftlist; 
global.crafting_result[| obj_puppet_hypoinject] = obj_puppet_hypoinject;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_beaker] = craftlist; 
global.crafting_result[| obj_puppet_beaker] = obj_puppet_beaker;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_pillbottle] = craftlist; 
global.crafting_result[| obj_puppet_pillbottle] = obj_puppet_pillbottle;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_scalpel] = craftlist; 
global.crafting_result[| obj_puppet_scalpel] = obj_puppet_scalpel;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_hemostat] = craftlist; 
global.crafting_result[| obj_puppet_hemostat] = obj_puppet_hemostat;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_sutures] = craftlist; 
global.crafting_result[| obj_puppet_sutures] = obj_puppet_sutures;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_surgerysaw] = craftlist; 
global.crafting_result[| obj_puppet_surgerysaw] = obj_puppet_surgerysaw;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_surgerydrill] = craftlist; 
global.crafting_result[| obj_puppet_surgerydrill] = obj_puppet_surgerydrill;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_cauterytool] = craftlist; 
global.crafting_result[| obj_puppet_cauterytool] = obj_puppet_cauterytool;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_cryobeaker] = craftlist; 
global.crafting_result[| obj_puppet_cryobeaker] = obj_puppet_cryobeaker;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_gps] = craftlist; 
global.crafting_result[| obj_puppet_gps] = obj_puppet_gps;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_labeler] = craftlist; 
global.crafting_result[| obj_puppet_labeler] = obj_puppet_labeler;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_ducttape] = craftlist; 
global.crafting_result[| obj_puppet_ducttape] = obj_puppet_ducttape;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_cautiontape] = craftlist; 
global.crafting_result[| obj_puppet_cautiontape] = obj_puppet_cautiontape;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_clipboard] = craftlist; 
global.crafting_result[| obj_puppet_clipboard] = obj_puppet_clipboard;



//furniture
var craftlist = ds_list_create(); 
global.crafting_req[| obj_furniture_stool] = craftlist; 
global.crafting_result[| obj_furniture_stool] = obj_furniture_stool;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_furniture_table] = craftlist; 
global.crafting_result[| obj_furniture_table] = obj_furniture_table;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_furniture_trashbin] = craftlist; 
global.crafting_result[| obj_furniture_trashbin] = obj_furniture_trashbin;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_furniture_locker] = craftlist; 
global.crafting_result[| obj_furniture_locker] = obj_furniture_locker;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_janitorcart] = craftlist; 
global.crafting_result[| obj_puppet_janitorcart] = obj_puppet_janitorcart;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_microwave] = craftlist; 
global.crafting_result[| obj_puppet_microwave] = obj_puppet_microwave;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_coffeemaker] = craftlist; 
global.crafting_result[| obj_puppet_coffeemaker] = obj_puppet_coffeemaker;



//constructables
var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_metal_frames,obj_puppet_parts_wires);
global.crafting_req[| obj_puppet_conduit] = craftlist; 
global.crafting_result[| obj_puppet_conduit] = obj_puppet_conduit;

var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_metal_frames,obj_puppet_parts_fabarray);
global.crafting_req[| obj_machine_STC] = craftlist; 
global.crafting_result[| obj_machine_STC] = obj_machine_STC;


var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_metal_plates);
global.crafting_req[| obj_puppet_blueprint] = craftlist; 
global.crafting_result[| obj_puppet_blueprint] = obj_puppet_blueprint;




var craftlist = ds_list_create();  //construction
ds_list_add(craftlist, obj_puppet_blueprint_genorator,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires);
global.crafting_req[| obj_puppet_blueprint_genorator] = craftlist; 
global.crafting_result[| obj_puppet_blueprint_genorator] = obj_machine_genorator;

var craftlist = ds_list_create();  //deconstruction
ds_list_add(craftlist, obj_puppet_blueprint_genorator,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires);
global.crafting_req[| obj_machine_genorator] = craftlist; 
global.crafting_result[| obj_machine_genorator] = obj_machine_genorator;




var craftlist = ds_list_create();  //construction
ds_list_add(craftlist, obj_puppet_blueprint_outdoorlamp,obj_puppet_metal_frames,obj_puppet_parts_wires);
global.crafting_req[| obj_puppet_blueprint_outdoorlamp] = craftlist; 
global.crafting_result[| obj_puppet_blueprint_outdoorlamp] = obj_machine_outdoorlamp;

var craftlist = ds_list_create();  //deconstruction
ds_list_add(craftlist, obj_puppet_blueprint_outdoorlamp,obj_puppet_metal_frames,obj_puppet_parts_wires);
global.crafting_req[| obj_machine_outdoorlamp] = craftlist; 
global.crafting_result[| obj_machine_outdoorlamp] = obj_machine_outdoorlamp;




var craftlist = ds_list_create();  //construction
ds_list_add(craftlist, obj_puppet_blueprint_chargingstation,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires);
global.crafting_req[| obj_puppet_blueprint_chargingstation] = craftlist; 
global.crafting_result[| obj_puppet_blueprint_chargingstation] = obj_machine_chargingstation;

var craftlist = ds_list_create();  //deconstruction
ds_list_add(craftlist, obj_puppet_blueprint_chargingstation,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires);
global.crafting_req[| obj_machine_chargingstation] = craftlist; 
global.crafting_result[| obj_machine_chargingstation] = obj_machine_chargingstation;




var craftlist = ds_list_create();  //construction
ds_list_add(craftlist, obj_puppet_blueprint_printer,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires);
global.crafting_req[| obj_puppet_blueprint_printer] = craftlist; 
global.crafting_result[| obj_puppet_blueprint_printer] = obj_machine_blueprinter;

var craftlist = ds_list_create(); //deconstruction
ds_list_add(craftlist, obj_puppet_blueprint_printer,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires);
global.crafting_req[| obj_machine_blueprinter] = craftlist; 
global.crafting_result[| obj_machine_blueprinter] = obj_machine_blueprinter;




var craftlist = ds_list_create();  //construction
ds_list_add(craftlist, obj_puppet_blueprint_fabricator,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires,obj_puppet_parts_fabarray);
global.crafting_req[| obj_puppet_blueprint_fabricator] = craftlist; 
global.crafting_result[| obj_puppet_blueprint_fabricator] = obj_machine_fabricator;

var craftlist = ds_list_create();  //deconstruction
ds_list_add(craftlist, obj_puppet_blueprint_fabricator,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires,obj_puppet_parts_fabarray);
global.crafting_req[| obj_machine_fabricator] = craftlist; 
global.crafting_result[| obj_machine_fabricator] =obj_machine_fabricator;



var craftlist = ds_list_create();  //construction
ds_list_add(craftlist, obj_puppet_blueprint_elecassem,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires,obj_puppet_parts_fabarray);
global.crafting_req[| obj_puppet_blueprint_elecassem] = craftlist; 
global.crafting_result[| obj_puppet_blueprint_elecassem] = obj_machine_elecassem;

var craftlist = ds_list_create();  //deconstruction
ds_list_add(craftlist, obj_puppet_blueprint_elecassem,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires,obj_puppet_parts_fabarray);
global.crafting_req[| obj_machine_elecassem] = craftlist; 
global.crafting_result[| obj_machine_elecassem] =obj_machine_elecassem;


//resources and parts
var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_plastic_rod] = craftlist; 
global.crafting_result[| obj_puppet_plastic_rod] = obj_puppet_plastic_rod;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_metal_ingot] = craftlist; 
global.crafting_result[| obj_puppet_metal_ingot] = obj_puppet_metal_ingot;

var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_metal_ingot);
global.crafting_req[| obj_puppet_metal_plates] = craftlist; 
global.crafting_result[| obj_puppet_metal_plates] = obj_puppet_metal_plates;

var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_metal_ingot);
global.crafting_req[| obj_puppet_metal_cable] = craftlist; 
global.crafting_result[| obj_puppet_metal_cable] = obj_puppet_metal_cable;

var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_metal_ingot);
global.crafting_req[| obj_puppet_metal_frames] = craftlist; 
global.crafting_result[| obj_puppet_metal_frames] = obj_puppet_metal_frames;

var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_plastic_rod,obj_puppet_metal_cable);
global.crafting_req[| obj_puppet_parts_wires] = craftlist; 
global.crafting_result[| obj_puppet_parts_wires] = obj_puppet_parts_wires;

var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_metal_frames,obj_puppet_metal_plates,obj_puppet_parts_wires);
global.crafting_req[| obj_puppet_parts_fabarray] = craftlist; 
global.crafting_result[| obj_puppet_parts_fabarray] = obj_puppet_parts_fabarray;

var craftlist = ds_list_create(); 
ds_list_add(craftlist,obj_puppet_metal_frames,obj_puppet_parts_wires);
global.crafting_req[| obj_machine_indoorlamp] = craftlist; 
global.crafting_result[| obj_machine_indoorlamp] = obj_machine_indoorlamp;


//toolkits
var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_assistbox] = craftlist; 
global.crafting_result[| obj_puppet_assistbox] = obj_puppet_assistbox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_cargobox] = craftlist; 
global.crafting_result[| obj_puppet_cargobox] = obj_puppet_cargobox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_commsbox] = craftlist; 
global.crafting_result[| obj_puppet_commsbox] = obj_puppet_commsbox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_weatherbox] = craftlist; 
global.crafting_result[| obj_puppet_weatherbox] = obj_puppet_weatherbox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_labbox] = craftlist; 
global.crafting_result[| obj_puppet_labbox] = obj_puppet_labbox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_medicbox] = craftlist; 
global.crafting_result[| obj_puppet_medicbox] = obj_puppet_medicbox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_toolbox] = craftlist; 
global.crafting_result[| obj_puppet_toolbox] = obj_puppet_toolbox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_minebox] = craftlist; 
global.crafting_result[| obj_puppet_minebox] = obj_puppet_minebox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_secbox] = craftlist; 
global.crafting_result[| obj_puppet_secbox] = obj_puppet_secbox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_atmobox] = craftlist; 
global.crafting_result[| obj_puppet_atmobox] = obj_puppet_atmobox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_hydrobox] = craftlist; 
global.crafting_result[| obj_puppet_hydrobox] = obj_puppet_hydrobox;

var craftlist = ds_list_create(); 
global.crafting_req[| obj_puppet_janibox] = craftlist; 
global.crafting_result[| obj_puppet_janibox] = obj_puppet_janibox;

