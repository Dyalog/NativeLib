# NativeLib
These are the C source and build files for the Dyalog Native Library Samples. 

> The Dyalog interpreter native library files **dwa_static** and **libdyalog** are required to build these projects. They are installed in **[DYALOG]/dwa/lib** in standard Dyalog installations from version 18.0 onwards. Therefore any software bulit from the Dyalog Native Library SDK (described in the document [*APL as a Shared Library*](http://docs.dyalog.com/latest/APL%20as%20a%20Shared%20Library.pdf)) must be used in accordance with a [Dyalog license agreement](https://www.dyalog.com/prices-and-licences.htm).

```
+-----------------------------------------------------------------+
| Dyalog is free for non-commercial use but is not free software. |
| A non-commercial licence can be used for experiments and        |
| proof of concept until the point in time that it is of value.   |
| For further information visit                                   |
| https://www.dyalog.com/prices-and-licences.htm                  |
+-----------------------------------------------------------------+
```

## JSON_APL
The JSON_APL sample allows the user to call APL functions from any language which can access native shared libraries (using what is commonly referred to as the "foreign function interface"), passing arguments and receiving results in JSON (JavaScript Object Notation) format. Its use is documented in [*The JSON_APL Shared Object*](http://docs.dyalog.com/latest/The%20JSON_APL%20Shared%20Object.pdf).

## HelloWorld
The HelloWorld sample calls into APL to display a simple "hello" message.

## Qa
The Qa sample uses and tests most (but not all) of the SDK and is provided for information only. It is used internally at Dyalog Ltd for QA purposes. Some elements of it might prove useful/interesting, for example, the Qa samples shows that the APL code can be called concurrently from multiple threads in the host application.

## Sign
The Sign sample calls into APL using various different argument types to return the astrological star sign for a specific date.
