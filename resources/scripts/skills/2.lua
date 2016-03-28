--Skill: Disarm traps
function onUse(user, target, skill)

	success = true

	for a in target.actors do
		trap = a:get():trap():get()
		if nil ~= trap and trap:isDetected() then
			if trap:getDifficulty() <= skill:getLevel() then
				trap:setArmed( not trap:isArmed() )
			else
				success = false
			end
		end
	end

	return success;
end