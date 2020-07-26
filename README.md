# instat
INSTruction STATistics: utility for printing amount of used instructions in code sections of PE x86_64.

## Building
```
cmake -B build -Dzydis_DIR=<PATH TO ZYDIS CMAKE DIR> -Dzycore_DIR=<PATH TO ZYCORE CMAKE DIR>
cmake --build build --config Release
```

## Example Usage
```
.\instat.exe .\instat.exe
```

## Example Output
```
int3:57514
mov:8343
jmp:1749
cmp:1557
add:1422
lea:1408
call:1079
ret:962
movzx:955
jz:885
test:811
```
