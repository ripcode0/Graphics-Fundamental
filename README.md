# Graphics Fundamental

## Matrix Order
|Shader|GPU memory Layout|CPU Calculate|CPU Memory Layout|
|-----|---|-----|-----|
|GLSL|Comlumn Major|Comlumn Major|Row Major|
|HLSL|Comlumn Major|Comlumn Major|Row Major|

## NDC
|API| Z-Depth| Intergration|
|--|--|--|
|OpenGL|-1 ~ 1|0 ~ 1|
|DirectX|0 ~ 1|0 ~ 1|

## Draw Order
|API|Codinate System|integrated|
|--|--|--|
|OpenGL|Right Hand : default| Left Hand CCW|
|DirectX|Left Hand : default| Left Hand CCW|

