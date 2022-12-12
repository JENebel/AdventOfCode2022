program dec8 (input, output, stderr);
var
    F: TextFile;
    line: AnsiString;
    score, best: LongInt;
    width, height, visible, i, j, x, y: Integer;
    forest: array[0..100] of array[0..100] of Integer;

function is_visible(x: integer; y: integer): Boolean;
var
    vis: Boolean;
    h: Integer;
begin
    h := forest[x][y];

    vis := True;
    for i := x + 1 to width - 1 do 
      if forest[i][y] >= h then vis := false;
    if vis then exit(True);

    vis := True;
    for i := x - 1 downto 0 do
      if forest[i][y] >= h then vis := false;
    if vis then exit(True);

    vis := True;
    for i := y + 1 to height - 1 do 
      if forest[x][i] >= h then vis := false;
    if vis then exit(True);

    vis := True;
    for i := y - 1 downto 0 do 
      if forest[x][i] >= h then vis := false;
    if vis then exit(True);

    is_visible := false;
end;

function scenic_score(x: integer; y: integer): LongInt;
var
    h: Integer;
    trees, scn: LongInt;
begin
    h := forest[x][y];
    trees := 0;
    scn := 0;

    for i := x + 1 to width - 1 do begin
      trees += 1;
      if forest[i][y] >= h then break;
    end;
    scn := trees;
    trees := 0;

    for i := x - 1 downto 0 do begin
      trees += 1;
      if forest[i][y] >= h then break;
    end;
    scn := trees * scn;
    trees := 0;

    for i := y + 1 to height - 1 do begin
      trees += 1;
      if forest[x][i] >= h then break;
    end;
    scn := trees * scn;
    trees := 0;

    for i := y - 1 downto 0 do begin
      trees += 1;
      if forest[x][i] >= h then break;
    end;
    scn := trees * scn;

    scenic_score := scn;
end;

//Program
begin
    Assign(F,'input8.txt');
    Reset(F);

    //Get size
    height := 0;
    while not Eof(F) do begin
      ReadLn(F, line);
      height += 1;
      width := length(line);
    end;
    Reset(F);

    //Load data
    for i := 1 to height do begin
      ReadLn(F, line);
      for j := 1 to width do begin
        forest[i - 1][j - 1] := ord(line[j]) - 48;
      end;
    end;

    //Solve
    visible := 0;
    best := 0;
    for x := 0 to height - 1 do begin
      for y := 0 to width - 1 do begin
        score := scenic_score(x, y);
        if score < 0 then WriteLn(score);
        if score > best then best := score;

        if is_visible(x, y) then begin 
          visible += 1;
          //Write(forest[x][y]);
        end// else Write('.');
      end;
      //WriteLn();
    end;

    WriteLn('Part 1: ', visible);
    WriteLn('Part 2: ', best);

    Close(F);
end.