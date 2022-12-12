REM
REM Keenan's Hack to remove intermediate files
REM If you find a way to enhance, please return updates to
REM ekeenan2@cdm.depaul.edu
REM

REM cleanup root director

    rmdir /S /Q Logs
    rmdir /S /Q Debug
    rmdir /S /Q Release
    rmdir /S /Q x64
    rmdir /S /Q ipch
    rmdir /S /Q .vs
  rem  rmdir /S /Q dist

    del /F /S /A:H *.suo
    del /F /S *.sdf
    del /F /S *.suo
    del /F *.db
  
REM walk through subdirectories delete Release & Debug subs

for /d %%D in (*) do (
	echo %%~fD
	del /F %%~D\*.bin
	rmdir /S /Q %%~D\Debug
	rmdir /S /Q %%~D\Release
	rmdir /S /Q %%~D\x64
	del /F /s *.user
	del /F /S *.bin
)