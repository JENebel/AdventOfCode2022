//  clear; fpc dec6; ./dec6.exe

program dec6 (input, output, stderr);
type
  arr = array[0..150] of boolean;
var
    F : TextFile;
    line : AnsiString;

function find(len: Integer): integer;
var
    i, j, c : integer;
    hset : array[0..150] of boolean;
    good : boolean;
begin
    find := -1;
    for i := len to 4900 do begin
        hset := default(arr);
        good := true;
        for j := 0 to len - 1 do begin
            c := ord(line[i-j]);
            if(hset[c]) then begin
                good := false;
                break;
            end;
            hset[c] := true;
        end;
        if good then begin
            find := i;
            break;
        end;
    end;
end;

//Program
begin
    assign(F,'input6.txt');
    reset(F);

    readLn(F, line);

    WriteLn('Part 1: ', find(4));
    WriteLn('Part 2: ', find(14));

    Close(F);
end.