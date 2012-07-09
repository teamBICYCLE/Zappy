function compareTables(a, b, test)
   matchct = 0
   for i=1,#a do
      if test(a[i], b[i])
      then matchct = matchct + 1
      end
   end
   if matchct == #a
   then return true
   end
end

function equal(a, b)
   return a == b
end

function supeq(a, b)
   return a >= b
end

function infeq(a, b)
   return a <= b
end

function 
