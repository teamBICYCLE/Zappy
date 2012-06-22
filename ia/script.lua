#!/usr/bin/lua

function this.avance(this)
	 print("lua: avance")
	 this:avance()
	 return (0)
end

function this.voir(this)
	 print("lua: voir")
	 this:voir()
	 return (0)
end

print("lol")