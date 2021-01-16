# These paths are for an optimised (opt) build from the source code found on https://github.com/Dyalog/NativeLib
sopaths = {
  "64bit": {
    "Linux": "./obj/JSON_APL/linux/64/opt/libJSON_APL.so",
    "Darwin": "./obj/JSON_APL/mac/64/opt/libJSON_APL.dylib",
    "Windows": "./x64/Release/JSON_APL.dll",
  },
  "32bit": {
    "Windows": "./Release/JSON_APL.dll",
  }
}
ridelibpaths = {
  "64bit": {
    "Linux": "/opt/mdyalog/18.0/64/unicode/lib/conga33_64.so",
    "Darwin": "/Applications/Dyalog-18.0.app/Contents/Resources/dyalog/lib/conga33_64.dylib",
    "Windows": "C:/Program Files/Dyalog/Dyalog APL-64 18.0 Unicode/conga33_64.dll",
  },
  "32bit": {
    "Windows": "C:/Program Files (x86)/Dyalog/Dyalog APL 18.0 Unicode/conga33_64.dll",
  }
}
