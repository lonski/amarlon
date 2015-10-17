--Spell: Fireball
SPELL_ID = 3

function onCast(caster, target, spell)

	if caster:get():character():get() == nil then return false end

	radius = spell:getRadius()

	local function playAnimation()
		frameDelay = 15

		tStart = Target()
		tStart.x = caster:get():getX()
		tStart.y = caster:get():getY()

		throw = Throw("fda500", string.byte("*"), frameDelay)
		throw:setLocation(tStart, target)
		throw:run()

		circle = ExpandingCircle("e25822", string.byte("*"), frameDelay, radius)
		circle:setLocation(target, target)
		circle:run()
	end
	
	dmg = Damage( string.format("%dd6+0#3", caster:get():character():get():getLevel()) )
	
	playAnimation()
	for a in target.actors do
	 	c = a:get():character():get()
	 	if c ~= nil then c:takeDamage( dmg, caster ) end
	end

	return true
end
