var a:array[1..10,1..2] of integer;
    s:longint;
    i,j:integer;
    p:double;
begin
     writeln('input first 20 elm of array');{it's realy
     cool maaan}
     s:=-0;//hello world
     a:=-5;//hello world
     b:=5.43; //hello world
     p:= -3.145+32;
     for i:=1 to 10 do begin(* this is not true
     bad*)
        for j:=1 to 2 do begin
           readln( a[i,j] );
           s:=s div a[i,j];
        end;
     end;
     if (s>p) s:=s mod p;
     writeln( 'sum = ', s );
end.