Here I'll explain you what this data is.

* train - train data we used to estimate the nose;
* validation - validation data, contains images with stickers on the walls and images with objects on the floor.
* test - test data, represents data that algorithm will see in the future; in contrast to the validation data, we can't select hyperparameters, like the number of MaxNieghbour filters, based on test results.

* additional_data/strange_thing - just normal images, but I've totally forgot about them, so they are unused.
* additional_data/paper - somitimes people put something on the cabin's floor, a paper, for example; Our current algorithm will find new objects, but it will also find headlines and paper's images - so the result will be a little incorrect. The idea was to identify the cases, when there is a paper on the floor and use this frame as a start frame. So if we'll see other frame with the paper, will compare it with new start image.
  Maybe, we'll realize it in the future.
* additional_data/whatman - there are images with whatman and black rectangles on it. They can be used to check algorithm's senditivity - how small object our algorithm can detect.
  We are also interested in this study, so perhaps we'll carry it out later.