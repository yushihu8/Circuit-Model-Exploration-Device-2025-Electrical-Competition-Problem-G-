/**********************************************************
>> 模块名       :寄存器控制模块
>> 信息         :控制FPGA内部寄存器的读写
>> 版本         :v0.0
>> 时间         :2025-11-21
>> 作者         :ts
************************************************************/

module reg_control(
    clk,
    rstn,

    w_reg_addr,
    w_reg_data,
    w_reg_en,

    r_reg_addr,
    r_reg_data,
    r_reg_en,

    w_ram_addr,
    w_ram_data,
    w_ram_en,

    r_ram_addr,
    r_ram_data,
    r_ram_en,

    //自定义寄存器端口
    adc_ram_en,

    coef_a1,
    coef_a2,
    coef_b0,
    coef_b1,
    coef_b2,
    coef_lode_en,
    adc_rata
  );

  input clk;
  input rstn;

  input w_reg_en;
  input [15:0]w_reg_addr;
  input [15:0]w_reg_data;

  input r_reg_en;
  input [15:0]r_reg_addr;
  output reg[15:0]r_reg_data;


  output reg [15:0]w_ram_addr;
  output [15:0]w_ram_data;
  output reg w_ram_en;

  output[15:0]r_ram_addr;
  input [15:0]r_ram_data;
  output r_ram_en;

  //自定义寄存器
  output reg adc_ram_en;


  //系数输出
  output reg[47:0] coef_a1;
  output reg[47:0] coef_a2;
  output reg[47:0] coef_b0;
  output reg[47:0] coef_b1;
  output reg[47:0] coef_b2;

  output reg [15:0]adc_rata;

  output reg coef_lode_en;

  reg r_reg_en_temp;

  localparam COEF_A1_0 = 16'ha001,
             COEF_A1_1 = 16'ha002,
             COEF_A1_2 = 16'ha003,

             COEF_A2_0 = 16'ha004,
             COEF_A2_1 = 16'ha005,
             COEF_A2_2 = 16'ha006,

             COEF_B0_0 = 16'ha007,
             COEF_B0_1 = 16'ha008,
             COEF_B0_2 = 16'ha009,

             COEF_B1_0 = 16'ha00a,
             COEF_B1_1 = 16'ha00b,
             COEF_B1_2 = 16'ha00c,

             COEF_B2_0 = 16'ha00d,
             COEF_B2_1 = 16'ha00e,
             COEF_B2_2 = 16'ha00f,

             ADC_RATE = 16'ha010,

             COEF_LODE_EN = 16'hbb02,

             ADC_RAM_EN_ADDR = 16'hbb01;

  assign w_ram_data = w_reg_data;
  assign r_ram_en = r_reg_en;
  assign r_ram_addr = r_reg_addr;

  always @(posedge clk or negedge rstn)
  begin
    if(~rstn)
    begin
      r_reg_data <= 16'd0;
      w_ram_en <= 1'd0;

      w_ram_addr <= 16'd0;

      r_reg_en_temp <= 1'd0;

      //自定义寄存器初始化
      adc_ram_en <= 1'd0;
      coef_lode_en <= 1'd0;

      coef_a1 <= 48'd0;
      coef_a2 <= 48'd0;
      coef_b0 <= 48'd0;
      coef_b1 <= 48'd0;
      coef_b2 <= 48'd0;

      adc_rata <= 16'd99;
    end
    else
    begin
      //写寄存器
      if(w_reg_en)
      begin
        case (w_reg_addr)
          ADC_RAM_EN_ADDR:
            adc_ram_en <= 1'd1;
          COEF_A1_0:
            coef_a1[47:32] <= w_reg_data;
          COEF_A1_1:
            coef_a1[31:16] <= w_reg_data;
          COEF_A1_2:
            coef_a1[15:0] <= w_reg_data;
          COEF_A2_0:
            coef_a2[47:32] <= w_reg_data;
          COEF_A2_1:
            coef_a2[31:16] <= w_reg_data;
          COEF_A2_2:
            coef_a2[15:0] <= w_reg_data;
          COEF_B0_0:
            coef_b0[47:32] <= w_reg_data;
          COEF_B0_1:
            coef_b0[31:16] <= w_reg_data;
          COEF_B0_2:
            coef_b0[15:0] <= w_reg_data;
          COEF_B1_0:
            coef_b1[47:32] <= w_reg_data;
          COEF_B1_1:
            coef_b1[31:16] <= w_reg_data;
          COEF_B1_2:
            coef_b1[15:0] <= w_reg_data;
          COEF_B2_0:
            coef_b2[47:32] <= w_reg_data;
          COEF_B2_1:
            coef_b2[31:16] <= w_reg_data;
          COEF_B2_2:
            coef_b2[15:0] <= w_reg_data;
          COEF_LODE_EN:
            coef_lode_en <= 1'd1;
          ADC_RATE:
            adc_rata <= w_reg_data;
          default:
          begin
            //写ram
            if(w_reg_addr <= 'd2047)
            begin
              w_ram_en <= 1'd1;
              w_ram_addr <= w_reg_addr;
            end
          end
        endcase
      end
      else if(r_reg_en_temp)
      begin
        case (r_reg_addr)
          //读寄存器
          default:
          begin
            //读ram
            if(r_reg_addr <= 'd2047)
              r_reg_data <= r_ram_data;
          end
        endcase
      end
      else
      begin
        w_ram_en <= 1'd0;
        adc_ram_en <= 1'd0;
        coef_lode_en <= 1'd0;

        r_reg_en_temp <= r_reg_en;
      end
    end
  end


endmodule


