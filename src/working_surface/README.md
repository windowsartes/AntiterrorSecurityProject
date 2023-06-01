### [EN] Module description
This module allows you to find a working surface on the image. To get the binary mask, which is commonly used by some important function, like, **getGlobalUpperAndLowerBorder** from the **noise_borders** module, you can just call **findSurface** function with your BGR or grayscale image as an argumnet. All the necessary preprocessing will be done inside the function. You will get a binary mask as s resutl


### [RU] Описание модуля
Этот модуль позволяет найти рабочую поверхность на изображении, полученном из кабины лифта. Чтобы получить бинарную маску, которая нужна для работы нескольких других важных функций, например, для работы функции **getGlobalUpperAndLowerBorder** из модуля **noise_borders**, просто вызовите функцию **findSurface**, передав ей в качестве аргумента ваше цветное или чёрно-белое изображение. Вся необходимая подготовка изображения происходит внутри функции. В итоге вы получите бинарную маску, которая выделяет рабочую зону кабины лифта.