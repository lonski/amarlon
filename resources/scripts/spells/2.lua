--Spell: Magic Missile
SPELL_ID = 2

function onCast(caster, target)
	
	dmg = Damage("1d6+1#2")

	count = 1
	level = caster:getLevel()
	if level >= 4  then count = count + 1 end
	if level >= 7  then count = count + 1 end
	if level >= 10 then count = count + 1 end
	if level >= 13 then count = count + 1 end

	local function playAnimation()
		tStart = Target()
		tStart.x = caster:getX()
		tStart.y = caster:getY()

		animation = Throw("dd0000", string.byte("*"), 15)
		animation:setLocation( tStart, target )
		animation:run()
	end

	local function strike(enemy)
	 	for i=1,count do
	 		enemy:takeDamage( dmg, caster )
	 		playAnimation()
	 	end
	end
	
	for a in target.actors do
		actor = ActorWrapper(a)
		strike(actor)
	end

	return true
end

function onCancel(target)
	return true
end
