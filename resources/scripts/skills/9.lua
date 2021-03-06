--Skill: Elf racial

MAGIC_WANDS_ST = 1
PARALYSIS_ST = 2
SPELL_ST = 4

function getModifiers()
						
	st1Mod = Modifier(2)
	st1Mod.Type.savingThrow = MAGIC_WANDS_ST

	st2Mod = Modifier(1)
	st2Mod.Type.savingThrow = PARALYSIS_ST

	st3Mod = Modifier(2)
	st3Mod.Type.savingThrow = SPELL_ST
	
	return {st1Mod, st2Mod, st3Mod}
end

function onUse(user, target, skill)

	local function addStatusEffect(actor)
		effect = StatusEffect(skill:getName(), skill:getScript(), -1)
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
	end

	return true;
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

	return true;
end