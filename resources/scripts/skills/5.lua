--Skill: Silent Move (Sneak)
D100 = 100

function onUse(user, target, skill)

	local function canSneak(actor)
		isNoticed = false

		map = actor:get():getMap():get()
		if nil ~= map then
			actors = map:getActors()
			for i=0, actors:size() - 1 do
				actor = actors:at(i):get()
				if actor:isInFov() and actor:isHostileTo(user) then
					mob = actor:monster():get()
					if nil ~= mob then
						if mob:isHunting() then
							isNoticed = true
							break
						end
					end
				end
			end
		end
		
		return not isNoticed
	end

	sneaks = false
	
	if canSneak(user) then
		if rollDice(D100) <= skill:getLevel() then
			ai = user:get():ai():get()
			if nil ~= ai then
				if not ai:isSneaking() then 
					ai:setSneaking(true) 
				end
				sneaks = true
			end
		end
	end
	
	return sneaks;	
end