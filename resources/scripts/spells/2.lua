--Spell: Magic Missile

forge = EffectForge.new()

function addMissile()
	forge:newRecipe()
	forge:setEffectType(3)
	forge:setEffectParam("damage", "1d6+1#2")
	forge:pushRecipe()
end

addMissile()
if caster.getLevel() >= 4  then addMissile() end
if caster.getLevel() >= 7  then addMissile() end
if caster.getLevel() >= 10 then addMissile() end
if caster.getLevel() >= 13 then addMissile() end


