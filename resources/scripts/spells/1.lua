--Spell: Cure Light Wounds

forge = EffectForge.new()

--Heal effect
forge:newRecipe()
forge:setEffectType(2)
forge:setEffectParam("heal", "1d6+1#0")
forge:pushRecipe()
