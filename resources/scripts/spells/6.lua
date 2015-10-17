--Spell: Sleep
SPELL_ID = 6
SPELL_SAVING_THROW = 4

function onCast(caster, target, spell)
	
	if caster:get():character():get() == nil then return false end

	local function playAreaAnimation()
		radius = spell:getRadius()
		animation = BlinkingCircle("333333", radius, 40, 1)
		animation:setLocation( target, target )
		animation:run()
	end

	local function playAnimation(actor)
		t = Target()
		t.x = actor:get():getX()
		t.y = actor:get():getY()

		animation = Blink("111111", 10, 10)
		animation:setLocation( t, t )
		animation:run()
	end

	local function addStatusEffect(actor)
		duration = caster:get():character():get():getLevel() * 5 + 1
		effect = StatusEffect(spell:getName(), spell:getScript(), duration)
		return actor:get():getStatusEffects():add( effect )
	end

	playAreaAnimation()

	for a in target.actors do
		if not a:get():isAllyOf(caster) then
			c = a:get():character():get()
			if c ~= nil then
				if c:getLevel() < 4 then
					if not c:rollSavingThrow(SPELL_SAVING_THROW) then
						addStatusEffect(a)
						playAnimation(a)
					end
				end
			end
		end
	end

	return true
end

function onCancel(target)
	return true;
end