--Spell: Charm Person
SPELL_ID = 8
MAXIMUM_VICTIM_LEVEL = 4
RACE_HUMAN = 1
CAST_RESULT_SUCCESS = 0
CAST_RESULT_RESSISTED = 1
SPELL_SAVING_THROW = 4

function doSavingRoll(actor, caster)
	c = actor:get():character():get()
	savingThrowBonus = 0
	
	if actor:get():isHostileTo(caster) then savingThrowBonus = 5 end
	
	return c:rollSavingThrow(SPELL_SAVING_THROW + savingThrowBonus)
end

function onCast(caster, target, spell)

	local function playAnimation(actor)
		t = Target()
		t.x = actor:getX()
		t.y = actor:getY()

		animation = Blink("ff69b4", 20, 15)
		animation:setLocation( t, t )
		animation:run()
	end
	
	local function playAnimationSuccess(actor)
		t = Target()
		t.x = actor:getX()
		t.y = actor:getY()

		animation = Blink("83F52C", 20, 15)
		animation:setLocation( t, t )
		animation:run()
	end
	
	local function addStatusEffect(actor)
		effect = StatusEffect(spell:getName(), spell:getScript(), -1)
		actor:get():getStatusEffects():add( effect )
	end
		
	ret = CAST_RESULT_RESSISTED
	
	for a in target.actors do
		c = a:get():character():get()		
		if c ~= nil then
			playAnimation(a:get())
			race = c:getRace()
			if c:getLevel() <= MAXIMUM_VICTIM_LEVEL or race:getType() == RACE_HUMAN then
				if not doSavingRoll(a, caster) then
					addStatusEffect(a)
					playAnimationSuccess(a:get())
					ret = CAST_RESULT_SUCCESS
				end
			end			
		end
	end

	return ret
end

function onCancel(target)
	return true;
end