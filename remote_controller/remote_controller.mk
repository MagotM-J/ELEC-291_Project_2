SHELL=cmd
CC=c51
COPT=
LOPT=
OBJS=remote_controller.obj IR_emitter.obj joy_stick.obj

remote_controller.hex: $(OBJS)
	$(CC) $(LOPT) $(OBJS)
	@echo Done!
	
remote_controller.obj: remote_controller.c IR_emitter.h joy_stick.h
	$(CC) $(COPT) -c remote_controller.c

IR_emitter.obj: IR_emitter.c IR_emitter.h
	$(CC) $(COPT) -c IR_emitter.c

joy_stick.obj: joy_stick.c joy_stick.h
	$(CC) $(COPT) -c joy_stick.c

clean:
	@del $(OBJS) *.asm *.lkr *.lst *.map *.hex *.map 2> nul

LoadFlash:
	EFM8_prog -ft230 -r remote_controller.hex

Dummy: remote_controller.hex remote_controller.Map
	@echo Nothing to see here!

explorer:
	cmd /c start explorer .