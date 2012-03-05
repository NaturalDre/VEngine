-- Holds a reference to all loaded scripts
ThisTable =
{

}


-- This will be called from C++. The script's name will be
-- it's stripped filename. AKA MyScript.lua will be called MyScript
-- inside ThisTable. Script writers should have their script inside
-- a the this namespace. E.G. this = { speed = 5; }
-- The reason is that when your script is loaded everything inside the global
-- variable 'this' will be added an element in the ThisTable so we know
-- your script scripts and wants to be updated. (e.g. OnEvent functions)
function AddToThisTable(ID)
	ThisTable[ID] = this;
end
