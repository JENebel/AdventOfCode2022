local file = io.open("input9.txt");

local knots = {
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
    {50, 50},
  }

local set1 = {}
local set2 = {}

for line in file:lines() do
    local dir = string.sub(line, 0, 1)
    local dist = tonumber(string.sub(line, 2, #line))

    for _ = 1, dist, 1 do
        if dir == "R" then
            knots[1][1] = knots[1][1] + 1
        elseif dir == "L" then
            knots[1][1] = knots[1][1] - 1
        elseif dir == "D" then
            knots[1][2] = knots[1][2] + 1
        elseif dir == "U" then
            knots[1][2] = knots[1][2] - 1
        end

        for i = 2, 10, 1 do
            local xdiff = knots[i - 1][1] - knots[i][1]
            local ydiff = knots[i - 1][2] - knots[i][2]

            if xdiff == 2 and ydiff == 2 then
                knots[i][1] = knots[i][1] + 1
                knots[i][2] = knots[i][2] + 1
            elseif xdiff == 2 and ydiff == -2 then
                knots[i][1] = knots[i][1] + 1
                knots[i][2] = knots[i][2] - 1
            elseif xdiff == -2 and ydiff == 2 then
                knots[i][1] = knots[i][1] - 1
                knots[i][2] = knots[i][2] + 1
            elseif xdiff == -2 and ydiff == -2 then
                knots[i][1] = knots[i][1] - 1
                knots[i][2] = knots[i][2] - 1
            
            elseif xdiff == 2 then
                knots[i][1] = knots[i][1] + 1
                knots[i][2] = knots[i - 1][2]
            elseif xdiff == -2 then
                knots[i][1] = knots[i][1] - 1
                knots[i][2] = knots[i - 1][2]
            elseif ydiff == 2 then
                knots[i][2] = knots[i][2] + 1
                knots[i][1] = knots[i - 1][1]
            elseif ydiff == -2 then
                knots[i][2] = knots[i][2] - 1
                knots[i][1] = knots[i - 1][1]
            end
        end
        set1[knots[2][1]..", "..knots[2][2]] = true
        set2[knots[10][1]..", "..knots[10][2]] = true
    end
end

local size1 = 0
for _ in pairs(set1) do size1 = size1 + 1 end
local size2 = 0
for _ in pairs(set2) do size2 = size2 + 1 end

print("Part 1: "..size1)
print("Part 2: "..size2)