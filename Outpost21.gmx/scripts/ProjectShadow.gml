///ProjectShadow(Vertex buffer,x1,y1,x2,y2,Light x,Light Y);
gml_pragma("forceinline");
var _vb = argument0;
var _Ax = argument1;
var _Ay = argument2;
var _Bx = argument3;
var _By = argument4;
var _Lx = argument5;
var _Ly = argument6;

// shadows are infinite - almost, just enough to go off screen
var SHADOW_LENGTH = 20000;

var Adx,Ady,Bdx,Bdy,len

// get unit length to point 1
Adx = _Ax-_Lx;      
Ady = _Ay-_Ly;      
len = (1.0*SHADOW_LENGTH)/sqrt( (Adx*Adx)+(Ady*Ady) );      // unit length scaler * Shadow length
Adx = _Ax + Adx * len;
Ady = _Ay + Ady * len;

// get unit length to point 2
Bdx = _Bx-_Lx;      
Bdy = _By-_Ly;      
len = (1.0*SHADOW_LENGTH) / sqrt( (Bdx*Bdx)+(Bdy*Bdy) );    // unit length scaler * Shadow length
Bdx = _Bx + Bdx * len;
Bdy = _By + Bdy * len;

//allow fading
var inalpha = floor(255*(clamp(argument7,0,1)/1));
inalpha = inalpha << 24;

// now build a quad
vertex_position(_vb, _Ax,_Ay);
vertex_argb(_vb, $00000000 | inalpha);
vertex_position(_vb, _Bx,_By);
vertex_argb(_vb, $00000000 | inalpha);
vertex_position(_vb, Adx,Ady);
vertex_argb(_vb, $00000000 | inalpha);

vertex_position(_vb, _Bx,_By);
vertex_argb(_vb, $00000000 | inalpha);
vertex_position(_vb, Adx,Ady);
vertex_argb(_vb, $00000000 | inalpha);
vertex_position(_vb, Bdx,Bdy);
vertex_argb(_vb, $00000000 | inalpha);
