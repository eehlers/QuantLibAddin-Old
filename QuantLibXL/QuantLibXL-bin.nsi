
# !defines

!define APP "QuantLibXL"
!define VER_NUMBER "0.8.0"
!define VER_NUMBER_UNDERSCORE "0_8_0"

# Compiler Flags

SetCompressor lzma

# Installer Attributes

Caption "${APP} - Setup"
DirText "Please select a location to install ${APP} (or use the default):"
Icon "Docs\images\favicon.ico"
InstallDir $PROGRAMFILES\${APP}-${VER_NUMBER}
LicenseData "LICENSE.TXT"
LicenseText "${APP} is released under the following license:"
Name "${APP}"
OutFile "..\${APP}-bin-${VER_NUMBER}.exe"
UninstallIcon "Docs\images\favicon.ico"
UninstallText "This will uninstall QuantLibXL. Hit next to continue."

ComponentText \
"By default the installer will install the QuantLibXL Addin (XLL) and basic example workbooks." \
"Optional components:" \
"The QuantLibXL Framework is a business application layer written in Excel VBA, \
including template workbooks for market data and interest rate derivates."

# Installer Instructions

Section

    SetOutPath "$INSTDIR"

    File "Authors.txt"
    File "Contributors.txt"
    File "LICENSE.TXT"
    File "NEWS.txt"
    File "README.txt"

    SetOutPath "$INSTDIR\xll"
    File "xll\QuantLibXL-vc80-mt-s-${VER_NUMBER_UNDERSCORE}.xll"

    SetOutPath "$INSTDIR\Workbooks\DateCalendarsDayCounters"
    File "Workbooks\DateCalendarsDayCounters\*.xls"

    SetOutPath "$INSTDIR\Workbooks\Math"
    File "Workbooks\Math\*.xls"

    SetOutPath "$INSTDIR\Workbooks\StandaloneExamples"
    File "Workbooks\StandaloneExamples\README.txt"
    File /x "BlackFormula.xls" \
         /x "capfloors.xls" \
            "Workbooks\StandaloneExamples\*.xls"

    SetOutPath "$INSTDIR\Workbooks\Utilities"
    File "Workbooks\Utilities\*.xls"

    SetOutPath "$INSTDIR\Docs"
    File "Docs\QuantLibXL-docs-${VER_NUMBER}.chm"

    WriteRegStr HKEY_LOCAL_MACHINE \
                "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuantLibXL-bin-${VER_NUMBER}" \
                "DisplayName" "QuantLibXL-bin ${VER_NUMBER} (remove only)"

    WriteRegStr HKEY_LOCAL_MACHINE \
                "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuantLibXL-bin-${VER_NUMBER}" \
                "UninstallString" '"$INSTDIR\QuantLibXLUninstall.exe"'

    CreateDirectory "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}"

    CreateShortCut "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}\Uninstall QuantLibXL.lnk" \
                   "$INSTDIR\QuantLibXLUninstall.exe" "" \
                   "$INSTDIR\QuantLibXLUninstall.exe" 0

    CreateShortCut "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}\README.txt.lnk" \
                   "$INSTDIR\README.txt"

    CreateShortCut "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}\LICENSE.txt.lnk" \
                   "$INSTDIR\LICENSE.txt"

    CreateShortCut "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}\QuantLibXL Directory.lnk" \
                   "$INSTDIR"

    CreateShortCut "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}\Example workbooks.lnk" \
                   "$INSTDIR\Workbooks"

    CreateShortCut "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}\Documentation (WinHelp).lnk" \
        "$INSTDIR\Docs\QuantLibXL-docs-${VER_NUMBER}.chm"

    WriteINIStr "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}\QuantLibXL Home Page.url" \
                "InternetShortcut" "URL" "http://www.quantlibxl.org/"

    WriteUninstaller "QuantLibXLUninstall.exe"

SectionEnd

Section /o Framework

    SetOutPath "$INSTDIR\framework"
    File "framework\QuantLibXL.xla"

    SetOutPath "$INSTDIR\Workbooks"
    File /r "Workbooks\*.xls"

    SetOutPath "$INSTDIR\metadata"
    File /r "..\QuantLibAddin\gensrc\metadata\*.xml"

    # ObjectBuilder crashes if it can't find the icon
    SetOutPath "$INSTDIR\Docs\images"
    File "Docs\images\favicon.bmp"

SectionEnd

Section "Uninstall"

    RMDir /r "$INSTDIR"
    RMDir /r "$SMPROGRAMS\QuantLibXL-bin-${VER_NUMBER}"

    DeleteRegKey HKEY_LOCAL_MACHINE \
        "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuantLibXL-bin-${VER_NUMBER}"

SectionEnd

