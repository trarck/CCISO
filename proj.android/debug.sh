./build_native.sh
adb uninstall com.trarck.cciso
ant debug
adb install bin/CCISO-debug.apk