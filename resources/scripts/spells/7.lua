--Spell: Blade Trap
SPELL_ID = 7
D20 = 20
DMG_PHYSICAL = 1

function onCast(caster, target, spell)

	damage = Damage("1d8+0#1")

	local function strike(actor)
		c = actor:get():character():get()
		if c ~= nil then
			roll = rollDice(D20) + 1
			if roll >= c:getArmorClass(DMG_PHYSICAL) then
				c:takeDamage(damage, caster)
			end
		end
	end

	for a in target.actors do
		strike(a)
	end

	return true
end

function onCancel(target, spell)
	return true
end
