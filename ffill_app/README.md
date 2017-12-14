## floodfill application on ct images
### Usage
 - [compile] g++ -o ffilldemo ffilldemo.cpp $(pkg-config --libs --cflags opencv)
 - [execute] ./ffilldemo [directory name where your ct images are]
 - [example] ./ffilldemo ~/Pictures/ct_coronal/
 - Just use Makefile. (make & make run)
 - Press key "h" to see overall instructions.
 - Especially, press key "n" to see next ct image.

### Assumption
 - All the images are in the same directory.
 - Image file names are in following format: 'ct.126.jpg'

### Shape Match + FloodFill
 - Previously & currently marked ct images ==(function)==> matched image
 - We will use ffillwhole.cpp as a source, not ffillmask. (Shape-match between colored images, not just segmented masks)
 
