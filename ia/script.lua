#!/usr/bin/lua

function this.avance(this)
	 this:IAAvance()
	 return (0)
end

function this.voir(this)
	 this:IAVoir()
	 return (0)
end

function this.prendre(this)
	 print("prendre food nigga")
	 this:IAPrendre("nourriture")
	 return (0)
end