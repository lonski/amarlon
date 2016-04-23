--Item: Health Potion
ITEM_ID=1

function onUse(user, item, target)

	heal = Damage("1d6+1#0")
	
	for a in target.actors do
		c = a:get():character():get()
		if c ~= nil then
			c:takeHeal( heal, user )
		end
	end

	return true
end