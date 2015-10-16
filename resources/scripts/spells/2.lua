--Spell: Magic Missile
SPELL_ID = 2
SHIELD = 5

function onCast(caster, target)
	
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
	 	for i=1,count do
	 		c = enemy:get():character():get()
	 		if c ~= nil then 
	 			if enemy:get():getStatusEffects():hasEffect(SHIELD) == false then
	 				c:takeDamage( dmg, caster )
	 			end
	 			playAnimation()
	 		end
	 	end
	end
	
	for a in target.actors do
		strike(a)
	end

	return true
end

function onCancel(target)
	return true
end
