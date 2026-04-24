# core_new

`core_new` is a clean seven-stage pipeline skeleton that keeps the current
external memory semantics:

- `irom`: synchronous fetch-side instruction port
- `dram/perip`: synchronous data-side memory port with `M1` issue and `M2` load handling

## Structure

- `core_new.sv`
  - top-level integration for `PC -> IF -> ID -> EX -> M1 -> M2 -> WB`
- `frontend/`
  - `pc_stage.sv`: PC register only
  - `fetch_stage.sv`: align fetched instruction with PC and prediction metadata
  - `bpu_top.sv`: predictor lookup and training
  - `redirect_ctrl.sv`: next-PC arbitration
- `decode/`
  - `decode_stage.sv`: bundle decoder, imm generator, and regfile
  - `decoder.sv`: instruction decode and control generation
  - `imm_gen.sv`: immediate generation
  - `regfile.sv`: 2R1W register file
- `execute/`
  - `execute_stage.sv`: EX datapath and branch/redirect integration
  - `alu.sv`: pure ALU
  - `branch_unit.sv`: branch/jump resolve and BPU training signals
  - `forward_ctrl.sv`: forwarding control for ALU and branch paths
- `mem/`
  - `mem1_stage.sv`: drive DRAM write-side signals in `M1`
  - `mem2_stage.sv`: load-side data handling in `M2`
  - `load_data_align.sv`: byte/half/word load expansion
- `wb/`
  - `wb_stage.sv`: final writeback mux
- `control/`
  - `hazard_ctrl.sv`: load-use hazard detect only
  - `pipeline_ctrl.sv`: stall/flush generation only
- `pipe/`
  - `pipe_pc_if.sv`: `PC/IF` register
  - `pipe_if_id.sv`: `IF/ID` register
  - `pipe_id_ex.sv`: `ID/EX` register
  - `pipe_ex_m1.sv`: `EX/M1` register
  - `pipe_m1_m2.sv`: `M1/M2` register
  - `pipe_m2_wb.sv`: `M2/WB` register

## Naming

- File names stay close to the stage/function name.
- Module names use the `core_new_` prefix to avoid collisions with existing `rtl/core` modules.
