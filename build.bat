@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

set INCLUDES=/Iscr /I%VULKAN_SDK%/include
set LINKS=/link /LIBPATH:%VULKAN_SDK%/lib vulkan-1.lib user32.lib
set DEFINES=

@echo "Building Project . . ."

cl /EHsc /Z7 /Fe"starlight 64" %INCLUDES% %DEFINES% src/main.cpp %LINKS%