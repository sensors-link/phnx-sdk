#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division, print_function
import sys,os,time
import subprocess

command = sys.argv[1] if len(sys.argv) > 1 else "UNKNOWN"
targetDir = os.path.dirname(os.path.realpath(__file__))
prjDir = os.path.realpath(os.getcwd() + "/..")
print(prjDir)
if os.path.exists(prjDir + "\\openocd.cfg"):
    cfgFile = prjDir + "\\openocd.cfg"
elif os.path.exists(targetDir + "\\openocd.cfg"):
    cfgFile = targetDir + "\\openocd.cfg"
else:
    cfgFile = "board\\phoenix.cfg"

print("OpenOCD config file:%s" % cfgFile)
if command == "flash" :
    os.system("TASKKILL /F /IM openocd.exe 2>NUL")
    binFile = sys.argv[2]
    binFile = binFile.replace("\\","/") # 简单的Window路径到POSIX路径转换
    cfgFile = cfgFile.replace("\\","/") # 简单的Window路径到POSIX路径转换
    run_args = ["openocd", "-f", cfgFile,
            "-c", "init; halt;",
            "-c", "program " + binFile + " 0x10100000 exit"]
    ret = subprocess.call(run_args, env=os.environ)

elif command == "softreset" :
    os.system("TASKKILL /F /IM openocd.exe 2>NUL")
    cfgFile = cfgFile.replace("\\","/") # 简单的Window路径到POSIX路径转换
    run_args = ["openocd", "-f", cfgFile,
            "-c", "init",
            "-c", "puts \"softreset chip, ignore the following ERROR:\"",
            "-c", "mww 0x40012C18 0xC3; mww 0x40012C18 0x3C; mww 0x40012C08 0x01; exit 0"]
    ret = subprocess.call(run_args, env=os.environ)

elif command == "gdbserver" :
    cfgFile = cfgFile.replace("\\","/") # 简单的Window路径到POSIX路径转换
    os.system("TASKKILL /F /IM openocd.exe 2>NUL")
    os.system('start openocd -f "' + cfgFile + '"')
    time.sleep(1)

elif command == "monitor" :
    serialPort = sys.argv[2]
    baudRate = sys.argv[3] if len(sys.argv) > 3 else "9600"
    os.system("START putty -sercfg " + baudRate + ",8,n,1,N -serial " + serialPort)

else :
    print('''Bad Command!
Usage:
    do.py flash binfile
    do.py softreset binfile
    do.py gdbserver
    do.py monitor
''')

