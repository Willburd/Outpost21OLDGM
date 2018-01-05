/// key_to_string( key )
/*//
Script by D.W. O'Boyle (@dwoboyle)
How to use:
Simply call this script in a draw_text function.
argument0 should be a keyboard key such as vk_enter or ord('Z').
//*/
 
//if( argument0 > 48 and argument0 < 91 )
//{ return chr(argument0); }
switch( argument0 )
{
    default: return chr(argument0); break;

    case 8: return ""; break; //backspace
    case 9: return ""; break; //tab
    case 13: return ""; break; //enter
    case 16: return ""; break; //shft
    case 17: return ""; break; //ctrl
    case 18: return ""; break; //alt
    case 19: return ""; break; //apusebreak
    case 20: return ""; break; //caplocks
    case 27: return ""; break; //escape
    case 33: return ""; break; //pgup
    case 34: return ""; break; //pgdown
    case 35: return ""; break; //end
    case 36: return ""; break; //home
    case 37: return ""; break; //left
    case 38: return ""; break; //up
    case 39: return ""; break; //right
    case 40: return ""; break; //down
    case 45: return ""; break; //insert
    case 46: return ""; break; //delete
    case 96: return "0"; break; //numpad
    case 97: return "1"; break;
    case 98: return "2"; break;
    case 99: return "3"; break;
    case 100: return "4"; break;
    case 101: return "5"; break;
    case 102: return "6"; break;
    case 103: return "7"; break;
    case 104: return "8"; break;
    case 105: return "9"; break;
    case 106: return "*"; break;
    case 107: return "+"; break;
    case 109: return "-"; break;
    case 110: return "."; break;
    case 111: return "/"; break; //numpad end
    case 112: return ""; break; //function keys
    case 113: return ""; break;
    case 114: return ""; break;
    case 115: return ""; break;
    case 116: return ""; break;
    case 117: return ""; break;
    case 118: return ""; break;
    case 119: return ""; break;
    case 120: return ""; break;
    case 121: return ""; break;
    case 122: return ""; break;
    case 123: return ""; break; //function keys end
    case 144: return ""; break; //numlock
    case 145: return ""; break; //scroll lock
    case 186: return ";"; break;
    case 187: return "="; break;
    case 188: return ","; break;
    case 189: return "-"; break;
    case 190: return "."; break;
    case 191: return "\"; break;
    case 192: return "`"; break;
    case 219: return "/"; break;
    case 220: return "["; break;
    case 221: return "]"; break;
    case 222: return "'"; break;
}
