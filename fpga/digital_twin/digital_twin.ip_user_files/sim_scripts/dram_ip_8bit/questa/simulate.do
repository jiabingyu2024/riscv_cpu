onbreak {quit -f}
onerror {quit -f}

vsim  -lib xil_defaultlib dram_ip_8bit_opt

set NumericStdNoWarnings 1
set StdArithNoWarnings 1

do {wave.do}

view wave
view structure
view signals

do {dram_ip_8bit.udo}

run 1000ns

quit -force
