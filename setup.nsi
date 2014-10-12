; Script generated with the Venis Install Wizard

; Define your application name
!define APPNAME "cLKSD"
!define APPNAMEANDVERSION "cLKSD v1.0"

; Main Install settings
Name "${APPNAMEANDVERSION}"
InstallDir "$PROGRAMFILES\cLKSD"
InstallDirRegKey HKLM "Software\${APPNAME}" ""
OutFile "clksd-1.0-setup.exe"

DirText "Choose the folder in which to install ${APPNAMEANDVERSION}."

Section "cLKSD"

	; Set Section properties
	SetOverwrite on

	; Set Section Files and Shortcuts
	SetOutPath "$INSTDIR\"
	File /r "C:\gtk+_3.6.4\*"

	SetOutPath "$INSTDIR\bin"
	File bin\Release\clksd.exe
	File clksd.sqlite
	File lib\eVehicleRegistrationAPI.dll
	File lib\CelikApi.dll
	File C:\CodeBlocks\DevPaks\bin\sqlite3.dll

	SetOutPath "$INSTDIR\bin\fonts"
	File /r fonts\*

	SetOutPath "$INSTDIR\bin\glade"
	File /r glade\*

	SetOutPath "$INSTDIR\bin\locale"
	File /r locale\*

	SetOutPath "$INSTDIR\bin"
	CreateShortCut "$DESKTOP\cLKSD.lnk" "$INSTDIR\bin\clksd.exe" sr
	CreateDirectory "$SMPROGRAMS\cLKSD"
	CreateShortCut "$SMPROGRAMS\cLKSD\cLKSD.lnk" "$INSTDIR\bin\clksd.exe"
	CreateShortCut "$SMPROGRAMS\cLKSD\Uninstall.lnk" "$INSTDIR\uninstall.exe"

SectionEnd

Section -FinishSection

	WriteRegStr HKLM "Software\${APPNAME}" "" "$INSTDIR"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayName" "${APPNAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "UninstallString" "$INSTDIR\uninstall.exe"
	WriteUninstaller "$INSTDIR\uninstall.exe"

	MessageBox MB_YESNO "Would you like to run ${APPNAMEANDVERSION}?" IDNO NoRun
		Exec "$INSTDIR\bin\cLKSD.exe"
	NoRun:

SectionEnd

;Uninstall section
Section Uninstall

	;Remove from registry...
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
	DeleteRegKey HKLM "SOFTWARE\${APPNAME}"

	; Delete self
	Delete "$INSTDIR\uninstall.exe"

	; Delete Shortcuts
	Delete "$DESKTOP\cLKSD.lnk"
	Delete "$SMPROGRAMS\cLKSD\cLKSD.lnk"
	Delete "$SMPROGRAMS\cLKSD\Uninstall.lnk"

	; Clean up cLKSD
	Delete "$INSTDIR\share\themes\Raleigh\gtk-2.0\clksd.exe"

	; Remove remaining directories
	RMDir /r /REBOOTOK $INSTDIR
	RMDir "$SMPROGRAMS\cLKSD"

SectionEnd

Function un.onInit

	MessageBox MB_YESNO|MB_DEFBUTTON2|MB_ICONQUESTION "Remove ${APPNAMEANDVERSION} and all of its components?" IDYES DoUninstall
		Abort
	DoUninstall:

FunctionEnd

; eof
