//  clear; fpc dec5; ./dec5.exe

program dec5 (input, output, stderr);
var
    F : TextFile;
    i, j, h, index, cnt, from, dest : integer;
    stacks, stacks2 : array[0..50] of array[0..50] of char;
    heights, heights2 : array[0..50] of integer;
    line : string;
    temp : char;

function read_int(): integer;
var
    result : integer;
    c : char;
begin
    result := 0;
    while not Eof(f) do begin
        read(F, c);
        if (ord(c) > 47) and (ord(c) < 58) then result := result * 10 + ord(c) - 48
        else break;
    end;
    
    read_int := result;
end;

begin
    assign(F,'input5.txt');
    reset(F);

    while true do begin
        readLn(F, line);
        if (length(line) = 0) then break;
        
        for i := 0 to 50 do begin
            if line[i] = '\n' then break;
        
            if (ord(line[i]) in [65..90]) then begin
                index := (i - 1) div 4;
                stacks[index][heights[index]] := line[i];
                heights[index] += 1;
            end;
        end;
    end;
    
    //Invert
    for i := 0 to 50 do begin
        h := heights[i];
        for j := 0 to (h div 2) - 1 do begin
            temp := stacks[i][h-j-1];
            stacks[i][h-j-1] := stacks[i][j];
            stacks[i][j] := temp;
        end;
    end;

    stacks2 := stacks;
    heights2 := heights;

    
    while not Eof(f) do begin
        for i := 0 to 4 do read(F, temp);
        cnt := read_int();
        for i := 0 to 4 do read(F, temp);
        from := read_int() - 1;
        for i := 0 to 2 do read(F, temp);
        dest := read_int() - 1;
        read(F, temp);

        for i := 0 to cnt - 1 do begin
            heights[from]-=1;
            stacks[dest][heights[dest]] := stacks[from][heights[from]];
            heights[dest]+=1;
        end;

        for i := 0 to cnt - 1 do begin
            stacks2[dest][heights2[dest] + i] := stacks2[from][heights2[from] - cnt + i];
        end;
        heights2[from] -= cnt;
        heights2[dest] += cnt;
    end;
    
    write('Part 1: ');
    for i := 0 to 50 do begin
        if heights[i] = 0 then break;
        write(stacks[i][heights[i] - 1]);
    end;

    writeLn();
    write('Part 2: ');
    for i := 0 to 50 do begin
        if heights2[i] = 0 then break;
        write(stacks2[i][heights2[i] - 1]);
    end;

    Close(F);
end.