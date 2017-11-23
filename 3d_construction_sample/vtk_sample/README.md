## 3D construction sample (without any image processing)
- 3dfrom2dslices.py: A python sample based on VTK-7.0. Construction of 3d sample from 2d JPG slices. Gives gray scale messy result. 
- MedicalDemo4.cxx: Downloaded .tar file from VTK examples site. It renders much cleaner and fancier 3d model from mha file (not 2d slices).
  > cd MedicalDemo4/build</br>
  > cmake ..</br>
  > make</br>
  > ./MedicalDemo4 osstem_sample.mha
