--Skill: Find Traps
function onUse(user, target, skill)

	local function playAnimation()
		t = Target()
		t.x = user:get():getX()
		t.y = user:get():getY()
		animation = BlinkingCircle("001188", skill:getRadius(), 40, 20)
		animation:setLocation( t, t )
		animation:run()
	end

	playAnimation()
	for a in target.actors do
		trap = a:get():trap():get()
		if nil ~= trap then
			if trap:getDifficulty() <= skill:getLevel() then
				trap:setDetected(true)
			end
		end
	end

	return true;
end