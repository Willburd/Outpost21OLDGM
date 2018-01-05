gml_pragma("forceinline");
return (global.client_top_gui_window == id or depth <= -1000) and instance_exists(obj_contextmenu) == false and visible == true; //context menu TAKES PRIORITY
