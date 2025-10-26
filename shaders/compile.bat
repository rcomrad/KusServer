set compiler_folder=D:\vulkansdk\Bin
set compiler_filename=glslc.exe
set compiler_path=%compiler_folder%\%compiler_filename%

set output_dir=..\data\shaders
if not exist "%output_dir%" (
    mkdir "%output_dir%"
)

if not exist "%compiler_path%" (
    echo Error: glslc.exe not found at %compiler_path%
    pause
    exit /b 1
)

"%compiler_path%" shader.frag -o "%output_dir%\frag.spv"
"%compiler_path%" shader.vert -o "%output_dir%\vert.spv"
