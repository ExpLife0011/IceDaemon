@echo off
choice /C YN /M "��ȷ����װ���Ʒ�����? ȷ���밴Y��ȡ���밴N"
if errorlevel 2 goto end1
if errorlevel 1 goto run

:run

%~dp0IceDaemon.exe -i
echo ��ʼ��������
net start ICEService
echo ���÷��񿪻��Զ�����
sc config ICEService start= auto
::echo ���÷����Զ��������ʱ��15s
::sc failure ICEService reset= 2592000 actions= restart/15000
goto end2

:end1
echo ��ȡ������������,���ڽ��ر�
exit

:end2
echo �������������,��������رմ���
pause>nul