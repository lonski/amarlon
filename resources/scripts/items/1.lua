--Item: Health Potion
ITEM_ID=1

function onUse(user, item, target)

	local function playAnimation(actor)
		t = Target()
		t.x = actor:getX()
		t.y = actor:getY()

		animation = Blink("0000ff", 20, 15)
		animation:setLocation( t, t )
		animation:run()
	end

	heal = Damage("1d6+1#0")
	
	for a in target.actors do
		c = a:get():character():get()
		if c ~= nil then
			c:takeHeal( heal, user )
			playAnimation( a:get() )
		end
	end

	return false
end