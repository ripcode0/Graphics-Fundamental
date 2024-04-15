# Graphics Fundamental

* 필수적인 라이브러리 제외하고 외부 라이브러리를 안쓰려고 노력함.
* Here we've tried to reduce the library as much as possible, except for the essentials

## Matrix Order
|Shader|GPU memory Layout|CPU Calculate|CPU Memory Layout|
|-----|---|-----|-----|
|GLSL|Comlumn Major|Comlumn Major|Row Major|
|HLSL|Comlumn Major|Comlumn Major|Row Major|

## NDC
|API| Z-Depth| Z-Depth Intergrated|
|--|--|--|
|OpenGL|-1 to 1|0 to 1|
|DirectX|0 to 1|0 to 1|

## Draw Order
|API|Coodinate System|Coodinate System Integrated|
|--|--|--|
|OpenGL|Right Hand CCW| Left Hand CW|
|DirectX|Left Hand CW| Left Hand CW|

[![coodinate system](https://www.scratchapixel.com/images/geometry/rhlh.png)]