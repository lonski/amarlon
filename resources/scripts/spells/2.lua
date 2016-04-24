--Spell: Magic Missile
SPELL_ID = 2
SHIELD = "Shield"
CAST_RESULT_SUCCESS = 0
CAST_RESULT_RESSISTED = 1

function onCast(caster, target, spell)
	
	if caster:get():character():get() == nil then return false end

	dmg = Damage("1d6+1#2")

	count = 1
	level = caster:get():character():get():getLevel()
	if level >= 4  then count = count + 1 end
	if level >= 7  then count = count + 1 end
	if level >= 10 then count = count + 1 end
	if level >= 13 then count = count + 1 end

	local function playAnimation()
		tStart = Target()
		tStart.x = caster:get():getX()
		tStart.y = caster:get():getY()

		animation = Throw("dd0000", string.byte("*"), 15)
		animation:setLocation( tStart, target )
		animation:run()
	end

	local function strike(enemy)
		result = false
		
	 	for i=1,count do
	 		c = enemy:get():character():get()
	 		if c ~= nil then 
	 			if enemy:get():getStatusEffects():hasEffect(SHIELD) == false then
	 				c:takeDamage( dmg, caster )
					result = true
	 			end
	 			playAnimation()
	 		end
	 	end
		
		return result
	end
	
	ret = CAST_RESULT_RESSISTED
	
	for a in target.actors do
		if strike(a) then ret = CAST_RESULT_SUCCESS end
	end

	return ret
end