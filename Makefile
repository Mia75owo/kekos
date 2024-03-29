# $@ = target file
# $< = first dependency
# $^ = all dependencies

all: run

kernel.bin: kernel-entry.o kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: kernel-entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	gcc -m32 -ffreestanding -c -fno-pie $< -o $@

mbr.bin: mbr.asm
	nasm $< -f bin -o $@

os-image.bin: mbr.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	$(RM) *.o *.dis mbr.bin kernel.bin
	qemu-system-x86_64 -fda $<
	$(RM) os-image.bin

clean:
	$(RM) *.bin *.o *.dis