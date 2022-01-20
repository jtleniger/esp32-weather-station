.data
    .global rain_edges
rain_edges:
.long 0x0
    .global wind_edges
wind_edges:
.long 0x0
    .global wind_value
wind_value:
.long 0x0
    .global last_wind_value
last_wind_value:
.long 0xffff
    .global rain_value
rain_value:
.long 0x0
    .global last_rain_value
last_rain_value:
.long 0xffff
    .global reading
reading:
.long 0x0
    .global sample
sample:
.long 0x0
    .global entry
.text
entry:
L.2:
move r2,reading
ld r2,r2,0
move r1,300
sub r2,r2,r1 #{ if r2 < r1 goto L.6
add r2,r2,r1
jump L.6, ov #}
jump L.18
L.6:
reg_rd 265,30,30
move r1,wind_value
st r0,r1,0
reg_rd 265,20,20
move r1,rain_value
st r0,r1,0
move r2,last_rain_value
ld r2,r2,0
move r1,0xffff
sub r2,r2,r1 #{ if r2==r1 goto L.8 
jump 1f, eq
add r2,r2,r1
jump 2f
1:
add r2,r2,r1
jump L.8
2:           #}
move r1,rain_value
ld r1,r1,0
sub r1,r1,r2 #{ if r1==r2 goto L.8 
jump 1f, eq
add r1,r1,r2
jump 2f
1:
add r1,r1,r2
jump L.8
2:           #}
move r2,rain_edges
ld r1,r2,0
add r1,r1,1
st r1,r2,0
L.8:
move r2,last_rain_value
move r1,rain_value
ld r1,r1,0
st r1,r2,0
move r2,last_wind_value
ld r2,r2,0
move r1,0xffff
sub r2,r2,r1 #{ if r2==r1 goto L.10 
jump 1f, eq
add r2,r2,r1
jump 2f
1:
add r2,r2,r1
jump L.10
2:           #}
move r1,wind_value
ld r1,r1,0
sub r1,r1,r2 #{ if r1==r2 goto L.10 
jump 1f, eq
add r1,r1,r2
jump 2f
1:
add r1,r1,r2
jump L.10
2:           #}
move r2,wind_edges
ld r1,r2,0
add r1,r1,1
st r1,r2,0
L.10:
move r2,last_wind_value
move r1,wind_value
ld r1,r1,0
st r1,r2,0
move r2,sample
ld r1,r2,0
add r1,r1,1
st r1,r2,0
ld r2,r2,0
move r1,32000
sub r2,r2,r1 #{ if r2 < r1 goto L.2
add r2,r2,r1
jump L.2, ov #}
move r2,sample
move r1,0
st r1,r2,0
move r2,reading
ld r2,r2,0
move r1,wind_readings
add r2,r2,r1
move r1,wind_edges
ld r1,r1,0
rsh r1,r1,1
st r1,r2,0
move r2,wind_edges
move r1,0
st r1,r2,0
move r2,reading
ld r2,r2,0
move r1,rain_readings
add r2,r2,r1
move r1,rain_edges
ld r1,r1,0
rsh r1,r1,1
st r1,r2,0
move r2,rain_edges
move r1,0
st r1,r2,0
move r2,reading
ld r1,r2,0
add r1,r1,1
st r1,r2,0
jump L.2
L.17:
L.18:
reg_rd 48,19,19
and r2,r0,1
move r2,r2 #if r2 == 0 goto L.17
jump L.17, eq
wake 
reg_wr 6,24,24,0
halt 
L.15:
L.1:

.bss
    .global wind_readings
wind_readings:
    .space 1200
    .global rain_readings
rain_readings:
    .space 1200
.text
halt
