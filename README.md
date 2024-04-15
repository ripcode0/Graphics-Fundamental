# Graphics Fundamental

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

[!coodinate system](https://www.scratchapixel.com/images/geometry/rhlh.png)