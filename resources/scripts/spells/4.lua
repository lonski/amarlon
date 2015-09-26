--Spell: Bless
SPELL_ID = 4

function onCast(caster, target)

	duration = caster:getLevel() + 1

	local function playAnimation(actor)
		t = Target()
		t.x = actor:getX()
		t.y = actor:getY()

		animation = Blink("ffff00", 20, 20)
		animation:setLocation( t, t )
		animation:run()
	end

	local function addStatusEffect(actor)
		effect = StatusEffect(SPELL_ID, duration)
		actor:addStatusEffect( effect )
	end

	local function applyModifiers(actor)
		SPELL_SAVING_THROW = 4

		actor:setAttackModifier( actor:getAttackModifier() + 1 )
		actor:setSavingThrowModifier( SPELL_SAVING_THROW, 
									  actor:getSavingThrowModifier(SPELL_SAVING_THROW) + 1 )
		actor:setMoraleModifier( actor:getMoraleModifier() + 1 )
	end

	for a in target.actors do
		actor = ActorWrapper(a)
		applyModifiers(actor)
		if actor:isAllyOf(caster) then
			addStatusEffect(actor)
			playAnimation(actor)
		end
	end

	return true
end

function onCancel(target)

	local function removeModifiers(actor)
		SPELL_SAVING_THROW = 4

		actor:setAttackModifier( actor:getAttackModifier() - 1 )
		actor:setSavingThrowModifier( SPELL_SAVING_THROW, 
									  actor:getSavingThrowModifier(SPELL_SAVING_THROW) - 1 )
		actor:setMoraleModifier( actor:getMoraleModifier() - 1 )
	end

	for a in target.actors do
		actor = ActorWrapper(a)
		removeModifiers(actor)
	end

	return true
end
