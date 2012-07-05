#!/usr/bin/lua

c = 0

function this.avance(this)
   if (c % 3) == 0
   then this:IATourner("gauche")
   end
   this:IAAvance()
   c = c + 1
   return (OK)
end

function this.voir(this)
   this:IAVoir()
   return (OK)
end

function this.prendre(this)
   str = this:IAPrendre("linemate")
   if str == "ok"
   then return (OK)
   else return (KO)
   end
end

function this.tourne(this)
   this:IATourner("droite")
   return (OK)
end

function this.elevate(this)
   this:IAPoser("linemate")
   ret = this:IAElevate()
   if ret == "ok"
   then return (OK)
   else return (KO)
   end
end