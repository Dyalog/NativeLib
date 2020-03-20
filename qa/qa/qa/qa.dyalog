∇ r←NumericArray (start len);⎕io
⎕io←0
r←start+⍳len
∇

∇ r←Add args
r←+/args
∇

∇ r←UCS args
r←⎕UCS args
∇

∇ r←Reflect args
r←args
∇

∇ Signal n
⎕SIGNAL n
∇


∇Error n
Signal n
∇

∇r←GetEnv n
r←2 ⎕nq '.' 'GetEnvironment' n
∇

∇r←Execute n
r←⍕⍎n
∇
