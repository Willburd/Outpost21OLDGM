///scr_set_depth( y, depth modifier);
//set the depth this should draw at based on the paralax of it.
//depth modifier is for stuff that flys, or sits on other objects.
gml_pragma("forceinline");
depth = (argument0 / -8) + argument1;
