--Skill: Open Locks
function onUse(user, target, skill)

	unlocked = true;

	for a in target.actors do
		openable = a:get():openable():get()
		if nil ~= openable then
			if openable:isLocked() and openable:getLockLevel() <= skill:getLevel() then
				openable:unlock()
			else
				unlocked = false;
			end
		end
	end

	return unlocked;
end