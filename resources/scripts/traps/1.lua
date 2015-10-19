--Trap: Blade Trap
TRAP_ID = 1
D20 = 20
DMG_PHYSICAL = 1

function onTrigger(target, trap)
	hit = false;

	damage = Damage("1d8+0#1")

	local function strike(actor)
		c = actor:get():character():get()
		if c ~= nil then
			roll = rollDice(D20) + 1
			if roll >= c:getArmorClass(DMG_PHYSICAL) then
				c:takeDamage(damage, ActorPtr())
				hit = true;
			end
		end
	end

	for a in target.actors do
		strike(a)
	end

	return hit
end