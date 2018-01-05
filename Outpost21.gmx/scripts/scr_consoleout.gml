///scr_consoleout("Text output to console.");
gml_pragma("forceinline");
show_debug_message(argument0);

//update console
global.console_log[9] = global.console_log[8];
global.console_log[8] = global.console_log[7];
global.console_log[7] = global.console_log[6];
global.console_log[6] = global.console_log[5];
global.console_log[5] = global.console_log[4];
global.console_log[4] = global.console_log[3];
global.console_log[3] = global.console_log[2];
global.console_log[2] = global.console_log[1];
global.console_log[1] = global.console_log[0];
global.console_log[0] = argument0;
