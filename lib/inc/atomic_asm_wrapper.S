/* 64-bit for pointers needed */

.globl cmpxchg_64
cmpxchg_64:
  mov %rsi, %rax # move old value to check into %rax
  lock cmpxchg %rdx, (%rdi) # (%rdi) = (%rdi) == %rax ? %rdx : (%rdi)
  ret

.global xchg_64
xchg_64:
  mov %rsi, %rax # move value to exchange into %rax
  lock xchg %rax, (%rdi) # (%rdi) = %rax, %rax = (%rdi)
  ret
