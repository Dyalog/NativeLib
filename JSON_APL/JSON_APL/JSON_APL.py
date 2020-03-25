#!/usr/bin/env python
# -*- coding: utf-8 -*-

import json
import platform
from ctypes import cdll, c_wchar_p, create_unicode_buffer
from platformpaths import sopaths, ridelibpaths

APL = cdll.LoadLibrary(sopaths[platform.architecture()[0]][platform.system()])

def InitAPL(runtime, WSargs): 
  __C_APL_WSargs_Binding_Params__ = cUnicodeList(WSargs) 
  APL.Initialise(runtime,len(WSargs),__C_APL_WSargs_Binding_Params__)

def cUnicodeList(pylist):
  cUL = (c_wchar_p * len(pylist))()
  cUL[:] = pylist
  return cUL

def CallJSON(function, parms):
  result = create_unicode_buffer('', 256)
  err = APL.CallJSON(function, json.dumps(parms), result)
  return (result.value, err)

def GetEnv(var):
  result = create_unicode_buffer('', 256)
  err = APL.GetEnv(var, result, 256)
  return (result.value, err)

def main():
  print("Loaded lib {0}".format(APL))
  print(CallJSON("Load","sign.dyalog"))
  print(CallJSON("GetSign", [1, 24])) # Call a function loaded from sign.dyalog

  # Call APL using statements formatted in JSON
  APLCode = {
    "Left": [1,0,1,1,0],
    "Function": "/",
    "Right": "APPLE"
  }
  print(CallJSON("Exec", APLCode))
  APLCode = {
    "Function": "+\\",
    "Right": [1,2,3,4,5]
  }
  print(CallJSON("Exec", APLCode))

  # Set a variable myvar in the APL workspace and assign its value to a python variable pyvar
  pyvar = json.loads((CallJSON("Exec", "myvar←⍳9"))[0])
  print(pyvar)
  # Alter the variable pyvar in python
  for i in range(len(pyvar)):
    pyvar[i] += i
  print(pyvar)
  # Process the APL variable myvar in APL and return the result
  print(json.loads(CallJSON("Exec", "+/myvar")[0]))
  # Process the contents of pyvar in APL and return the result
  APLCode = {
    "Function": "+/",
    "Right": pyvar
  }  
  print(json.loads(CallJSON("Exec", APLCode)[0]))

  # Query available workspace
  APLCode = {
    "Function": "⎕WA"
  }
  print(CallJSON("Exec", APLCode))
  # Query MAXWS
  print(GetEnv("MAXWS"))
  # Query SESSION_FILE
  print(GetEnv("SESSION_FILE"))
  # Query RIDE_INIT
  print(GetEnv("RIDE_INIT"))
  # Query DYALOG_RIDELIB
  print(GetEnv("DYALOG_RIDELIB"))
  print("Done")
WSargs = [
  "MAXWS=512Mb",
  "SESSION_FILE=JSON_APL.dse",
  "RIDE_INIT=SERVE:*:4502",
  "DYALOG_RIDELIB="+ridelibpaths[platform.architecture()[0]][platform.system()]
]
InitAPL(1,WSargs)
CallJSON("Exec","3502⌶1") # Start RIDE
#input("You can now use RIDE to access the active workspace. Press Enter to continue...")
main()
