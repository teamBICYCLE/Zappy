#!/usr/bin/lua

dofile("Scripts/utils.lua")
gx, gy = 0, 0

function this.enought_food(this)
   this:IAVoir()
   print("test: ", this:IAMissingRockOnCase())
   this:IAInventaire()
   if this:IAgetInventoyValue(NOURRITURE) > 8
   then return OK
   else
      obj = NOURRITURE
      return KO
   end
end

function this.can_elevate(this)
   print("DANS CAN ELEVATE")
   this:IAInventaire()
   if (this:IAgetInventoyValue(LINEMATE) > 0)
   then return OK
   else
      print ("search linemate")
      obj = LINEMATE
      return KO
   end
end

function AjustRock(count, type)
   print ("AJUST: ", count, type)
   if (count < 0)
   then
      count = -count
      while count > 0 do
	 this:IAPrendre(type)
	 count = count - 1
      end
   else while count > 0 do
	 this:IAPoser(type)
	 count = count - 1
	end
   end
end

function this.elevate(this)
   this:IAVoir()
   local n, l, d, s, m, p, t = this:IAMissingRockOnCase()
   AjustRock(l, LINEMATE)
   AjustRock(d, DERAUMERE)
   AjustRock(s, SIBUR)
   AjustRock(m, MENDIANE)
   AjustRock(p, PHIRAS)
   AjustRock(t, THYSTAME)
   this:IAElevate()
   return OK
end

function this.obj_sur_case(this)
   this:IAVoir()
   local r = {this:IACaseContent(this:IACurrentPosition())}
   if r[obj + 1] > 0
   then return OK
   else return KO
   end
end

function this.prendre_obj(this)
   this:IAPrendre(obj)
end

function this.voit_obj(this)
   this:IAVoir()
   print (obj)
   gx, gy = this:IAGetCLosestItem(obj)
   print (gx, gy)
   if gx == -1 or gy == -1
   then return KO
   else return OK
   end
end

function this.go_to(this)
   this:IAGoto(gx, gy)
   local x, y = this:IACurrentPosition()
   if gx == x and gy == y
   then return OK
   else return KO
   end
end

just_turned = false
function this.parcours_map(this)
   if not just_turned
   then
      local r = math.random(100)
      if r < 13
      then
	 this:IATourner(GAUCHE)
	 just_turned = true
      elseif r < 26
      then
	 this:IATourner(DROITE)
	 just_turned = true
      else this:IAAvance()
      end
   else this:IAAvance()
   end
   return OK
end
