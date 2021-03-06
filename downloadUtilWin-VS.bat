@ECHO ON

SET project_name=Voxels

MD ".\%project_name%\Debug"
MD ".\%project_name%\x64\Debug"

CALL:downloadLibrary "SDL2", "2.0.8", "https://www.libsdl.org/release"
CALL:downloadLibrary "SDL2_ttf" "2.0.14" "https://www.libsdl.org/projects/SDL_ttf/release"
CALL:downloadLibrary "SDL2_net" "2.0.1" "https://www.libsdl.org/projects/SDL_net/release"
CALL:downloadLibrary "SDL2_mixer" "2.0.2" "https://www.libsdl.org/projects/SDL_mixer/release"
CALL:downloadLibrary "SDL2_image" "2.0.3" "https://www.libsdl.org/projects/SDL_image/release"

powershell -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest http://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.zip -OutFile glew.zip"
powershell -Command "Expand-Archive glew.zip ."
DEL /Q "glew.zip"
MD "%project_name%\%project_name%\glew"
MOVE "glew-2.1.0\src\glew.c" "%project_name%\%project_name%\glew\"
MD "%project_name%\%project_name%\glew\GL"
MOVE ".\glew-2.1.0\include\GL\glew.h" ".\%project_name%\%project_name%\glew\GL\glew.h"
MOVE ".\glew-2.1.0\include\GL\eglew.h" ".\%project_name%\%project_name%\glew\GL\eglew.h"
MOVE ".\glew-2.1.0\include\GL\glxew.h" ".\%project_name%\%project_name%\glew\GL\glxew.h"
MOVE ".\glew-2.1.0\include\GL\wglew.h" ".\%project_name%\%project_name%\glew\GL\wglew.h"

RD /S /Q ".\glew-2.1.0"

cd ".\assets\fonts"
powershell -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest https://www.1001freefonts.com/d/5455/ormont-light.zip -OutFile font.zip"
powershell -Command "Expand-Archive font.zip ."
powershell -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest https://www.1001freefonts.com/d/5742/raleway.zip -OutFile font.zip"
powershell -Command "Expand-Archive font.zip ."
DEL "font.zip"
RD __MACOSX

GOTO:EOF

:downloadLibrary
RD "%~1"
powershell -Command "Invoke-WebRequest %~3/%~1-devel-%~2-VC.zip -OutFile %~1.zip"
powershell -Command "Expand-Archive %~1.zip ."
MOVE "%~1-%~2" "%~1"
DEL "%~1.zip"
MOVE /Y ".\%~1\lib\x86\*.dll" ".\%project_name%\Debug\"
MOVE /Y ".\%~1\lib\x64\*.dll" ".\%project_name%\x64\Debug\"
GOTO:EOF
