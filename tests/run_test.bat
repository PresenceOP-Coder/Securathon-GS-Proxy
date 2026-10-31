@echo off
echo Running Microsoft strings64.exe...
strings64.exe -a -n 7 C:\Windows\System32\ntdll.dll > orig.txt
echo Running my_strings.exe clone...
..\build\Release\my_strings.exe -a -n 7 C:\Windows\System32\ntdll.dll > clone.txt
fc orig.txt clone.txt
pause
