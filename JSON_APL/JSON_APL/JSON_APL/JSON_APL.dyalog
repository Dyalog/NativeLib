∇ r←Load APLCode
  :If ∨/('.dyalog'≡¯7↑APLCode)('.aplf' '.aplo' '.apln' '.aplc' '.apli'(∨/∘.≡)⊂¯5↑APLCode)
    :Trap 0
	    2⎕FIX'file://',APLCode
	    r←0
	  :Else
	    r←1
	  :EndTrap
  :ElseIf '.dws'≡¯4↑APLCode
    :Trap 0
	    r←0
	  :Else
	    r←1
	  :EndTrap
  :Else
    r←1
  :EndIf
∇

∇ out←Exec APL
  :If 9=⎕NC'APL' ⍝ Object here (CallJSON)
    :If 0<APL.⎕NC'Function'
      :If 0<APL.⎕NC'Right'
        :If 0<APL.⎕NC'Left'
          APL.(r←⍎'Left', Function, 'Right')
        :Else
          APL.(r←⍎Function, 'Right')
        :EndIf
      :Else
        APL.(r←⍎Function)
      :EndIf
      out←APL.r
    :EndIf
  :Else
    out←⍎APL
  :EndIf
∇

∇ r←GetEnv n
  r←2⎕NQ '.' 'GetEnvironment' n
∇