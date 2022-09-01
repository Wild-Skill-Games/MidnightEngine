if not exist "vendor\bin\premake\bin\release\premake5.exe" (
	call vendor/bin/premake/Bootstrap.bat
)

call vendor\bin\premake\bin\release\premake5.exe vs2022