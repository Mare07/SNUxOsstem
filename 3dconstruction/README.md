## Changed marking color blue(255, 0, 0) to white (255, 255, 255) in UI/ffillwhole.cpp and UI/shapematch.cpp
- To make sinus "white" when building mha file from jpg slices.
- Because blue is converted into black in gray scale, thus making it hard to recognize sinus in 3d. 

## Compile and Run
### VolumeFromSlices: This makes .mha file out of jpg slices)
#### In /build
- cmake ..
- make
- ./VolumeFromSlices ~/path/to/your/floodfilled/image/folder/ct.res.%d.jpg 88 188 please.mha

### In MedicalDemo4/build
- cmake ..
- make
- ./MedicalDemo4 ../../VolumeFromSlices/build/please.mha

