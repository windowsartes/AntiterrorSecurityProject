### [EN] Module description
This module provides you a functionalyte to detect objects on given image. This module can't find objects on raw image, but it's very useful when you alredy have a thresholded image.
Firstly, call **detectObjects** with your thresholded image as an argumnet. It'll return you a vector of the frame coordinates in the **L**eft-**R**ight-**T**op-**B**ottom format. Then you can call **makeRectangles** function with the image, where you want to draw frames, and the vector from previous step as arguments. It'll show you your image with found objects. 


### [RU] Описание модуля
Этот модуль позволяет выполнить детекцию объектов на изображении. Функционал данного модуля не позволяет найти новые объекты на сыром изображении, но он полезен для работы с изображениями, к пикселям которых уже применили некий порог. 
Сначала примените к изображению, к которому предварительно был применён какой-то порог, функцию **detectObjects** она вёрнёт vector, содержащий **Л**евую, **П**равую, **В**ерхнюю и **Н**ижнюю границу для каждого из обнаруженных объектов. Затем передайте оригинальное изображние и найденные ранее границы в функцию **makeRectangles**, она нарисует рамки для всех обнаруженных предметов. 