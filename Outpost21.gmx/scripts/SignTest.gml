///SignTest( Ax ,Ay ,Bx , By, Lx, Ly);
gml_pragma("forceinline");
var _Ax = argument0;
var _Ay = argument1;
var _Bx = argument2;
var _By = argument3;
var _Lx = argument4;
var _Ly = argument5;

return ((_Bx - _Ax) * (_Ly - _Ay) - (_By - _Ay) * (_Lx - _Ax));
