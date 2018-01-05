//deconstruct from array
var get_array = argument0;
var get_index = argument1;

global.text_input_repeater = clamp(global.text_input_repeater - 1,0,99999);

//typing control
if current_selection != -1 {
    
    if keyboard_check(vk_control) {
        if keyboard_check_pressed( ord('V')) {
            var getstr = clipboard_get_text();
            get_array[get_index,0] = string_copy(getstr,1, min(string_length(getstr), get_array[get_index,1]));
        }
    }
    else
    {
        //force resent on press
        if keyboard_check_pressed(vk_anykey) global.text_input_repeater = 0;
        
        //go for the loop
        if keyboard_check(vk_anykey) and global.text_input_repeater == 0 {   
            var filter = keyboard_key;
            show_debug_message("keypressed: " + string(key_to_string(filter)) );
            global.text_input_repeater  = 10;
            
            switch filter {
                case vk_enter: 
                case vk_delete:
                case vk_alt:
                case vk_shift:
                case vk_lshift:
                case vk_rshift:
                
                break;
                
                case vk_backspace: 
                    if string_length(get_array[get_index,0]) > 0 {
                        get_array[get_index,0] = string_copy( get_array[get_index,0], 0, string_length(get_array[get_index,0])-1 );
                    }
                break;
                
                default:
                    if string_length(get_array[get_index,0]) < get_array[get_index,1] {
                        var collect_string = key_to_string(filter);
                        
                        if keyboard_check(vk_shift) collect_string = string_upper(collect_string) else collect_string = string_lower(collect_string);
                        
                        get_array[get_index,0] = get_array[get_index,0] + collect_string;
                    }
                break;
            }
            
            show_debug_message("Newstring: " + string(get_array[get_index,0]));
        }
    }
}

return get_array;
