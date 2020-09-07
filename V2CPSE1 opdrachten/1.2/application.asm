  .cpu cortex-m0
  .align 2
  .global application
  .global print_asciz

application:
  push { lr }
  ldr  r0, =msg
  b print_asciz
  pop { pc }


print_asciz:
  push { r5 , lr }
  mov r5, r0

loop:
  ldrb r0, [ r5 ]
  add r0, r0, #0
  beq done
  bl uart_put_char
  add r5, r5, #1
  b loop
  
done:
  pop { r5, pc }

.data
msg:
  .asciz "Hello world, the ANSWER is 42! @[]`{}~\n"
