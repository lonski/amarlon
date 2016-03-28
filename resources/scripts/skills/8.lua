--Skill: Dwarf racial

DEATH_ST = 0
MAGIC_WANDS_ST = 1
PARALYSIS_ST = 2
DRAGON_BREATH_ST = 3
SPELL_ST = 4

function getModifiers()
						
	stMod = Modifier(4)
	stMod.Type.savingThrow = DEATH_ST

	st2Mod = Modifier(4)
	st2Mod.Type.savingThrow = MAGIC_WANDS_ST

	st3Mod = Modifier(4)
	st3Mod.Type.savingThrow = PARALYSIS_ST

	st4Mod = Modifier(3)
	st4Mod.Type.savingThrow = DRAGON_BREATH_ST

	st5Mod = Modifier(4)
	st5Mod.Type.savingThrow = SPELL_ST
	
	return {stMod, st2Mod, st3Mod, st4Mod, st5Mod}
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