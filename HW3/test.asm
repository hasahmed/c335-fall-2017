.text
.syntax unified
.thumb
    ands r0, r1
    eors r0, r2
    lsls r0, r3
    lsrs r0, r4
    adds r0, r1, r2
    eors r0, r3
    lsrs r0, r2
    asrs r0, r5
    lsrs r0, r7
    cmp r5, 100
    cmp r0, 235
    adds r1, 8
    subs r1, 6
    movs r7, 200
    adds r7, r3, r1
