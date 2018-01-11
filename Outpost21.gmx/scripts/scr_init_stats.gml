///scr_init_stats();
//inits race stats, arc mods, and job mods

/*******************
    RACES AND MODIFIERS
*******************/
enum enum_races {
    human,
    nevrean,
    valekin,
}

//human
var i = enum_races.human;
global.race_mod[ i, 0] =  1; //str
global.race_mod[ i, 1] =  1; //dex
global.race_mod[ i, 2] =  1; //int
global.race_mod[ i, 3] =  1; //con
global.race_mod[ i, 4] = spr_nevreanstand; //sprite
global.race_mod[ i, 5] = "Human";
global.race_mod[ i, 6] = enum_homeworlds.earth;
global.race_mod[ i, 7] = enum_homeworlds.luna;
global.race_mod[ i, 8] = enum_homeworlds.mars;
global.race_mod[ i, 9] = enum_homeworlds.offworld;
var lang_list = ds_list_create();
lang_list[| 0] = enum_language.galactic
lang_list[| 1] = enum_language.terran;
lang_list[| 2] = enum_language.martian;
global.race_mod[ i, 10] = lang_list; //additional languages

//nevrean
var i = enum_races.nevrean;
global.race_mod[ i, 0] = -1; //str
global.race_mod[ i, 1] =  2; //dex
global.race_mod[ i, 2] =  2; //int
global.race_mod[ i, 3] = -1; //con
global.race_mod[ i, 4] = spr_nevreanstand; //sprite
global.race_mod[ i, 5] = "Nevrean";
global.race_mod[ i, 6] = enum_homeworlds.talcity;
global.race_mod[ i, 7] = enum_homeworlds.goldring;
global.race_mod[ i, 8] = enum_homeworlds.taljungle;
global.race_mod[ i, 9] = enum_homeworlds.offworld;
var lang_list = ds_list_create();
lang_list[| 0] = enum_language.galactic
lang_list[| 1] = enum_language.eltin;
lang_list[| 2] = enum_language.pipperine;
global.race_mod[ i, 10] = lang_list; //additional languages

//valekin
var i = enum_races.valekin;
global.race_mod[ i, 0] =  2; //str
global.race_mod[ i, 1] =  1; //dex
global.race_mod[ i, 2] =  1; //int
global.race_mod[ i, 3] = -1; //con
global.race_mod[ i, 4] = spr_nevreanstand; //sprite
global.race_mod[ i, 5] = "Valekin";
global.race_mod[ i, 6] = enum_homeworlds.not_set;
global.race_mod[ i, 7] = enum_homeworlds.not_set;
global.race_mod[ i, 8] = enum_homeworlds.not_set;
global.race_mod[ i, 9] = enum_homeworlds.offworld;
var lang_list = ds_list_create();
lang_list[| 0] = enum_language.galactic
lang_list[| 1] = enum_language.eltin;
global.race_mod[ i, 10] = lang_list; //additional languages

/*******************
    HOMEWORLDS
*******************/

enum enum_homeworlds {
    not_set,
    offworld,
    earth,
    luna,
    mars,
    talcity,
    goldring,
    taljungle,
}

var i = enum_homeworlds.not_set;
global.planet_mod[ i, 0] = "Unset";
global.planet_mod[ i, 1] = "bluh bluh bluh.";
global.planet_mod[ i, 2] = 0; //str
global.planet_mod[ i, 3] = 0; //dex
global.planet_mod[ i, 4] = 0; //int
global.planet_mod[ i, 5] = 0; //con


var i = enum_homeworlds.offworld;
global.planet_mod[ i, 0] = "Off world";
global.planet_mod[ i, 1] = " You have spent your life in space. "
                         + "Your life of travel has made you a "
                         + "jack of all trades, but master of none. "
global.planet_mod[ i, 2] = 1; //str
global.planet_mod[ i, 3] = 1; //dex
global.planet_mod[ i, 4] = 1; //int
global.planet_mod[ i, 5] = 1; //con


var i = enum_homeworlds.earth;
global.planet_mod[ i, 0] = "Earth";
global.planet_mod[ i, 1] = " Humanities own place in the stars. "
                         + "Years of wars and power struggles "
                         + "upon these grounds have sharpend " 
                         + "and honed the human spirit into "
                         + "a blade that was destine to break "
                         + "beyond any bonds that would hold "
                         + "them.##"
                         + " With the more turbulent years "
                         + "behind it. Earth is largely a "
                         + "paradise world with a corrupt "
                         + "underbelly. Education, food, "
                         + "and prosperity are plentiful. "
                         + "Three generations have passed, "
                         + "and many children will never know "
                         + "a world without elevators into the "
                         + "heavens, and the reasons for " 
                         + "humanities long dark and bloody past.";
global.planet_mod[ i, 2] = 0; //str
global.planet_mod[ i, 3] = 1; //dex
global.planet_mod[ i, 4] = 2; //int
global.planet_mod[ i, 5] = 1; //con


var i = enum_homeworlds.luna;
global.planet_mod[ i, 0] = "Lunar farm array";
global.planet_mod[ i, 1] = " 2078 Marked the first year of " 
                         + "humanities escape from Earth's "
                         + "gravitational prison. The massive "
                         + "solar farming stations constructed " 
                         + "on each of the Moon's poles remain " 
                         + "as monument to that triumph.##"
                         + " Hardened by a long life of lunar "
                         + "construction work. You have experienced "
                         + "the hardships and struggles of a "
                         + "society growing up on a world "
                         + "not their own, and may have never set "
                         + "foot on the very soil humanity has "
                         + "walked upon for millions of years.";
global.planet_mod[ i, 2] = 1; //str
global.planet_mod[ i, 3] = 1; //dex
global.planet_mod[ i, 4] = 0; //int
global.planet_mod[ i, 5] = 2; //con


var i = enum_homeworlds.mars;
global.planet_mod[ i, 0] = "Martian sea";
global.planet_mod[ i, 1] = " Many decades of political turmoil "
                         + "marr the early history of Mar's "
                         + "settlement. The largest of which "
                         + "being the intentional melting of "
                         + "its polar caps. The runaway effects "
                         + "of humanities first terraforming "
                         + "were once believed to be abject "
                         + "failures.##"
                         + " However the discovery of martian "
                         + "bacteria growing in the new oceans "
                         + "have lead to decades of medical "
                         + "breakthroughs, and Mars now hosts "
                         + "a bizarre and unique ecosystem of "
                         + "both alien and earthly life. "
                         + "Regarded as humanities greatest: " 
                         + "Happy accident.";
global.planet_mod[ i, 2] = 0; //str
global.planet_mod[ i, 3] = 0; //dex
global.planet_mod[ i, 4] = 2; //int
global.planet_mod[ i, 5] = 2; //con


var i = enum_homeworlds.talcity;
global.planet_mod[ i, 0] = "Tal";
global.planet_mod[ i, 1] = " Many centuries of political turmoil, "
                         + "world wars, attempted genocide, and "
                         + "an overwhelming hostile planet has "
                         + "shaped Tal into a hardened, cultural "
                         + "wonderland of many races living in close "
                         + "harmony with each other and the planet itself. ## "
                         + "With the planet modernized to be on par with "
                         + "the rest of the galaxy, and the untamable alien "
                         + "wilds now completely understood and controlled, "
                         + "the inhabinants looked towards the stars for thier "
                         + "next great triumph.";
global.planet_mod[ i, 2] = 2; //str
global.planet_mod[ i, 3] = 0; //dex
global.planet_mod[ i, 4] = 0; //int
global.planet_mod[ i, 5] = 2; //con

var i = enum_homeworlds.goldring;
global.planet_mod[ i, 0] = "The Great Golden Ring";
global.planet_mod[ i, 1] = " Probabably one of the most impressive feats "
                         + "of engineering in all the known worlds, the Great "
                         + "Golden Ring of Vilous is a giant artificial ring built "
                         + "around Tal, existing within the exosphere of the planet "
                         + "and supported by numerous giant space elevators to the surface. "
                         + "The Ring serves as a singular super city compltete with every "
                         + "building imaginable, and serves as Tal's space port and the "
                         + "center of it's comerce, just like the ancient city of Goldring "
                         + "that this colousal strucutre was named and inspired by. "
global.planet_mod[ i, 2] = 0; //str
global.planet_mod[ i, 3] = 1; //dex
global.planet_mod[ i, 4] = 2; //int
global.planet_mod[ i, 5] = 1; //con

var i = enum_homeworlds.taljungle;
global.planet_mod[ i, 0] = "The Talaxian Jungles of Tal";
global.planet_mod[ i, 1] = " Despite all the modernization of Tal, "
                         + " the alien jungles that had plagued civilization "
                         + "since all of recorded vilous history still covers "
                         + "almost thirty percent of the planet's land. "
                         + "And many still choose to eek out an existance in "
                         + "these harsh lands, shunning the collectivism the rest "
                         + "of the world has embraced. ## "
                         + "Growing up here is still just as dangerous as it was "
                         + "in days of old, even with the technoligical developments "
                         + "that are now utilized, requiring a strong force of will "
                         + "to live here.";
global.planet_mod[ i, 2] = 1; //str
global.planet_mod[ i, 3] = 1; //dex
global.planet_mod[ i, 4] = -1; //int
global.planet_mod[ i, 5] = 3; //con

/*******************
    ARCHETYPES
*******************/
enum enum_archetype {
    muscle,
    nerd,
    fast,
    iron,
    every,
}

//muscleman
var i = enum_archetype.muscle;
global.arch_mod[ i, 0] =  1.50; //str
global.arch_mod[ i, 1] =  0.80; //dex
global.arch_mod[ i, 2] =  0.80; //int
global.arch_mod[ i, 3] =  0.80; //con
global.arch_mod[ i, 4] = "The muscle - #Be it training or your own growth. Your body leans to the blunt and rough power of raw physical strength.";

//nerd
var i = enum_archetype.nerd;
global.arch_mod[ i, 0] =    0.80; //str
global.arch_mod[ i, 1] =    0.80; //dex
global.arch_mod[ i, 2] =    1.50; //int
global.arch_mod[ i, 3] =    0.80; //con
global.arch_mod[ i, 4] = "The nerd - #Knowledge and experiences make you who you are, and learning more is always exciting. Even if you spend most of your time indoors.";

//fast
var i = enum_archetype.fast;
global.arch_mod[ i, 0] =    0.80; //str
global.arch_mod[ i, 1] =    1.50; //dex
global.arch_mod[ i, 2] =    0.80; //int
global.arch_mod[ i, 3] =    0.80; //con
global.arch_mod[ i, 4] = "The artist - #Everything you do is an extension of your will. Your craft is your life, and the dexterity of your body is your tool to do it.";

//iron
var i = enum_archetype.iron;
global.arch_mod[ i, 0] =    0.80; //str
global.arch_mod[ i, 1] =    0.80; //dex
global.arch_mod[ i, 2] =    0.80; //int
global.arch_mod[ i, 3] =    1.50; //con
global.arch_mod[ i, 4] = "The iron man - #You have taken a few punches in your life, but through sheer bulk, or by sheer will; Not one of them has knocked you down yet.";

//everyman
var i = enum_archetype.every;
global.arch_mod[ i, 0] =   1.00; //str
global.arch_mod[ i, 1] =   1.00; //dex
global.arch_mod[ i, 2] =   1.00; //int
global.arch_mod[ i, 3] =   1.00; //con
global.arch_mod[ i, 4] = "The everyman - #You neither excel nor lag behind in any particular traits. Perfect for someone who wants to dabble in anything.";


/*******************
    JOB MODS
*******************/
enum enum_job_stat {
    stat_name,
    stat_desc,
    stat_startkit,
}
enum enum_jobs {
    assistant,
    cargo,
    comms,
    weather,
    science,
    medical,
    engineering,
    mining,
    security,
    atmo,
    hydrophonics,
    filtration,
}

//assistant job
var job = enum_jobs.assistant;
global.job_mod[ job, enum_job_stat.stat_name]          = "Assistant";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-On the job training#" +
                                                         "-Aiding management and other staff#" +
                                                         "-Ensuring on-site equipment is powered#" +
                                                         "-Janitorial aid";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_assistbox;

//cargo
var job = enum_jobs.cargo;
global.job_mod[ job, enum_job_stat.stat_name]          = "Cargo and receiving";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Ordering supplies from orbital relay#" +
                                                         "-Transporting received orders to departments#" +
                                                         "-Keeping stock of outpost supplies";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_cargobox;

//comms
var job = enum_jobs.comms;
global.job_mod[ job, enum_job_stat.stat_name]          = "Communications";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Com array maintenance#" +
                                                         "-Com array alignment#" +
                                                         "-Informing management of company orders#" +
                                                         "-Syncronizing Cargo requests with orbital relay#" +
                                                         "-Weather array maintenance#" +
                                                         "-Ensuring local communications are secured";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_commsbox;

//weather
var job = enum_jobs.weather;
global.job_mod[ job, enum_job_stat.stat_name]          = "Weather monitor";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Informing staff of hazardous weather#" +
                                                         "-Keeping track of dangerous trends in weather#" +
                                                         "-Ensuring the safety of away teams, such as mining#" +
                                                         "-Weather array maintenance#";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_weatherbox;

//science
var job = enum_jobs.science;
global.job_mod[ job, enum_job_stat.stat_name]          = "RnD staff";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Enhancement of company supplied tools using onsite resources#" +
                                                         "-Inspection and research of discovered native objects#" +
                                                         "-Wildlife observation and in field research#" +
                                                         "-Chemical management and manufacture#" +
                                                         "-Creation of high power H2cells for vehicles";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_labbox;

//medical
var job = enum_jobs.medical;
global.job_mod[ job, enum_job_stat.stat_name]          = "Medical staff";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Recovery of on site staff#" +
                                                         "-Application of drugs and medical equipment#" +
                                                         "-Maintnence of cryo and healing pods#" +
                                                         "-Situational emergency aid";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_medicbox;

//engineering
var job = enum_jobs.engineering;
global.job_mod[ job, enum_job_stat.stat_name]          = "Engineering";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Assembly of on site equipment#" +
                                                         "-Construction of heavy machinery#" +
                                                         "-Upkeep and operation of powerplant#" +
                                                         "-Upkeep of outpost's primary utilities#" +
                                                         "-Heavy vehicle operation";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_toolbox;

//mining
var job = enum_jobs.mining;
global.job_mod[ job, enum_job_stat.stat_name]          = "Resource extraction";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Thumper operation outside of facility#" +
                                                         "-Mineral transport#" +
                                                         "-Heavy vehicle operation#" +
                                                         "-Water source scouting and collection"
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_minebox;

//security
var job = enum_jobs.security;
global.job_mod[ job, enum_job_stat.stat_name]          = "Security staff";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Ensuring on site safety and stability#" +
                                                         "-Protection of high security property#" +
                                                         "-Situational emergency aid#" +
                                                         "-Weapon management#" +
                                                         "-Wildlife management#" +
                                                         "-Heavy vehicle operation";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_secbox;

//atmo
var job = enum_jobs.atmo;
global.job_mod[ job, enum_job_stat.stat_name]          = "ATMO technician";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Atmospheric converter operation#" +
                                                         "-Maintaining outpost's primary function#" +
                                                         "-Regulation of ATMO supply feeds";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_atmobox;

//hydrophonics
var job = enum_jobs.hydrophonics;
global.job_mod[ job, enum_job_stat.stat_name]          = "hydrophonic farmer";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-On site food production" +
                                                         "-upkeep of recreational and experimental pool#" +
                                                         "-Harvest management#" +
                                                         "-Wildlife management";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_hydrobox;

//filtration
var job = enum_jobs.filtration;
global.job_mod[ job, enum_job_stat.stat_name]          = "Waste management";
global.job_mod[ job, enum_job_stat.stat_desc]          = "Job expectations: #" +
                                                         "-Janitorial service#" +
                                                         "-Management of on site landfill#" + 
                                                         "-Upkeep of water filtration system#" + 
                                                         "-Monitoring ATMO water supply feed#" +
                                                         "-Heavy vehicle operation";
global.job_mod[ job, enum_job_stat.stat_startkit]      = obj_puppet_janibox;
                    
                                                         
/*******************
    PREVIOUS EMPLOYERS
*******************/

//assistant job
var i = 0;
global.previous_job_mod[ i, 0]          = "Unemployed";
global.previous_job_mod[ i, 1]          = " You've lived at home with your parents your " + 
                                            "entire life till they just kicked you out.";
i += 1;
global.previous_job_mod[ i, 0]          = "Personal employment";
global.previous_job_mod[ i, 1]          = " description";
i += 1;
global.previous_job_mod[ i, 0]          = "ESHUI subsidiary";
global.previous_job_mod[ i, 1]          = " description";
i += 1;
global.previous_job_mod[ i, 0]          = "Galactic Association of Fast Food outlets";
global.previous_job_mod[ i, 1]          = " description";
i += 1;
global.previous_job_mod[ i, 0]          = "Galactic Highspeed-Railway Company";
global.previous_job_mod[ i, 1]          = " description";
i += 1;
global.previous_job_mod[ i, 0]          = "Builders League United";
global.previous_job_mod[ i, 1]          = " description";
i += 1;
global.previous_job_mod[ i, 0]          = "Nanotrasen Research Station 13";
global.previous_job_mod[ i, 1]          = " description";
i += 1;
global.previous_job_mod[ i, 0]          = "Reliable Excavation Demolition ";
global.previous_job_mod[ i, 1]          = " description";
i += 1;
global.previous_job_mod[ i, 0]          = "Universe hauling LTD.";
global.previous_job_mod[ i, 1]          = " description";




/*******************
    LANGUAGES
*******************/

enum enum_language {
    galactic,
    terran,
    martian,
    pipperine,
    eltin,
}

//assistant job
global.language_mod[ enum_language.galactic, 0]         = "Galactic common";
global.language_mod[ enum_language.terran, 0]           = "Terran";
global.language_mod[ enum_language.martian, 0]          = "Martian";
global.language_mod[ enum_language.pipperine, 0]        = "Pipperine";
global.language_mod[ enum_language.eltin, 0]            = "Eltin";


/*******************
    Guilds
*******************/

enum enum_guilds {
    none,
    earthgov,
    unitedfed,
    western_front,
    
}

var i = enum_guilds.none;
global.guild_mod[ i, 0] = "None";
global.guild_mod[ i, 1] = " You lack any form of prior affiliation "
                         + "with any major organization in the galaxy. "
                         + "You will be provided with only the standard "
                         + "ESHUI staff provisions. Including clothing, "
                         + " and initial off-planet hiring pay check.";
                         
var i = enum_guilds.earthgov;
global.guild_mod[ i, 0] = "Earthgov";
global.guild_mod[ i, 1] = " blah blah blah"
                         + " "


var i = enum_guilds.unitedfed;
global.guild_mod[ i, 0] = "United Federation";
global.guild_mod[ i, 1] = " ";
                         
var i = enum_guilds.western_front;
global.guild_mod[ i, 0] = "Western Front";
global.guild_mod[ i, 1] = " ";
