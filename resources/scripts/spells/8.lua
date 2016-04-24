--Spell: Charm Person
SPELL_ID = 8
MAXIMUM_VICTIM_LEVEL = 4
RACE_HUMAN = 1
CAST_RESULT_SUCCESS = 0
CAST_RESULT_RESSISTED = 1
SPELL_SAVING_THROW = 4
PLAYER_TEAM = 2
MODIFIER_TYPE_CHARACTER_TEAM = 4

function createModifier()
	mod = Modifier(PLAYER_TEAM)
	mod.Type.generic = MODIFIER_TYPE_CHARACTER_TEAM
			
	return mod
end

function doSavingRoll(actor, caster)
	c = actor:get():character():get()
	savingThrowBonus = 0
	
	if caster ~= nil then
		if actor:get():isHostileTo(caster) then savingThrowBonus = 5 end
	end
	
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
	
	local function addModifier(actor)
		c = actor:get():character():get():addModifier( createModifier() )
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
					addModifier(a)
					playAnimationSuccess(a:get())
					ret = CAST_RESULT_SUCCESS
				end
			end			
		end
	end

	return ret
end

function onCancel(target)
	actor = target:getFirstActor()
	if actor:get() ~= nil then
		actor:get():character():get():removeModifier( createModifier() )
	end

	return true;
end

function onDayTick(target, effect)
	
	actor = target:getFirstActor()
	
	if actor:get() ~= nil and effect ~= nil then
		if doSavingRoll(actor, nil) then
			effect:setDuration(1)			
		end
	end

	return true
end