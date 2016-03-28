--Skill: Human racial

EXP_PERCENT_BONUS = 3

function getModifiers()

	expMod = Modifier(10)
	expMod.Type.generic = EXP_PERCENT_BONUS
	
	return {expMod}
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