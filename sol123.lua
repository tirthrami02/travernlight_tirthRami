-- Q1:
-- Original Code:
local function releaseStorage(player)
    player:setStorageValue(1000, -1)
end

function onLogout(player)
    if player:getStorageValue(1000) == 1 then
        addEvent(releaseStorage, 1000, player)
    end
    return true
end
-- My solution:

-- I did not found anyb syntax problem here. Every thing works fine but there is a logical problem here.
-- I will check if 'player' is exists or not and then assign the value.
-- I will we assign -1 in the 'releaseStorage' function.
-- Then I only return true if we execute 'addEvent' function in onLogout function otherwise I will return false.

-- My Code:

local function releaseStorage(player)
    -- checks if a player is not a null entity
    if player then
        -- set the value to -1
        player:setStorageValue(1000, -1)
    end
end

function onLogout(player)
    -- check original condition, this will true because we assign value to -1 in releaseStorage function
    if player:getStorageValue(1000) == -1 then
        addEvent(releaseStorage, 1000, player)
        -- if addEvent occurs then only we return true here
        return true
    end
    -- if we can't execute addEvent, then we have to return false here.
    return false
end
---------------------------------------------------------------------------------------------------------------
-- Q2:
-- Original Code:

function printSmallGuildNames(memberCount)
    -- this method is supposed to print names of all guilds that have less than memberCount max members
    local selectGuildQuery = "SELECT name FROM guilds WHERE max_members < %d;"
    local resultId = db.storeQuery(string.format(selectGuildQuery, memberCount))
    local guildName = result.getString("name")
    print(guildName)
end

-- My Solution:
-- This code will not work. Because after calculating resultId we do not use this in 'guildName',
-- so our purpose will not fulfilled.
-- And also we don't repeat the process to print 'guildName' parameter, for printing all names of all guilds we have 
-- to repeat that line untill we found 'resultId' is null.

-- My Code:

function printSmallGuildNames(memberCount)
    local selectGuildQuery = "SELECT name FROM guilds WHERE max_members < %d;"
    local resultId = db.storeQuery(string.format(selectGuildQuery, memberCount))
    --  until then every thing is good...
    --  Now we are running loop until we found resultId is null.

    if resultId ~= nil then
        repeat
            -- Now, I fixxed guildName sytax by passing 'resultId' parameter in result.getString() function.
            local guildName = result.getString(resultId, "name")
            -- printing it.
            print(guildName)
        until not result.next(resultId)
    else
        -- Printing Error notification we face any error.
        print("Error executing query")
    end
end

-- This will work as per demand.

---------------------------------------------------------------------------------------------------------------
-- Q3:
-- Original Code:

function do_sth_with_PlayerParty(playerId, membername)
    player = Player(playerId)
    local party = player:getParty()

    for k, v in pairs(party:getMembers()) do
        if v == Player(membername) then
            party:removeMember(Player(membername))
        end
    end
end

-- My Solution:
-- Here they did not define 'player' as 'local'
-- And they are also making a new 'Player' every time inside the if sentences, we can use 'memberToRemove' directly instead of making a new object
-- My Code:

function do_sth_with_PlayerParty(playerId, membername)
    local player = Player(playerId)
    local party = player:getParty()

    -- Create the player object once, because previosuly we were creating objects every time in the loop
    local memberToRemove = Player(membername) 

    local members = party:getMembers()
    -- make an array to access all elements of 'party'

    for i = #members, 1, -1 do
        if members[i] == memberToRemove then
            party:removeMember(memberToRemove)
        end
    end
end

---------------------------------------------------------------------------------------------------------------
-- Q4:
-- Original Code:
