  .cpu cortex-m0
  .align 2
  .global application
  .global print_asciz
  .global changeletters

print_asciz:
  push { r5 , lr }
  mov r5, r0
loop:
  ldrb r0, [ r5 ]
  add r0, r0, #0
  beq done
  bl changeletters
  bl uart_put_char
  add r5, r5, #1
  b loop
done:
  pop { r5, pc }

application:
  push { lr }
  ldr  r0, =msg
  bl print_asciz
  pop { pc }

changeletters:
  push { lr }
  cmp r0, #97
  bge islowercase
  cmp r0, #65
  bge isuppercase
  b end
islowercase:
  cmp r0, #122
  bls lowercasecalc
  b end
isuppercase:
  cmp r0, #90
  bls uppercasecalc
  b end
lowercasecalc:
  sub r0, r0, #32
  b end
uppercasecalc:
  add r0, r0, #32
  b end

end:
  pop { pc }


.data
msg:
  .asciz "Hello world, the ANSWER is 42! @[]`{}~\n"
