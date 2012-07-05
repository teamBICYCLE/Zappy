#!/usr/bin/lua

c = 0

function this.avance(this)
   if (c % 7) == 0
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

function prendrePlusieur(this, str, c)
   while (c > 0)
   do
      this:IAPrendre(str)
      c = c - 1
   end
end

function this.elevate(this)
   this:IAVoir()
   local n, l, d, s, m, p, t = this:IACaseContent(this:IACurrentPosition())
   prendrePlusieur(this, "nourriture", n)
   prendrePlusieur(this, "linemate", l)
   prendrePlusieur(this, "deraumere", d)
   prendrePlusieur(this, "sibur", s)
   prendrePlusieur(this, "mendiane", m)
   prendrePlusieur(this, "phiras", p)
   prendrePlusieur(this, "thystame", t)
   this:IAPoser("linemate")
   ret = this:IAElevate()
   if ret == "ok"
   then return (OK)
   else return (KO)
   end
end