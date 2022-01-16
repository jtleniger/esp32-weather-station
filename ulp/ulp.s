.data
    .global rain_ticks
rain_ticks:
.long 0x0
    .global next_rain_edge
next_rain_edge:
.long 0x0
    .global wind_ticks
wind_ticks:
.long 0x0
    .global next_wind_edge
next_wind_edge:
.long 0x1
    .global reading
reading:
.long 0x0
    .global sample
sample:
.long 0x0
    .global entry
.text
.bss
entry.12:
    .space 4
.text
.bss
entry.19:
    .space 4
.text
entry:
L.2:
move r2,reading
ld r2,r2,0
move r1,30
sub r2,r2,r1 #{ if r2 < r1 goto L.6
add r2,r2,r1
jump L.6, ov #}
jump L.28
L.6:
reg_rd 265,30,30
move r1,wind
st r0,r1,0
reg_rd 265,20,20
move r1,rain
st r0,r1,0
move r2,rain
ld r2,r2,0
move r1,next_rain_edge
ld r1,r1,0
sub r2,r2,r1 #{ if r2!=r1 goto L.8 
jump 1f, eq
add r2,r2,r1
jump L.8
1:
add r2,r2,r1 #}
move r2,next_rain_edge
ld r2,r2,0
move r2,r2 #if r2 == 0 goto L.10
jump L.10, eq
move r2,rain_ticks
ld r1,r2,0
add r1,r1,1
st r1,r2,0
L.10:
move r2,next_rain_edge
ld r1,r2,0
move r1,r1 #{ if r1 goto L.13 
jump 1f, eq
jump L.13
1:           #}
move r1,1
move r3,entry.12
st r1,r3,0
jump L.14
L.13:
move r1,0
move r3,entry.12
st r1,r3,0
L.14:
move r1,entry.12
ld r1,r1,0
st r1,r2,0
L.8:
move r2,wind
ld r2,r2,0
move r1,next_wind_edge
ld r1,r1,0
sub r2,r2,r1 #{ if r2!=r1 goto L.15 
jump 1f, eq
add r2,r2,r1
jump L.15
1:
add r2,r2,r1 #}
move r2,next_wind_edge
ld r2,r2,0
move r2,r2 #{ if r2 goto L.17 
jump 1f, eq
jump L.17
1:           #}
move r2,wind_ticks
ld r1,r2,0
add r1,r1,1
st r1,r2,0
L.17:
move r2,next_wind_edge
ld r1,r2,0
move r1,r1 #{ if r1 goto L.20 
jump 1f, eq
jump L.20
1:           #}
move r1,1
move r3,entry.19
st r1,r3,0
jump L.21
L.20:
move r1,0
move r3,entry.19
st r1,r3,0
L.21:
move r1,entry.19
ld r1,r1,0
st r1,r2,0
L.15:
wait 123
move r2,sample
ld r1,r2,0
add r1,r1,1
st r1,r2,0
ld r2,r2,0
move r1,0xfe11
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
move r1,wind_ticks
ld r1,r1,0
st r1,r2,0
move r2,wind_ticks
move r1,0
st r1,r2,0
move r2,reading
ld r2,r2,0
move r1,rain_readings
add r2,r2,r1
move r1,rain_ticks
ld r1,r1,0
st r1,r2,0
move r2,rain_ticks
move r1,0
st r1,r2,0
move r2,reading
ld r1,r2,0
add r1,r1,1
st r1,r2,0
jump L.2
L.27:
L.28:
reg_rd 48,19,19
and r2,r0,1
move r2,r2 #if r2 == 0 goto L.27
jump L.27, eq
wake 
halt 
L.25:
L.1:

.bss
    .global rain
rain:
    .space 4
    .global wind
wind:
    .space 4
    .global wind_readings
wind_readings:
    .space 120
    .global rain_readings
rain_readings:
    .space 120
.text
halt
