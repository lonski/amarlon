--Item: Pantry Key
function onUse(user, item, target)
	LOCK_ID=1
	for a in target.actors do
	 	o = a:get():openable():get()
	 	if (o ~= nil) and (o:getLockId() == LOCK_ID) then 
	 	 	if o:isLocked() then
		  	o:unlock()
		 	elseif a:get():isBlocking() then --lock only if actor is blocking (do not lock opened door)
		 		o:lock()
		 	end
	 	end
	end

	return true
end
