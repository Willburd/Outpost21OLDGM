///scr_init_objectsprites();
global.obj_sprites = ds_list_create();

//living entities
global.obj_sprites[| obj_puppet] = spr_puppetplace;
global.obj_sprites[| obj_puppet_player] = spr_puppetplace;
global.obj_sprites[| obj_puppet_arrivalshuttle] = spr_puppetplace;
global.obj_sprites[| obj_puppet_borb] = spr_borb;
global.obj_sprites[| obj_puppet_laserpoint] = spr_puppetplace;

//food
global.obj_sprites[| obj_puppet_cup] = spr_cup;
global.obj_sprites[| obj_puppet_coffeepack] = spr_coffeepack;
global.obj_sprites[| obj_puppet_coffee_hot] = spr_coffee_hot;
global.obj_sprites[| obj_puppet_coffee_cold] = spr_coffee;
global.obj_sprites[| obj_puppet_coffee_microwaved] = spr_coffee_hot;


//clothing/equipment
global.obj_sprites[| obj_puppet_toolbelt] = spr_puppetplace;
global.obj_sprites[| obj_puppet_medbelt] = spr_puppetplace;
global.obj_sprites[| obj_puppet_secbelt] = spr_puppetplace;
global.obj_sprites[| obj_puppet_hazardvest] = spr_puppetplace;
global.obj_sprites[| obj_puppet_hardhat] = spr_puppetplace;
global.obj_sprites[| obj_puppet_firehelmet] = spr_puppetplace;
global.obj_sprites[| obj_puppet_sechelmet] = spr_puppetplace;
global.obj_sprites[| obj_puppet_firesuit] = spr_puppetplace;
global.obj_sprites[| obj_puppet_secgasmask] = spr_puppetplace;
global.obj_sprites[| obj_puppet_gasmask] = spr_puppetplace;
global.obj_sprites[| obj_puppet_secarmor] = spr_puppetplace;
global.obj_sprites[| obj_puppet_riotarmor] = spr_puppetplace;
global.obj_sprites[| obj_puppet_bombarmor] = spr_puppetplace;
global.obj_sprites[| obj_puppet_weldgogs] = spr_puppetplace;
global.obj_sprites[| obj_puppet_goggles] = spr_puppetplace;
global.obj_sprites[| obj_puppet_nitrogloves] = spr_puppetplace;
global.obj_sprites[| obj_puppet_sterilmask] = spr_puppetplace;
global.obj_sprites[| obj_puppet_cleansuit_helmet] = spr_puppetplace;
global.obj_sprites[| obj_puppet_cleansuit_body] = spr_puppetplace;
global.obj_sprites[| obj_puppet_sunglasses] = spr_puppetplace;
global.obj_sprites[| obj_puppet_glasses_perscrip] = spr_puppetplace;


//tools
global.obj_sprites[| obj_puppet_crowbar] = spr_crowbar;
global.obj_sprites[| obj_puppet_wirecutter] = spr_puppetplace;
global.obj_sprites[| obj_puppet_screwdriver] = spr_screwdriver;
global.obj_sprites[| obj_puppet_weldtool] = spr_puppetplace;
global.obj_sprites[| obj_puppet_wrench] = spr_wrench;
global.obj_sprites[| obj_puppet_laserrifle] = spr_laserrifle;
global.obj_sprites[| obj_puppet_powercell] = spr_powercell_full;
global.obj_sprites[| obj_puppet_securitycard] = spr_securitycard;
global.obj_sprites[| obj_puppet_securitytool] = spr_security_tool;
global.obj_sprites[| obj_puppet_flashlight] = spr_puppetplace;
global.obj_sprites[| obj_puppet_flare] = spr_puppetplace;
global.obj_sprites[| obj_puppet_radioA] = spr_puppetplace;
global.obj_sprites[| obj_puppet_umbrella] = spr_puppetplace;
global.obj_sprites[| obj_puppet_paper] = spr_puppetplace;
global.obj_sprites[| obj_puppet_pen] = spr_puppetplace;
global.obj_sprites[| obj_puppet_pencil] = spr_puppetplace;
global.obj_sprites[| obj_puppet_bucket] = spr_puppetplace;
global.obj_sprites[| obj_puppet_mop] = spr_puppetplace;
global.obj_sprites[| obj_puppet_fireex] = spr_puppetplace;
global.obj_sprites[| obj_puppet_fireaxe] = spr_puppetplace;
global.obj_sprites[| obj_puppet_stunbaton] = spr_puppetplace;
global.obj_sprites[| obj_puppet_pepperspray] = spr_puppetplace;
global.obj_sprites[| obj_puppet_taser] = spr_puppetplace;
global.obj_sprites[| obj_puppet_flashbang] = spr_puppetplace;
global.obj_sprites[| obj_puppet_emp] = spr_puppetplace;
global.obj_sprites[| obj_puppet_handcuffs] = spr_puppetplace;
global.obj_sprites[| obj_puppet_secflashlight] = spr_puppetplace;
global.obj_sprites[| obj_puppet_fluidspec] = spr_puppetplace;
global.obj_sprites[| obj_puppet_stethoscope] = spr_puppetplace;
global.obj_sprites[| obj_puppet_bandaid_box] = spr_puppetplace;
global.obj_sprites[| obj_puppet_bandaid] = spr_puppetplace;
global.obj_sprites[| obj_puppet_burnointment] = spr_puppetplace;
global.obj_sprites[| obj_puppet_disinfectant] = spr_puppetplace;
global.obj_sprites[| obj_puppet_antitoxin] = spr_puppetplace;
global.obj_sprites[| obj_puppet_epinephrine] = spr_puppetplace;
global.obj_sprites[| obj_puppet_syringe] = spr_puppetplace;
global.obj_sprites[| obj_puppet_hypoinject] = spr_puppetplace;
global.obj_sprites[| obj_puppet_beaker] = spr_puppetplace;
global.obj_sprites[| obj_puppet_pillbottle] = spr_puppetplace;
global.obj_sprites[| obj_puppet_scalpel] = spr_puppetplace;
global.obj_sprites[| obj_puppet_hemostat] = spr_puppetplace;
global.obj_sprites[| obj_puppet_sutures] = spr_puppetplace;
global.obj_sprites[| obj_puppet_surgerysaw] = spr_puppetplace;
global.obj_sprites[| obj_puppet_surgerydrill] = spr_puppetplace;
global.obj_sprites[| obj_puppet_cauterytool] = spr_puppetplace;
global.obj_sprites[| obj_puppet_cryobeaker] = spr_puppetplace;
global.obj_sprites[| obj_puppet_gps] = spr_puppetplace;
global.obj_sprites[| obj_puppet_labeler] = spr_puppetplace;
global.obj_sprites[| obj_puppet_ducttape] = spr_puppetplace;
global.obj_sprites[| obj_puppet_cautiontape] = spr_puppetplace;
global.obj_sprites[| obj_puppet_clipboard] = spr_puppetplace;


//furniture
global.obj_sprites[| obj_furniture_stool] = spr_furniture_stool;
global.obj_sprites[| obj_furniture_table] = spr_furniture_table;
global.obj_sprites[| obj_furniture_trashbin] = spr_furniture_trashbin;
global.obj_sprites[| obj_puppet_microwave] = spr_microwave;
global.obj_sprites[| obj_puppet_coffeemaker] = spr_coffeemaker;


//constructables
global.obj_sprites[| obj_puppet_conduit] = spr_conduit_item;
global.obj_sprites[| obj_machine_STC] = spr_stc_item;
global.obj_sprites[| obj_machine_indoorlamp] = spr_floorlight_item;

global.obj_sprites[| obj_puppet_blueprint] = spr_blueprint;
global.obj_sprites[| obj_puppet_blueprint_genorator] = spr_blueprint;
global.obj_sprites[| obj_puppet_blueprint_outdoorlamp] = spr_blueprint;
global.obj_sprites[| obj_puppet_blueprint_chargingstation] = spr_blueprint;
global.obj_sprites[| obj_puppet_blueprint_fabricator] = spr_blueprint;
global.obj_sprites[| obj_puppet_blueprint_printer] = spr_blueprint;
global.obj_sprites[| obj_puppet_blueprint_elecassem] = spr_blueprint;

//resources and parts
global.obj_sprites[| obj_puppet_plastic_rod] = spr_plastic_rod;
global.obj_sprites[| obj_puppet_metal_ingot] = spr_metal_ingot;
global.obj_sprites[| obj_puppet_metal_plates] = spr_metal_plates;
global.obj_sprites[| obj_puppet_metal_cable] = spr_metal_cable;
global.obj_sprites[| obj_puppet_metal_frames] = spr_metal_frames;
global.obj_sprites[| obj_puppet_parts_fabarray] = spr_part_fabarray;
global.obj_sprites[| obj_puppet_parts_wires] = spr_wire_spool;

//toolkits
global.obj_sprites[| obj_puppet_toolbox] = spr_toolbox;


