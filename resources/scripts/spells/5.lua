--Spell: Shield
SPELL_ID = 5

DMG_PHYSICAL = 1
DMG_MISSILE  = 6

function getModifiers()
	
	acMod = Modifier(3)
	acMod.Type.ac = DMG_PHYSICAL
	
	acModMissile = Modifier(6)
	acModMissile.Type.ac = DMG_MISSILE
	
	return { acMod, acModMissile }
end

function onCast(caster, target, spell)
	
	if caster:get():character():get() == nil then return false end

	duration = caster:get():character():get():getLevel() + 6

	local function playAnimation(actor)
		t = Target()
		t.x = actor:get():getX()
		t.y = actor:get():getY()

		animation = Blink("333366", 20, 20)
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

	for a in target.actors do
		if addStatusEffect(a) then
			applyModifiers(a)
		end
		playAnimation(a)
	end

	return true
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
