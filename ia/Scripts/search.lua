#!/usr/bin/lua

dofile("Scripts/utils.lua")
gx, gy = 0, 0
MAP_SIZE = 20
HAS_LAYED = false
HAS_TO_CALL_PLAYER = false

function this.meet(this)
   if this:IAMessageInQueue("level " .. this:IAGetLevel())
   then
      local dir, msg
      ox, oy, dir, msg = this:IALastMsg()
      local cx, cy = this:IACurrentPosition()
      if ox ~= cx and oy ~= cy
      then
      	 this:IAVoir()
      	 return LOOP
      end
      gdir = dir
   else
      this:IAVoir()
      return LOOP
   end
   if gdir == NONE
   then return OK
   else
      return KO
   end
end

function this.go_dir(this)
   if gdir == this:IACurrentDirection()
   then this:IAAvance()
   else
      if gdir - 1 == ((this:IACurrentDirection() - 1) + 1) % 4
      then this:IATourner(DROITE)
      else this:IATourner(GAUCHE)
      end
      return KO
   end
   return OK
end

function this.enought_food(this)
   if (HAS_TO_CALL_PLAYER == true)
   then
      local nbslots = this:IACanConnectPlayer()
      this:IAConnectPlayer(nbslots)
   end
   if (HAS_LAYED == false)
   then
      this:IALay()
      HAS_LAYED = true
      HAS_TO_CALL_PLAYER = true
   end
   this:IAInventaire()
   if this:IAgetInventoyValue(NOURRITURE) > 30
   then return OK
   elseif this:IAMessageInQueue("level " .. this:IAGetLevel())
   then return FRIEND
   else
      obj = NOURRITURE
      return KO
   end
end

function this.can_elevate(this)
   this:IAInventaire()
   print(this:IAMissingRockInInventory())
   if (compareTables({this:IAMissingRockInInventory()}, {0, 0, 0, 0, 0, 0, 0}, infeq))
   then return OK
   else
      obj = this:IAMissingRockInInventoryID()
      if obj == -1
      then obj = NOURRITURE
      end
      return KO
   end
end

function AjustRock(count, type)
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
   print ("ETVOILA: ", gx, gy)
   print ("Et la position:", this:IACurrentPosition())
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

function this.can_wait_mates(this)
   this:IAVoir()
   local n, l, d, s, m, p, t, j = this:IAMissingRockOnCase()
   if j <= 0
   then return OK
   end
   this:IAInventaire()
   if this:IAgetInventoyValue(NOURRITURE) > MAP_SIZE
   then return OK
   else
      obj = NOURRITURE
      return KO
   end
end

function this.enought_mates(this)
   this:IAVoir()
   local r = {this:IAMissingRockOnCase()}
   print (unpack(r))
   if r[8] <= 0
   then return OK
   else return KO
   end
end

function this.call_mates(this)
   if this:IAMessageInQueue("level " .. this:IAGetLevel())
   then return FRIEND
   end
   this:IABroadcast("level " .. this:IAGetLevel())
   return OK
end