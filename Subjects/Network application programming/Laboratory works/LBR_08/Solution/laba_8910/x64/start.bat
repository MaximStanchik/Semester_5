@echo off

for /l %%i in (1, 1, 4) do (
	start ./Debug/ClientT.exe
)