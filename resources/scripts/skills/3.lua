--Skill: Hide
D100 = 100
function onUse(user, target, skill)

	local function canHide(actor)
		inShadow = false
		hostileActorsNearby = false
		
		HOSTILE_ACTOR_RADIUS_CHECK = 5
		
		map = actor:get():getMap():get()
		if nil ~= map then
			x = actor:get():getX()
			y = actor:get():getY()
			
			--Check for shadowed area
			coords = {
			  {x+1, y+1},
			  {x+1, y  },
			  {x+1, y-1},
			  {x,   y-1},
			  {x,   y+1},
			  {x-1, y-1},
			  {x-1, y  },
			  {x-1, y+1}
			}

			for k,v in pairs(coords) do
			  if map:isBlocked(v[1], v[2]) and not map:isTransparent(v[1], v[2]) then
				inShadow = true
				break
			  end
			end
			
			--Check for hostile actors
			actors = map:getActors( x, y, HOSTILE_ACTOR_RADIUS_CHECK )
			for i=0, actors:size() - 1 do
				actor = actors:at(i):get()
				if actor:isInFov() and actor:isHostileTo(user) then
					hostileActorsNearby = true
					break
				end
			end			
		end
		
		if hostileActorsNearby then msg("hostile mobs spotted!") end
		return inShadow and not hostileActorsNearby
	end
	
	hidden = false
	
	if canHide(user) then
		if rollDice(D100) <= skill:getLevel() then
			ai = user:get():ai():get()
			if nil ~= ai then
				if not ai:isHiding() then 
					ai:setHiding(true) 
				end
				hidden = true
			end
		end
	end
	
	return hidden;
end