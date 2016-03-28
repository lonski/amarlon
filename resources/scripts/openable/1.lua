function onOpen(opener, toOpen)
  result = false;

  CLOSED_DOOR = 3
  OPENED_DOOR = 4

  if toOpen:get():getType() == CLOSED_DOOR then
    openable = toOpen:get():openable():get()
    if openable ~= nil then
      toOpen:get():setType( OPENED_DOOR )
      toOpen:get():setSymbol( string.byte("\\") )
      toOpen:get():setTransparent( true )
      toOpen:get():setBlocking( false )
      result = true
    end
  end

  return result;
end

function onClose(closer, toClose)
  result = false;

  CLOSED_DOOR = 3
  OPENED_DOOR = 4

  if toClose:get():getType() == OPENED_DOOR then
    openable = toClose:get():openable():get()
    if openable ~= nil then
      toClose:get():setType( CLOSED_DOOR )
      toClose:get():setSymbol( string.byte("+") )
      toClose:get():setTransparent( false )
      toClose:get():setBlocking( true )
      result = true
    end
  end

  return result;
end