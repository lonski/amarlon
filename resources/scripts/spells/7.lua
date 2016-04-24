--Spell: Blade Trap
SPELL_ID = 7
D20 = 20
DMG_PHYSICAL = 1
CAST_RESULT_SUCCESS = 0
CAST_RESULT_RESSISTED = 1

function onCast(caster, target, spell)

	damage = Damage("1d8+0#1")

	local function strike(actor)
		ret = false
		
		c = actor:get():character():get()
		if c ~= nil then
			roll = rollDice(D20) + 1
			if roll >= c:getArmorClass(DMG_PHYSICAL) then
				c:takeDamage(damage, caster)
				ret = true
			end
		end
		
		return ret
	end

	ret = CAST_RESULT_RESSISTED
	
	for a in target.actors do
		if strike(a) then ret = CAST_RESULT_SUCCESS end
	end

	return ret
end