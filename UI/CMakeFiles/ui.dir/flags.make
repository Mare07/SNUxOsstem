# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# compile CXX with /usr/bin/c++
CXX_FLAGS =   -msse2    -pthread -std=gnu++11

CXX_DEFINES = -DITK_IO_FACTORY_REGISTER_MANAGER -DvtkDomainsChemistry_AUTOINIT="1(vtkDomainsChemistryOpenGL2)" -DvtkIOExport_AUTOINIT="1(vtkIOExportOpenGL2)" -DvtkRenderingContext2D_AUTOINIT="1(vtkRenderingContextOpenGL2)" -DvtkRenderingCore_AUTOINIT="3(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingOpenGL2)" -DvtkRenderingOpenGL2_AUTOINIT="1(vtkRenderingGL2PSOpenGL2)" -DvtkRenderingVolume_AUTOINIT="1(vtkRenderingVolumeOpenGL2)"

CXX_INCLUDES = -I/home/hyewon/SNUxOsstem/UI/ITKFactoryRegistration -isystem /usr/local/include/ITK-4.13 -I/home/hyewon/VTK-build/Utilities/KWIML -I/home/hyewon/VTK/Utilities/KWIML -I/home/hyewon/VTK-build/Utilities/KWSys -I/home/hyewon/VTK/Utilities/KWSys -I/home/hyewon/VTK-build/ThirdParty/utf8 -I/home/hyewon/VTK/ThirdParty/utf8 -I/home/hyewon/VTK-build/Common/Core -I/home/hyewon/VTK/Common/Core -I/home/hyewon/VTK-build/Common/Math -I/home/hyewon/VTK/Common/Math -I/home/hyewon/VTK-build/Common/Misc -I/home/hyewon/VTK/Common/Misc -I/home/hyewon/VTK-build/Common/System -I/home/hyewon/VTK/Common/System -I/home/hyewon/VTK-build/Common/Transforms -I/home/hyewon/VTK/Common/Transforms -I/home/hyewon/VTK-build/Common/DataModel -I/home/hyewon/VTK/Common/DataModel -I/home/hyewon/VTK-build/Common/Color -I/home/hyewon/VTK/Common/Color -I/home/hyewon/VTK-build/Common/ExecutionModel -I/home/hyewon/VTK/Common/ExecutionModel -I/home/hyewon/VTK-build/Common/ComputationalGeometry -I/home/hyewon/VTK/Common/ComputationalGeometry -I/home/hyewon/VTK-build/Filters/Core -I/home/hyewon/VTK/Filters/Core -I/home/hyewon/VTK-build/Filters/General -I/home/hyewon/VTK/Filters/General -I/home/hyewon/VTK-build/Imaging/Core -I/home/hyewon/VTK/Imaging/Core -I/home/hyewon/VTK-build/Imaging/Fourier -I/home/hyewon/VTK/Imaging/Fourier -I/home/hyewon/VTK-build/ThirdParty/alglib -I/home/hyewon/VTK/ThirdParty/alglib -I/home/hyewon/VTK-build/Filters/Statistics -I/home/hyewon/VTK/Filters/Statistics -I/home/hyewon/VTK-build/Filters/Extraction -I/home/hyewon/VTK/Filters/Extraction -I/home/hyewon/VTK-build/Infovis/Core -I/home/hyewon/VTK/Infovis/Core -I/home/hyewon/VTK-build/Filters/Geometry -I/home/hyewon/VTK/Filters/Geometry -I/home/hyewon/VTK-build/Filters/Sources -I/home/hyewon/VTK/Filters/Sources -I/home/hyewon/VTK-build/Rendering/Core -I/home/hyewon/VTK/Rendering/Core -I/home/hyewon/VTK-build/ThirdParty/zlib -I/home/hyewon/VTK/ThirdParty/zlib -I/home/hyewon/VTK-build/ThirdParty/freetype -I/home/hyewon/VTK/ThirdParty/freetype -I/home/hyewon/VTK-build/Rendering/FreeType -I/home/hyewon/VTK/Rendering/FreeType -I/home/hyewon/VTK-build/Rendering/Context2D -I/home/hyewon/VTK/Rendering/Context2D -I/home/hyewon/VTK-build/Charts/Core -I/home/hyewon/VTK/Charts/Core -I/home/hyewon/VTK/ThirdParty/lz4/vtklz4/lib -I/home/hyewon/VTK-build/ThirdParty/lz4/vtklz4 -I/home/hyewon/VTK-build/ThirdParty/lz4 -I/home/hyewon/VTK/ThirdParty/lz4 -I/home/hyewon/VTK-build/IO/Core -I/home/hyewon/VTK/IO/Core -I/home/hyewon/VTK-build/IO/Legacy -I/home/hyewon/VTK/IO/Legacy -I/home/hyewon/VTK-build/ThirdParty/expat -I/home/hyewon/VTK/ThirdParty/expat -I/home/hyewon/VTK-build/IO/XMLParser -I/home/hyewon/VTK/IO/XMLParser -I/home/hyewon/VTK-build/IO/XML -I/home/hyewon/VTK/IO/XML -I/home/hyewon/VTK-build/ThirdParty/libxml2/vtklibxml2 -I/home/hyewon/VTK-build/ThirdParty/libxml2 -I/home/hyewon/VTK/ThirdParty/libxml2 -I/home/hyewon/VTK-build/IO/Infovis -I/home/hyewon/VTK/IO/Infovis -I/home/hyewon/VTK-build/ThirdParty/glew -I/home/hyewon/VTK/ThirdParty/glew -I/home/hyewon/VTK-build/Rendering/OpenGL2 -I/home/hyewon/VTK/Rendering/OpenGL2 -I/home/hyewon/VTK-build/Rendering/ContextOpenGL2 -I/home/hyewon/VTK/Rendering/ContextOpenGL2 -I/home/hyewon/VTK-build/Testing/Core -I/home/hyewon/VTK/Testing/Core -I/home/hyewon/VTK-build/Utilities/DICOMParser -I/home/hyewon/VTK/Utilities/DICOMParser -I/home/hyewon/VTK-build/Utilities/MetaIO/vtkmetaio -I/home/hyewon/VTK-build/Utilities/MetaIO -I/home/hyewon/VTK/Utilities/MetaIO -I/home/hyewon/VTK-build/ThirdParty/jpeg -I/home/hyewon/VTK/ThirdParty/jpeg -I/home/hyewon/VTK-build/ThirdParty/png -I/home/hyewon/VTK/ThirdParty/png -I/home/hyewon/VTK-build/ThirdParty/tiff/vtktiff/libtiff -I/home/hyewon/VTK-build/ThirdParty/tiff -I/home/hyewon/VTK/ThirdParty/tiff -I/home/hyewon/VTK-build/IO/Image -I/home/hyewon/VTK/IO/Image -I/home/hyewon/VTK-build/Testing/Rendering -I/home/hyewon/VTK/Testing/Rendering -I/home/hyewon/VTK-build/Imaging/Sources -I/home/hyewon/VTK/Imaging/Sources -I/home/hyewon/VTK-build/Filters/Hybrid -I/home/hyewon/VTK/Filters/Hybrid -I/home/hyewon/VTK-build/Filters/Modeling -I/home/hyewon/VTK/Filters/Modeling -I/home/hyewon/VTK-build/Imaging/Color -I/home/hyewon/VTK/Imaging/Color -I/home/hyewon/VTK-build/Imaging/General -I/home/hyewon/VTK/Imaging/General -I/home/hyewon/VTK-build/Imaging/Hybrid -I/home/hyewon/VTK/Imaging/Hybrid -I/home/hyewon/VTK-build/Interaction/Style -I/home/hyewon/VTK/Interaction/Style -I/home/hyewon/VTK-build/Rendering/Annotation -I/home/hyewon/VTK/Rendering/Annotation -I/home/hyewon/VTK-build/Rendering/Volume -I/home/hyewon/VTK/Rendering/Volume -I/home/hyewon/VTK-build/Interaction/Widgets -I/home/hyewon/VTK/Interaction/Widgets -I/home/hyewon/VTK-build/Views/Core -I/home/hyewon/VTK/Views/Core -I/home/hyewon/VTK-build/Views/Context2D -I/home/hyewon/VTK/Views/Context2D -I/home/hyewon/VTK-build/Filters/Programmable -I/home/hyewon/VTK/Filters/Programmable -I/home/hyewon/VTK-build/ThirdParty/verdict -I/home/hyewon/VTK/ThirdParty/verdict -I/home/hyewon/VTK-build/Filters/Verdict -I/home/hyewon/VTK/Filters/Verdict -I/home/hyewon/VTK-build/Filters/Generic -I/home/hyewon/VTK/Filters/Generic -I/home/hyewon/VTK-build/IO/Geometry -I/home/hyewon/VTK/IO/Geometry -I/home/hyewon/VTK-build/Testing/GenericBridge -I/home/hyewon/VTK/Testing/GenericBridge -I/home/hyewon/VTK-build/Domains/Chemistry -I/home/hyewon/VTK/Domains/Chemistry -I/home/hyewon/VTK-build/Domains/ChemistryOpenGL2 -I/home/hyewon/VTK/Domains/ChemistryOpenGL2 -I/home/hyewon/VTK-build/Utilities/HashSource -I/home/hyewon/VTK/Utilities/HashSource -I/home/hyewon/VTK-build/Parallel/Core -I/home/hyewon/VTK/Parallel/Core -I/home/hyewon/VTK-build/Filters/AMR -I/home/hyewon/VTK/Filters/AMR -I/home/hyewon/VTK-build/ThirdParty/hdf5/vtkhdf5 -isystem /home/hyewon/VTK/ThirdParty/hdf5/vtkhdf5/hl/src -isystem /home/hyewon/VTK/ThirdParty/hdf5/vtkhdf5/src -I/home/hyewon/VTK-build/ThirdParty/hdf5 -I/home/hyewon/VTK/ThirdParty/hdf5 -I/home/hyewon/VTK-build/IO/AMR -I/home/hyewon/VTK/IO/AMR -I/home/hyewon/VTK/ThirdParty/netcdf/vtknetcdf/include -I/home/hyewon/VTK-build/ThirdParty/netcdf/vtknetcdf -I/home/hyewon/VTK-build/ThirdParty/netcdf -I/home/hyewon/VTK/ThirdParty/netcdf -I/home/hyewon/VTK-build/ThirdParty/exodusII -I/home/hyewon/VTK/ThirdParty/exodusII -I/home/hyewon/VTK-build/IO/Exodus -I/home/hyewon/VTK/IO/Exodus -I/home/hyewon/VTK-build/Imaging/Math -I/home/hyewon/VTK/Imaging/Math -I/home/hyewon/VTK-build/Rendering/VolumeOpenGL2 -I/home/hyewon/VTK/Rendering/VolumeOpenGL2 -I/home/hyewon/VTK-build/Filters/FlowPaths -I/home/hyewon/VTK/Filters/FlowPaths -I/home/hyewon/VTK-build/Filters/Imaging -I/home/hyewon/VTK/Filters/Imaging -I/home/hyewon/VTK-build/Rendering/Label -I/home/hyewon/VTK/Rendering/Label -I/home/hyewon/VTK-build/Filters/HyperTree -I/home/hyewon/VTK/Filters/HyperTree -I/home/hyewon/VTK-build/Imaging/Stencil -I/home/hyewon/VTK/Imaging/Stencil -I/home/hyewon/VTK-build/Filters/Parallel -I/home/hyewon/VTK/Filters/Parallel -I/home/hyewon/VTK-build/Filters/ParallelImaging -I/home/hyewon/VTK/Filters/ParallelImaging -I/home/hyewon/VTK-build/Filters/Points -I/home/hyewon/VTK/Filters/Points -I/home/hyewon/VTK-build/Filters/SMP -I/home/hyewon/VTK/Filters/SMP -I/home/hyewon/VTK-build/Filters/Selection -I/home/hyewon/VTK/Filters/Selection -I/home/hyewon/VTK-build/ThirdParty/netcdfcpp -I/home/hyewon/VTK/ThirdParty/netcdfcpp -I/home/hyewon/VTK-build/IO/NetCDF -I/home/hyewon/VTK/IO/NetCDF -I/home/hyewon/VTK-build/ThirdParty/jsoncpp -I/home/hyewon/VTK/ThirdParty/jsoncpp -I/home/hyewon/VTK-build/IO/Parallel -I/home/hyewon/VTK/IO/Parallel -I/home/hyewon/VTK-build/Filters/Texture -I/home/hyewon/VTK/Filters/Texture -I/home/hyewon/VTK-build/Filters/Topology -I/home/hyewon/VTK/Filters/Topology -I/home/hyewon/VTK-build/Infovis/Layout -I/home/hyewon/VTK/Infovis/Layout -I/home/hyewon/VTK/ThirdParty/libproj4/vtklibproj4 -I/home/hyewon/VTK-build/ThirdParty/libproj4/vtklibproj4 -I/home/hyewon/VTK-build/ThirdParty/libproj4 -I/home/hyewon/VTK/ThirdParty/libproj4 -I/home/hyewon/VTK-build/Geovis/Core -I/home/hyewon/VTK/Geovis/Core -I/home/hyewon/VTK-build/IO/EnSight -I/home/hyewon/VTK/IO/EnSight -I/home/hyewon/VTK-build/ThirdParty/gl2ps -I/home/hyewon/VTK/ThirdParty/gl2ps -I/home/hyewon/VTK-build/Rendering/GL2PSOpenGL2 -I/home/hyewon/VTK/Rendering/GL2PSOpenGL2 -I/home/hyewon/VTK/ThirdParty/libharu/vtklibharu/include -I/home/hyewon/VTK-build/ThirdParty/libharu/vtklibharu/include -I/home/hyewon/VTK-build/ThirdParty/libharu -I/home/hyewon/VTK/ThirdParty/libharu -I/home/hyewon/VTK-build/IO/Export -I/home/hyewon/VTK/IO/Export -I/home/hyewon/VTK-build/IO/ExportOpenGL2 -I/home/hyewon/VTK/IO/ExportOpenGL2 -I/home/hyewon/VTK-build/Interaction/Image -I/home/hyewon/VTK/Interaction/Image -I/home/hyewon/VTK-build/IO/Import -I/home/hyewon/VTK/IO/Import -I/home/hyewon/VTK-build/IO/LSDyna -I/home/hyewon/VTK/IO/LSDyna -I/home/hyewon/VTK-build/IO/MINC -I/home/hyewon/VTK/IO/MINC -I/home/hyewon/VTK-build/ThirdParty/oggtheora -I/home/hyewon/VTK/ThirdParty/oggtheora -I/home/hyewon/VTK-build/IO/Movie -I/home/hyewon/VTK/IO/Movie -I/home/hyewon/VTK-build/IO/PLY -I/home/hyewon/VTK/IO/PLY -I/home/hyewon/VTK-build/IO/ParallelXML -I/home/hyewon/VTK/IO/ParallelXML -I/home/hyewon/VTK-build/ThirdParty/sqlite -I/home/hyewon/VTK/ThirdParty/sqlite -I/home/hyewon/VTK-build/IO/SQL -I/home/hyewon/VTK/IO/SQL -I/home/hyewon/VTK-build/Testing/IOSQL -I/home/hyewon/VTK/Testing/IOSQL -I/home/hyewon/VTK-build/IO/TecplotTable -I/home/hyewon/VTK/IO/TecplotTable -I/home/hyewon/VTK-build/IO/Video -I/home/hyewon/VTK/IO/Video -I/home/hyewon/VTK-build/Imaging/Statistics -I/home/hyewon/VTK/Imaging/Statistics -I/home/hyewon/VTK-build/Rendering/Image -I/home/hyewon/VTK/Rendering/Image -I/home/hyewon/VTK-build/Imaging/Morphological -I/home/hyewon/VTK/Imaging/Morphological -I/home/hyewon/VTK-build/Rendering/LOD -I/home/hyewon/VTK/Rendering/LOD -I/home/hyewon/VTK-build/Views/Infovis -I/home/hyewon/VTK/Views/Infovis -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gio-unix-2.0 -I/usr/include/mirclient -I/usr/include/mircore -I/usr/include/mircookie -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -isystem /usr/local/include -isystem /home/hyewon/VTK-build/Utilities/KWSys/vtksys -isystem /home/hyewon/VTK-build/ThirdParty/hdf5/vtkhdf5/hl/src -isystem /home/hyewon/VTK-build/ThirdParty/hdf5/vtkhdf5/src -isystem /home/hyewon/VTK-build/ThirdParty/netcdfcpp/vtknetcdfcpp -isystem /usr/local/include/opencv 
