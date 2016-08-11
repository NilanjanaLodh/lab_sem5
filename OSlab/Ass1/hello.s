# -----------------------------------------------------------------------------
# Just for testing ; the system calls of this listem in analyseCalls
# A 64-bit Linux standalone program that writes "Hello, World" to the console
# using system calls only.  The program does not need to link with any external
# libraries at all.
#
# System calls used:
#   1: write(fileid, bufferAddress, numberOfBytes)
#   60: exit(returnCode)
#
#
# Assemble and link in one step:
#     gcc -nostdlib hello.s
# To see all system calls without being annoyed by the actual output, do :
# strace ./bin_hello > dummy_file
# -----------------------------------------------------------------------------

        .global _start

        .text
_start:
        # write(1, message, 13)
        mov     $1, %rax                # system call 1 is write
        mov     $1, %rdi                # file handle 1 is stdout
        mov     $message, %rsi          # address of string to output
        mov     $13, %rdx               # number of bytes
        syscall                         # invoke operating system to do the write

        # exit(0)
        mov     $60, %rax               # system call 60 is exit
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
message:
        .ascii  "Hello, World\n"