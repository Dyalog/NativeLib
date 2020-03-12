# Dyalog Native Library
This file is located in the directory **[DYALOG]/dwa/lib** in standard Dyalog installations.
The two other files in this directory (but not on GitHub),
- dwa_static 
- libdyalog  

can be used as part of an SDK to create shared libraries which allow APL code to be called by any language or program that can access native shared libraries. The SDK is described in the document [*APL as a Shared Library*](http://docs.dyalog.com/latest/APL%20as%20a%20Shared%20Library.pdf). It is also possible to produce a static library or a self-contained application containing APL code.

[*The JSON_APL Shared Object*](http://docs.dyalog.com/latest/The%20JSON_APL%20Shared%20Object.pdf) is an example of such a shared library. It is included with standard installations of Dyalog version 17.1 onwards in **[DYALOG]/Samples/JSON_APL**, alongside an example Python script (**JSON_APL.py**) and dyalog function (**sign.dyalog**). It can be run out-of-the-box with a Python 3 interpreter. 

The C source code, Visual Studio Solution files and makefiles for the JSON_APL Shared Object, as well as three other samples ("helloworld", "qa" and "sign"), can be downloaded from https://github.com/dyalog/NativeLib. 
