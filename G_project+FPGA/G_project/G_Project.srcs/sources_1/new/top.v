 module top(
    clk,
    rstn,
    spi_cs,
    spi_clk,
    spi_mosi,
    spi_miso,

    adc_clk0,
    adc_in0,
    adc_clk1,
    adc_in1,

    dac_clk,
    dac_out
  );

  input clk;
  input rstn;
  input spi_cs;
  input spi_clk;
  input spi_mosi;
  output spi_miso;

  output adc_clk0;
  input [13:0]adc_in0;

  output adc_clk1;
  input [13:0]adc_in1;

  output dac_clk;
  output [13:0]dac_out;

  wire adc_val0;
  wire [13:0]adc_out0;

  wire adc_val1;
  wire [13:0]adc_out1;

  wire clk_out40_96m;

  wire [9:0]w_ram_addr;
  wire [27:0] w_ram_data;
  wire  w_ram_en;

  wire [15:0]r_ram_addr;
  wire [13:0]r_ram_data;
  wire r_ram_en;

  wire adc_ram_en;

  wire [47:0]coef_a1;
  wire [47:0]coef_a2;
  wire [47:0]coef_b0;
  wire [47:0]coef_b1;
  wire [47:0]coef_b2;
  wire coef_lode_en;

  wire [15:0]adc_rata;

  assign dac_clk = ~clk_out40_96m;

  clk_wiz_40_96m clk_wiz_40_96m_inst0
                 (
                   .clk_out1(clk_out40_96m),
                   .resetn(rstn),
                   .clk_in1(clk)
                 );

  ad9248 ad9248_inst0(
           .clk(clk_out40_96m),
           .rstn(rstn),
           .adc_clk(adc_clk0),
           .adc_in(adc_in0),
           .adc_out(adc_out0),
           .adc_val(adc_val0),
           .clk_tim_count(16'd99)
         );

  ad9248 ad9248_inst1(
           .clk(clk_out40_96m),
           .rstn(rstn),
           .adc_clk(adc_clk1),
           .adc_in(adc_in1),
           .adc_out(adc_out1),
           .adc_val(adc_val1),
           .clk_tim_count(adc_rata)
         );

  adc_ram_control adc_ram_control_inst0(
                    .clk(clk_out40_96m),
                    .rstn(rstn),
                    .adc_in0(adc_out0),
                    .adc_in1(adc_out1),
                    .adc_val(adc_val0),
                    .w_ram_addr(w_ram_addr),
                    .w_ram_data(w_ram_data),
                    .w_ram_en(w_ram_en),
                    .adc_ram_en(adc_ram_en)
                  );

  adc_ram adc_ram_inst0(
            .clka(clk_out40_96m),
            .wea(w_ram_en),
            .addra(w_ram_addr),
            .dina(w_ram_data),
            .clkb(clk_out40_96m),
            .enb(r_ram_en),
            .addrb(r_ram_addr[10:0]),
            .doutb(r_ram_data)
          );

  iir_filter iir_filter_inst0(
               .clk(clk_out40_96m),
               .rstn(rstn),
               .data_in(adc_out1),
               .data_out(dac_out),
               .coef_a1(coef_a1),
               .coef_a2(coef_a2),
               .coef_b0(coef_b0),
               .coef_b1(coef_b1),
               .coef_b2(coef_b2),
               .data_in_val(adc_val1),
               .coef_lode(1'd1)
             );
             
  spi_reg_control spi_reg_control_inst0(
                    .clk(clk_out40_96m),
                    .rstn(rstn),

                    .spi_cs(spi_cs),
                    .spi_clk(spi_clk),
                    .spi_mosi(spi_mosi),
                    .spi_miso(spi_miso),

                    // .w_ram_addr(w_ram_addr),
                    // .w_ram_data(w_ram_data),
                    // .w_ram_en(w_ram_en),

                    .r_ram_addr(r_ram_addr),
                    .r_ram_data({2'b00,r_ram_data}),
                    .r_ram_en(r_ram_en),

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
