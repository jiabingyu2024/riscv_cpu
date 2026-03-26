SIM_OUT = sim/smoke.out
FILELIST = sim/filelist.f

.PHONY: smoke clean

smoke:
	iverilog -g2012 -o $(SIM_OUT) -c $(FILELIST)
	vvp $(SIM_OUT)

clean:
	rm -f $(SIM_OUT) sim/smoke.vcd
