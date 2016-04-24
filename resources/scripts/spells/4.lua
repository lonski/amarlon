--Spell: Bless
SPELL_ID = 4
SPELL_SAVING_THROW = 4
AB_MODIFIER_TYPE = 0
MORALE_MODIFIER_TYPE = 1
CAST_RESULT_SUCCESS = 0
CAST_RESULT_RESSISTED = 1

function getModifiers()
	
	abMod = Modifier(1)
	abMod.Type.generic = AB_MODIFIER_TYPE						
			
	stMod = Modifier(1)
	stMod.Type.savingThrow = SPELL_SAVING_THROW
	
	moraleMod = Modifier(1)
	moraleMod.Type.generic = MORALE_MODIFIER_TYPE
	
	return {abMod, stMod, moraleMod}
end

function onCast(caster, target, spell)

	if caster:get():character():get() == nil then return false end

	duration = caster:get():character():get():getLevel() * 5 + 1 

	local function playAreaAnimation()
		radius = spell:getRadius()
		animation = BlinkingCircle("333300", radius, 40, 1)
		animation:setLocation( target, target )
		animation:run()
	end

	local function playAnimation(actor)
		t = Target()
		t.x = actor:get():getX()
		t.y = actor:get():getY()

		animation = Blink("ffff00", 20, 20)
		animation:setLocation( t, t )
		animation:run()
	end

	local function addStatusEffect(actor)
		effect = StatusEffect(spell:getName(), spell:getScript(), duration)
		return actor:get():getStatusEffects():add( effect )
	end

	local function applyModifiers(actor)
		c = actor:get():character():get()
		if c ~= nil then
			for k, mod in pairs(getModifiers()) do
				c:addModifier( mod )
			end
		end
	end

	playAreaAnimation()

	for a in target.actors do		
		if a:get():isAllyOf(caster) then			
			if addStatusEffect(a) then
				applyModifiers(a)
			end
			playAnimation(a)
		end
	end

	return CAST_RESULT_SUCCESS
end

function onCancel(target)

	local function removeModifiers(actor)
		c = actor:get():character():get()
		if c ~= nil then
			for k, mod in pairs(getModifiers()) do
				c:removeModifier( mod )
			end
		end
	end

	for a in target.actors do
		removeModifiers(a)
	end

	return true
end
