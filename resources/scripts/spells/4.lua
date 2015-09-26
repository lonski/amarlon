--Spell: Bless
SPELL_ID = 4

function onCast(caster, target)

	if caster:get():character():get() == nil then return false end

	duration = caster:get():character():get():getLevel() + 1

	local function playAnimation(actor)
		t = Target()
		t.x = actor:get():getX()
		t.y = actor:get():getY()

		animation = Blink("ffff00", 20, 20)
		animation:setLocation( t, t )
		animation:run()
	end

	local function addStatusEffect(actor)
		effect = StatusEffect(SPELL_ID, duration)
		actor:get():getStatusEffects():add( effect )
	end

	local function applyModifiers(actor)
		c = actor:get():character():get()
		if c ~= nil then
			SPELL_SAVING_THROW = 4

			c:setAttackModifier( c:getAttackModifier() + 1 )
			c:setSavingThrowModifier( SPELL_SAVING_THROW, 
										  c:getSavingThrowModifier(SPELL_SAVING_THROW) + 1 )
			c:setMoraleModifier( c:getMoraleModifier() + 1 )
		end
	end

	for a in target.actors do
		applyModifiers(a)
		if a:get():isAllyOf(caster) then			
			addStatusEffect(a)
			playAnimation(a)
		end
	end

	return true
end

function onCancel(target)

	local function removeModifiers(actor)
		c = actor:get():character():get()
		if c ~= nil then
			SPELL_SAVING_THROW = 4

			c:setAttackModifier( c:getAttackModifier() - 1 )
			c:setSavingThrowModifier( SPELL_SAVING_THROW, 
										  c:getSavingThrowModifier(SPELL_SAVING_THROW) - 1 )
			c:setMoraleModifier( c:getMoraleModifier() - 1 )
		end
	end

	for a in target.actors do
		removeModifiers(a)
	end

	return true
end
