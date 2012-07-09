#!/usr/bin/lua

function this.exit(this)
   exit()
end

function this.enought_friends(this)
   this:IAVoir()
   local j = {this:IACaseContent(this:IACurrentPosition())}
   local j = j[8]
   print ("test: ", j)
   count = 2
   if j >= count
   then return OK
   else return KO
   end
end

function this.enought_food(this)
   this:IAInventaire()
   if this:IAgetInventoyValue(NOURRITURE) > 15
   then return OK
   else
      obj = NOURRITURE
      return KO
   end
end

function this.obj_sur_case(this)
   local ox, oy, tx, ty, msg = this:IALastMsg()
   if not (ox == -1)
   then
      this:IAVoir()
      local x, y = this:IAGetCLosestItem(JOUEUR)
      if not (x == -1 and y == -1)
      then gx, gy = x, y
      else
	 print(ox, oy, tx, ty, msg)
	 gx, gy = tx, ty
      end
      return GOTO
   end
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

function this.call_friends()
   this:IABroadcast(count)
   return OK
end