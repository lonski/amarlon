--Spell: Fireball

forge  = EffectForge.new()
level  = caster.getLevel()
damage = level .. "d6+0#3"

--Forge damage effect
forge:newRecipe()
forge:setEffectType(3)
forge:setEffectParam("damage", damage)
forge:pushRecipe()