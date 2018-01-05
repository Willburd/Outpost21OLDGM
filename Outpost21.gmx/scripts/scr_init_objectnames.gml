///scr_init_objectnames()
global.obj_names = ds_list_create();

//living entities
global.obj_names[| obj_puppet] = "Blank";
global.obj_names[| obj_puppet_player] = "Player";
global.obj_names[| obj_puppet_arrivalshuttle] = "";
global.obj_names[| obj_puppet_borb] = "Borb";
global.obj_names[| obj_puppet_laserpoint] = "";

//food
global.obj_names[| obj_puppet_cup] = "Cup";
global.obj_names[| obj_puppet_coffeepack] = "Coffee Pack";
global.obj_names[| obj_puppet_coffee_hot] = "Coffee";
global.obj_names[| obj_puppet_coffee_microwaved] = "Coffee";
global.obj_names[| obj_puppet_coffee_cold] = "Coffee (Cold)";

//clothing/equipment
global.obj_names[| obj_puppet_toolbelt] = "Toolbelt";
global.obj_names[| obj_puppet_medbelt] = "Medical Belt";
global.obj_names[| obj_puppet_secbelt] = "Security Belt";
global.obj_names[| obj_puppet_hazardvest] = "Hazard Vest";
global.obj_names[| obj_puppet_hardhat] = "Hard Hat";
global.obj_names[| obj_puppet_firehelmet] = "Fire Helmet";
global.obj_names[| obj_puppet_sechelmet] = "Security Helmet";
global.obj_names[| obj_puppet_firesuit] = "Fire Suit";
global.obj_names[| obj_puppet_secgasmask] = "Security Gasmask";
global.obj_names[| obj_puppet_gasmask] = "Gasmask";
global.obj_names[| obj_puppet_secarmor] = "Body Armor";
global.obj_names[| obj_puppet_riotarmor] = "Riot Armor";
global.obj_names[| obj_puppet_bombarmor] = "Bomb Armor";
global.obj_names[| obj_puppet_weldgogs] = "Welding goggles";
global.obj_names[| obj_puppet_goggles] = "Goggles";
global.obj_names[| obj_puppet_nitrogloves] = "Nitro Gloves";
global.obj_names[| obj_puppet_sterilmask] = "Steril Mask";
global.obj_names[| obj_puppet_cleansuit_helmet] = "Cleansuit Helmet";
global.obj_names[| obj_puppet_cleansuit_body] = "Cleansuit Body";
global.obj_names[| obj_puppet_sunglasses] = "Sunglasses";
global.obj_names[| obj_puppet_glasses_perscrip] = "Glasses";

//tools
global.obj_names[| obj_puppet_crowbar] = "Crowbar";
global.obj_names[| obj_puppet_wirecutter] = "Wirecutter";
global.obj_names[| obj_puppet_screwdriver] = "Screwdriver";
global.obj_names[| obj_puppet_weldtool] = "Welder";
global.obj_names[| obj_puppet_wrench] = "Wrench";
global.obj_names[| obj_puppet_laserrifle] = "M34e Ion-Rifle";
global.obj_names[| obj_puppet_powercell] = "Powercell";
global.obj_names[| obj_puppet_securitycard] = "Security Card";
global.obj_names[| obj_puppet_securitytool] = "Security Tool";
global.obj_names[| obj_puppet_flashlight] = "Flashlight";
global.obj_names[| obj_puppet_flare] = "Flare";
global.obj_names[| obj_puppet_radioA] = "Shortwave radio";
global.obj_names[| obj_puppet_umbrella] = "Lead Umbrella";
global.obj_names[| obj_puppet_paper] = "Paper";
global.obj_names[| obj_puppet_pen] = "Pen";
global.obj_names[| obj_puppet_pencil] = "Pencil";
global.obj_names[| obj_puppet_bucket] = "Bucket";
global.obj_names[| obj_puppet_mop] = "Mop";
global.obj_names[| obj_puppet_fireex] = "Fire Extinguisher";
global.obj_names[| obj_puppet_fireaxe] = "Fire Axe";
global.obj_names[| obj_puppet_stunbaton] = "Stun Baton";
global.obj_names[| obj_puppet_pepperspray] = "Pepper Spray";
global.obj_names[| obj_puppet_taser] = "Taser";
global.obj_names[| obj_puppet_flashbang] = "Flashbang";
global.obj_names[| obj_puppet_emp] = "Emp";
global.obj_names[| obj_puppet_handcuffs] = "Handcuffs";
global.obj_names[| obj_puppet_secflashlight] = "Sec. Flashlight";
global.obj_names[| obj_puppet_fluidspec] = "Fluid Spectrometer";
global.obj_names[| obj_puppet_stethoscope] = "Stethoscope";
global.obj_names[| obj_puppet_bandaid_box] = "Box of Bandaids";
global.obj_names[| obj_puppet_bandaid] = "Bandaid";
global.obj_names[| obj_puppet_burnointment] = "Burn Ointment";
global.obj_names[| obj_puppet_disinfectant] = "Disinfectant";
global.obj_names[| obj_puppet_antitoxin] = "Antitoxin";
global.obj_names[| obj_puppet_epinephrine] = "Epinephrine";
global.obj_names[| obj_puppet_syringe] = "Syringe";
global.obj_names[| obj_puppet_hypoinject] = "Hypo-Injector";
global.obj_names[| obj_puppet_beaker] = "Beaker";
global.obj_names[| obj_puppet_pillbottle] = "Pillbottle";
global.obj_names[| obj_puppet_scalpel] = "Scalpel";
global.obj_names[| obj_puppet_hemostat] = "Hemostat";
global.obj_names[| obj_puppet_sutures] = "Sutures";
global.obj_names[| obj_puppet_surgerysaw] = "Surgical Saw";
global.obj_names[| obj_puppet_surgerydrill] = "Surgical Drill";
global.obj_names[| obj_puppet_cauterytool] = "Cautery Tool";
global.obj_names[| obj_puppet_cryobeaker] = "Cryo-Beaker";
global.obj_names[| obj_puppet_gps] = "Mining GPS";
global.obj_names[| obj_puppet_labeler] = "Labeler";
global.obj_names[| obj_puppet_ducttape] = "Duct Tape";
global.obj_names[| obj_puppet_cautiontape] = "Caution Tape";
global.obj_names[| obj_puppet_clipboard] = "Clipboard";

//furniture
global.obj_names[| obj_furniture_stool] = "Stool";
global.obj_names[| obj_furniture_table] = "Table";
global.obj_names[| obj_furniture_trashbin] = "Trashbin";
global.obj_names[| obj_furniture_locker] = "Locker";
global.obj_names[| obj_puppet_janitorcart] = "Janitorial Service Cart";
global.obj_names[| obj_puppet_microwave] = "Microwave";
global.obj_names[| obj_puppet_coffeemaker] = "Coffeemaker";

//constructables
global.obj_names[| obj_puppet_conduit] = "Power Conduit";
global.obj_names[| obj_machine_STC] = "S.T.Constructor";

global.obj_names[| obj_puppet_blueprint] = "Blank Blueprint";

global.obj_names[| obj_puppet_blueprint_genorator] = "Generator Blueprint";
global.obj_names[| obj_machine_genorator] = "Generator";

global.obj_names[| obj_puppet_blueprint_outdoorlamp] = "Mounted Light Blueprint";
global.obj_names[| obj_machine_outdoorlamp] = "Mounted Light";

global.obj_names[| obj_machine_indoorlamp] = "Floor Light";

global.obj_names[| obj_puppet_blueprint_chargingstation] = "Charging Station Blueprint";
global.obj_names[| obj_machine_chargingstation] = "Charging Station";

global.obj_names[| obj_puppet_blueprint_printer] = "Blueprinter Blueprint";
global.obj_names[| obj_machine_blueprinter] = "Blueprinter";

global.obj_names[| obj_puppet_blueprint_fabricator] = "Fabricator Blueprint";
global.obj_names[| obj_machine_fabricator] = "Mass Fabricator";

global.obj_names[| obj_puppet_blueprint_elecassem] = "Electro-Assembler Blueprint";
global.obj_names[| obj_machine_elecassem] = "Electro-Assembler";

//resources and parts
global.obj_names[| obj_puppet_plastic_rod] = "Raw Plastic";
global.obj_names[| obj_puppet_metal_ingot] = "Metal Ingot";
global.obj_names[| obj_puppet_metal_plates] = "Metal Plates";
global.obj_names[| obj_puppet_metal_cable] = "Metal Cable";
global.obj_names[| obj_puppet_metal_frames] = "Metal Frame";
global.obj_names[| obj_puppet_parts_fabarray] = "Fabrication Array";
global.obj_names[| obj_puppet_parts_wires] = "Wire Spool";

//toolkits
global.obj_names[| obj_puppet_assistbox] = "Intern's Toolkit";
global.obj_names[| obj_puppet_cargobox] = "Mister Lifter Toolkit";
global.obj_names[| obj_puppet_commsbox] = "Bluesmooth 300 Kit";
global.obj_names[| obj_puppet_weatherbox] = "Weatherman's Companion";
global.obj_names[| obj_puppet_labbox] = "Labmaster 2000";
global.obj_names[| obj_puppet_medicbox] = "Mrs.Fixit Medkit";
global.obj_names[| obj_puppet_toolbox] = "Mr.Handy Toolkit";
global.obj_names[| obj_puppet_minebox] = "";
global.obj_names[| obj_puppet_secbox] = "Safety Sam Security Kit";
global.obj_names[| obj_puppet_atmobox] = "S.I. ATMO Toolkit";
global.obj_names[| obj_puppet_hydrobox] = "Audrey M.3 Growkit";
global.obj_names[| obj_puppet_janibox] = "";
