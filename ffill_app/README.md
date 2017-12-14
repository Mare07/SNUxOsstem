## floodfill application on ct images
### Usage
 - [compile] g++ -o ffilldemo ffilldemo.cpp $(pkg-config --libs --cflags opencv)
 - [execute] ./ffilldemo [directory name where your ct images are]
 - [example] ./ffilldemo ~/Pictures/ct_coronal/
 - I assumed image file names are in following format: 'ct.126.jpg'
 - Press key "h" to see overall instructions.
 - Especially, press key "n" to see next ct image.
