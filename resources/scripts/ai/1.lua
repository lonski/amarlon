STATE_WANDERING            = 1
STATE_CAST_BUFF_SELF       = 2
STATE_MELEE_ATTACK         = 3
STATE_CAST_OFFENSIVE_SPELL = 4
STATE_ATTACK_RANGE         = 5
STATE_MOVE_TO_TARGET       = 6
STATE_EVADING              = 7
STATE_HEAL                 = 8
STATE_IDLE                 = 9

RANGE_CLOSE = 1.9

function onUpdate(actor)

  --=== INIT ===--

  ai = actor:get():ai():get()
  enemies = ai:getEnemiesInFov()

  --=== FUNCTIONS ===--

  local function isEnemySpotted()
    return enemies:size() > 0
  end

  local function getClosestEnemy()
    closestEnemy = ActorPtr()
    range = 666
    for i=0,enemies:size() - 1 do
      e = enemies:at(i)
      r = calculateDistance(actor, e)
      if r < range and r > 0 then
        closestEnemy = e        
        range = r
      end
    end
    return closestEnemy
  end

  local function chooseTarget()    
    if enemies:size() > 1 then
      ai:setTarget( getClosestEnemy() )
    elseif enemies:size() > 0 then
      ai:setTarget( enemies:at(0) )
    end
  end

  local function getEnemyDistance()
    return calculateDistance(actor, ai:getTarget():getFirstActor())
  end

  local function isTracking()
    return ai:getCurrentState() == STATE_MOVE_TO_TARGET and ai:hasTarget()
  end

  --=== LOGIC ===--

  if isEnemySpotted() or isTracking() then
  
    chooseTarget()

    if ai:hasTarget() then
    
      if getEnemyDistance() > RANGE_CLOSE then
        ai:changeState( STATE_MOVE_TO_TARGET )
      else
        ai:changeState( STATE_MELEE_ATTACK )
      end
      
    else
      ai:changeState( STATE_IDLE )
    end
    
  else
    ai:changeState( STATE_IDLE )
  end

end