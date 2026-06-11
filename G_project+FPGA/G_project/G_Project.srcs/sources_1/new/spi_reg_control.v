module spi_reg_control(
    clk,
    rstn,
    spi_cs,
    spi_clk,
    spi_mosi,
    spi_miso,

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
  input spi_cs;
  input spi_clk;
  input spi_mosi;
  output spi_miso;

  //自定义寄存器端口
  output adc_ram_en;
  output [47:0] coef_a1;
  output [47:0] coef_a2;
  output [47:0] coef_b0;
  output [47:0] coef_b1;
  output [47:0] coef_b2;
  output coef_lode_en;

  wire [15:0]w_reg_addr;
  wire [15:0]w_reg_data;
  wire w_reg_en;

  wire [15:0]r_reg_addr;
  wire [15:0]r_reg_data;
  wire r_reg_en;

  output [15:0]w_ram_addr;
  output [15:0]w_ram_data;
  output  w_ram_en;

  output[15:0]r_ram_addr;
  input [15:0]r_ram_data;
  output r_ram_en;
  output [15:0]adc_rata;

  spi_control spi_control_inst0(
                .clk(clk),
                .rstn(rstn),

                .spi_cs(spi_cs),
                .spi_clk(spi_clk),
                .spi_mosi(spi_mosi),
                .spi_miso(spi_miso),

                .w_reg_addr(w_reg_addr),
                .w_reg_data(w_reg_data),
                .w_reg_en(w_reg_en),

                .r_reg_addr(r_reg_addr),
                .r_reg_data(r_reg_data),
                .r_reg_en(r_reg_en)
              );

  reg_control reg_control_inst0(
                .clk(clk),
                .rstn(rstn),

                .w_reg_addr(w_reg_addr),
                .w_reg_data(w_reg_data),
                .w_reg_en(w_reg_en),

                .r_reg_addr(r_reg_addr),
                .r_reg_data(r_reg_data),
                .r_reg_en(r_reg_en),

                .w_ram_addr(w_ram_addr),
                .w_ram_data(w_ram_data),
                .w_ram_en(w_ram_en),

                .r_ram_addr(r_ram_addr),
                .r_ram_data(r_ram_data),
                .r_ram_en(r_ram_en),

                //自定义寄存器端口
                .adc_ram_en(adc_ram_en),

                .coef_a1(coef_a1),
                .coef_a2(coef_a2),
                .coef_b0(coef_b0),
                .coef_b1(coef_b1),
                .coef_b2(coef_b2),
                .coef_lode_en(coef_lode_en),
                .adc_rata(adc_rata)

              );

endmodule
