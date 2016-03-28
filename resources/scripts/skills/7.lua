--Skill: Darkvision
function onUse(user, target, skill)
	r = true
	
	for actor in target.actors do
		effect = StatusEffect(skill:getName(), skill:getScript(), -1)
		r = r and actor:get():getStatusEffects():add( effect )
	end
	
	return r
end

function onCancel(target)
	return true;
end