--Spell: Fireball

forge  = EffectForge.new()
level  = caster.getLevel()
damage = string.format("%dd6+0#3", level)

--Forge damage effect
forge:newRecipe()
forge:setEffectType(3)
forge:setEffectParam("damage", damage)
forge:pushRecipe()