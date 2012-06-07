#!/usr/bin/lua

print("kikoo", GLOBALINT, GLOBALSTR, GLOBALNB)
--setHook(MASKRET, 0)

function this.oneRet(this)
   print("one ret returning 5")
   print("multiple ret", this:multipleRet())
   return (5)
end

function this.multRet(this, intpar, strpar)
   print("received", intpar, strpar)
   print("mult ret returning 5, 4, 3, 2, 1")
   this:noRet()
   return 5, 4, 3, 2, 1
end