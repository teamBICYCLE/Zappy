#!/usr/bin/lua

function this.avance(this)
	 this:IAAvance()
	 return (OK)
end

function this.voir(this)
	 this:IAVoir()
	 return (OK)
end

function this.prendre(this)
	 str = this:IAPrendre("nourriture")
	 if str == "ok"
	    then return (OK)
	    else return (KO)
	 end
end

function this.tourne(this)
	 this:IATourner("droite")
	 return (OK)
end