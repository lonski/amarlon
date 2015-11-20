function onTalk(talker, npc, dialog, choice)

	ret = choice.jump
	if ret == 0 then ret = -1 end
	if dialog.id == 0 then ret = 1 end

	return ret
end