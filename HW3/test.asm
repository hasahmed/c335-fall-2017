.text
.syntax unified
.thumb
    adds r0, r5, r4
    subs r6, r7, r0
    adds r0, r1, r2
    adds r7, r3, r1
    adds r0, r5, r4
    adds r0, r5, 1
    subs r6, r7, 5
    cmp r5, 100
    cmp r0, 235
    adds r1, 8
    subs r1, 6
    movs r7, 200
    ands r0, r1
    eors r0, r2
    lsls r0, r3
    lsrs r0, r4
    eors r0, r3
    lsrs r0, r2
    asrs r0, r5
    lsrs r0, r7
