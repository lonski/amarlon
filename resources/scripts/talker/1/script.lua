BEER = 29
CHA = 5

function onTalk(talker, npc, dialog, choice)

	ret = choice.jump
	if ret == 0 then ret = -1 end
	if dialog.id == 0 then ret = 1 end

	local function testForCHA()
		c = talker:get():character():get()
		if c:abilityRoll( CHA,0 ) then
			ret = 5
		else
			ret = 4
		end
	end

	local function pay2gpAndGiveBeer()
		inv = talker:get():inventory():get()
		gold = inv:getGoldAmount()
		if gold >= 2 then
			inv:modifyGoldAmount(-2,true)
			inv:add( ActorDB:fetch(BEER),true )
		else
			ret = 6
		end
	end

	local function pay1gpAndGiveBeer()
		inv = talker:get():inventory():get()
		gold = inv:getGoldAmount()
		if gold >= 1 then
			inv:modifyGoldAmount(-1,true)
			inv:add( ActorDB:fetch(BEER),true )
		else
			ret = 6
		end
	end

	funcs = {}
	--[Dialog, Choice] = Function
	funcs["3,1"] = testForCHA
	funcs["3,2"] = pay2gpAndGiveBeer
	funcs["4,1"] = pay2gpAndGiveBeer
	funcs["5,1"] = pay1gpAndGiveBeer

	pcall( function() funcs[ string.format("%d,%d", dialog.id, choice.id) ]() end )

	return ret
end