@echo off
net stop ICEService
%~dp0IceDaemon.exe -u

echo ������ж�����,��������رմ���
pause>nul
