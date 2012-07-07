#!/usr/bin/lua

obj = NOURRITURE

gx, gy = 0, 0
just_turned = false

function this.obj_sur_case(this)
   this:IAVoir()
   local r = {this:IACaseContent(this:IACurrentPosition())}
   if r[obj] > 0
   then return OK
   else return KO
   end
end

function this.prendre_obj(this)
   this:IAPrendre(obj)
end

function this.voit_obj(this)
   this:IAVoir()
   gx, gy = this:IAGetClosestItem(obj)
end

function this.go_to(this)
   this:IAGoto(gx, gy)
end

function this.parcours_map(this)
   if not just_turned
   then
      local r = math.random(100)
      if r < 13
      then
	 this:tourne(gauche)
	 just_turned = true
      elseif r < 26
      then
	 this:tourne(droite)
	 just_turned = true
      else this:avance()
      end
   else this:avance()
   end
end
