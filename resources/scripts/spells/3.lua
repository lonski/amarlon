--Spell: Fireball
SPELL_ID = 3

function onCast(caster, target)

	radius = SpellDB:getRadius( SPELL_ID )

	local function playAnimation()
		frameDelay = 15

		tStart = Target()
		tStart.x = caster:getX()
		tStart.y = caster:getY()

		throw = Throw("fda500", string.byte("*"), frameDelay)
		throw:setLocation(tStart, target)
		throw:run()

		circle = ExpandingCircle("e25822", string.byte("*"), frameDelay, radius)
		circle:setLocation(target, target)
		circle:run()
	end
	
	dmg = Damage( string.format("%dd6+0#3", caster:getLevel()) )
	
	playAnimation()
	for a in target.actors do
		ActorWrapper(a):takeDamage( dmg, caster )
	end

	return true
end

function onCancel(target)
	return true
end
