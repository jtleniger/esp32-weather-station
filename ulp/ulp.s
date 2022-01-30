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
    .global entry
.text
entry:
reg_wr 3,31,31,1
L.2:
L.3:
reg_rd 3,30,30
move r0,r0 #if r0 == 0 goto L.2
jump L.2, eq
reg_rd 5,14,0
move r1,last_sample_at
st r0,r1,0
L.5:
move r2,reading
ld r2,r2,0
move r1,300
sub r2,r2,r1 #{ if r2 < r1 goto L.9
add r2,r2,r1
jump L.9, ov #}
jump L.24
L.9:
reg_rd 265,30,30
move r1,wind_value
st r0,r1,0
reg_rd 265,20,20
move r1,rain_value
st r0,r1,0
move r2,last_rain_value
ld r2,r2,0
move r1,0xffff
sub r2,r2,r1 #{ if r2==r1 goto L.11 
jump 1f, eq
add r2,r2,r1
jump 2f
1:
add r2,r2,r1
jump L.11
2:           #}
move r1,rain_value
ld r1,r1,0
sub r1,r1,r2 #{ if r1==r2 goto L.11 
jump 1f, eq
add r1,r1,r2
jump 2f
1:
add r1,r1,r2
jump L.11
2:           #}
move r2,rain_edges
ld r1,r2,0
add r1,r1,1
st r1,r2,0
L.11:
move r2,last_rain_value
move r1,rain_value
ld r1,r1,0
st r1,r2,0
move r2,last_wind_value
ld r2,r2,0
move r1,0xffff
sub r2,r2,r1 #{ if r2==r1 goto L.13 
jump 1f, eq
add r2,r2,r1
jump 2f
1:
add r2,r2,r1
jump L.13
2:           #}
move r1,wind_value
ld r1,r1,0
sub r1,r1,r2 #{ if r1==r2 goto L.13 
jump 1f, eq
add r1,r1,r2
jump 2f
1:
add r1,r1,r2
jump L.13
2:           #}
move r2,wind_edges
ld r1,r2,0
add r1,r1,1
st r1,r2,0
L.13:
move r2,last_wind_value
move r1,wind_value
ld r1,r1,0
st r1,r2,0
reg_wr 3,31,31,1
L.15:
L.16:
reg_rd 3,30,30
move r0,r0 #if r0 == 0 goto L.15
jump L.15, eq
reg_rd 5,14,0
move r1,this_sample_at
st r0,r1,0
move r2,this_sample_at
ld r2,r2,0
move r1,last_sample_at
ld r1,r1,0
sub r2,r2,r1
move r1,122
sub r2,r2,r1 #{ if r2 < r1 goto L.5
add r2,r2,r1
jump L.5, ov #}
move r2,last_sample_at
move r1,this_sample_at
ld r1,r1,0
st r1,r2,0
move r2,reading
ld r2,r2,0
move r1,wind_ticks
add r2,r2,r1
move r1,wind_edges
ld r1,r1,0
rsh r1,r1,1
st r1,r2,0
move r2,wind_edges
move r1,0
st r1,r2,0
move r2,reading
ld r1,r2,0
add r1,r1,1
st r1,r2,0
jump L.5
L.23:
L.24:
reg_rd 48,19,19
and r2,r0,1
move r2,r2 #if r2 == 0 goto L.23
jump L.23, eq
wake 
reg_wr 6,24,24,0
halt 
L.21:
L.1:

.bss
    .global this_sample_at
this_sample_at:
    .space 4
    .global last_sample_at
last_sample_at:
    .space 4
    .global wind_ticks
wind_ticks:
    .space 1200
.text
halt
