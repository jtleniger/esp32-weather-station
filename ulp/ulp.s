.data
    .global rainTicks
rainTicks:
.long 0x0
    .global nextRainEdge
nextRainEdge:
.long 0x0
    .global rainDebounceCounter
rainDebounceCounter:
.long 0xa
    .global windTicks
windTicks:
.long 0x0
    .global nextWindEdge
nextWindEdge:
.long 0x0
    .global windDebounceCounter
windDebounceCounter:
.long 0xa
    .global entry
.text
.bss
entry.rain:
    .space 4
.text
.bss
entry.wind:
    .space 4
.text
.bss
entry.12:
    .space 4
.text
.bss
entry.21:
    .space 4
.text
entry:
L.2:
reg_rd 265,31,30
rsh r2,r0,9
move r3,entry.rain
st r2,r3,0
reg_rd 265,29,14
rsh r2,r0,14
move r3,entry.wind
st r2,r3,0
move r2,entry.rain
ld r2,r2,0
and r2,r2,1
move r3,entry.rain
st r2,r3,0
move r2,entry.wind
ld r2,r2,0
and r2,r2,1
move r3,entry.wind
st r2,r3,0
move r2,entry.rain
ld r2,r2,0
move r1,nextRainEdge
ld r1,r1,0
sub r2,r2,r1 #{ if r2==r1 goto L.6 
jump 1f, eq
add r2,r2,r1
jump 2f
1:
add r2,r2,r1
jump L.6
2:           #}
move r2,rainDebounceCounter
move r1,10
st r1,r2,0
jump L.7
L.6:
move r2,rainDebounceCounter
ld r2,r2,0
move r2,r2 #if r2 == 0 goto L.8
jump L.8, eq
move r2,rainDebounceCounter
ld r1,r2,0
sub r1,r1,1
st r1,r2,0
jump L.9
L.8:
move r2,rainDebounceCounter
move r1,10
st r1,r2,0
move r2,nextRainEdge
ld r2,r2,0
move r2,r2 #if r2 == 0 goto L.10
jump L.10, eq
move r2,rainTicks
ld r1,r2,0
add r1,r1,1
st r1,r2,0
L.10:
move r2,nextRainEdge
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
L.9:
L.7:
move r2,entry.wind
ld r2,r2,0
move r1,nextWindEdge
ld r1,r1,0
sub r2,r2,r1 #{ if r2==r1 goto L.15 
jump 1f, eq
add r2,r2,r1
jump 2f
1:
add r2,r2,r1
jump L.15
2:           #}
move r2,windDebounceCounter
move r1,10
st r1,r2,0
jump L.2
L.15:
move r2,windDebounceCounter
ld r2,r2,0
move r2,r2 #if r2 == 0 goto L.17
jump L.17, eq
move r2,windDebounceCounter
ld r1,r2,0
sub r1,r1,1
st r1,r2,0
jump L.2
L.17:
move r2,windDebounceCounter
move r1,10
st r1,r2,0
move r2,nextWindEdge
ld r2,r2,0
move r2,r2 #{ if r2 goto L.19 
jump 1f, eq
jump L.19
1:           #}
move r2,windTicks
ld r1,r2,0
add r1,r1,1
st r1,r2,0
L.19:
move r2,nextWindEdge
ld r1,r2,0
move r1,r1 #{ if r1 goto L.22 
jump 1f, eq
jump L.22
1:           #}
move r1,1
move r3,entry.21
st r1,r3,0
jump L.23
L.22:
move r1,0
move r3,entry.21
st r1,r3,0
L.23:
move r1,entry.21
ld r1,r1,0
st r1,r2,0
jump L.2
L.1:

.bss
    .global windBuckets
windBuckets:
    .space 1200
    .global rainBuckets
rainBuckets:
    .space 1200
.text
halt
