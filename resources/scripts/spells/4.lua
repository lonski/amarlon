--Spell: Bless

forge    = EffectForge.new()
duration = caster.getLevel() + 1

--Forge Attack roll bonus effect
forge:newRecipe()
forge:setEffectType(4)
forge:setEffectParam("time", duration)
forge:setEffectParam("modifier", 1)
forge:pushRecipe()

--Forge Spell Saving Throw bonus effect
forge:newRecipe()
forge:setEffectType(5)
forge:setEffectParam("time", duration)
forge:setEffectParam("modifier", 1)
forge:setEffectParam("throw_type", 4)
forge:pushRecipe()

--Forge Morale bonus effect
forge:newRecipe()
forge:setEffectType(6)
forge:setEffectParam("time", duration)
forge:setEffectParam("modifier", 1)
forge:pushRecipe()
