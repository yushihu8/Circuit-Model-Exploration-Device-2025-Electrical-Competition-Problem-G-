`timescale 1ns/1ps
module top_tb();

  parameter WIDE = 16;

  reg clk;
  reg rstn;
  reg spi_cs;
  reg spi_clk;
  reg spi_mosi;

  reg [WIDE - 1:0]send_data;

  top top_inst0(
        .clk(clk),
        .rstn(rstn),
        .spi_cs(spi_cs),
        .spi_clk(spi_clk),
        .spi_mosi(spi_mosi),
        .adc_in0(14'd111),
        .adc_in1(14'd222)
      );

  initial
  begin
    clk = 0;
    rstn = 0;
    spi_clk = 0;
    spi_mosi = 0;
    spi_cs = 1;
    send_data = 0;
  end

  always #1 clk = ~clk;

  integer i = 0;

  initial
  begin
    #11;
    rstn = 1;
    #1000;
    send_data = 16'haa01;
    spi_cs = 0;
    #11;
    repeat(WIDE)
    begin
      spi_mosi = send_data[WIDE - 1 - i];
      #11;
      spi_clk = 1;
      #11;
      spi_clk = 0;
      #11;
      i = i + 1;
    end
    #11;
    spi_cs = 0;
    #2000;
    i = 0;
    send_data = 16'ha010;
    spi_cs = 0;
    #11;
    repeat(WIDE)
    begin
      spi_mosi = send_data[WIDE - 1 - i];
      #11;
      spi_clk = 1;
      #11;
      spi_clk = 0;
      #11;
      i = i + 1;
    end
    #11;
    spi_cs = 0;
    #1000;
    i = 0;
    send_data = 16'h1122;
    #11;
    repeat(WIDE)
    begin
      spi_mosi = send_data[WIDE - 1 - i];
      #11;
      spi_clk = 1;
      #11;
      spi_clk = 0;
      #11;
      i = i + 1;
    end

    spi_cs = 0;
    #1000;
    i = 0;
    send_data = 16'h3344;
    #11;
    repeat(WIDE)
    begin
      spi_mosi = send_data[WIDE - 1 - i];
      #11;
      spi_clk = 1;
      #11;
      spi_clk = 0;
      #11;
      i = i + 1;
    end


    spi_cs = 0;
    #1000;
    i = 0;
    send_data = 16'h5566;
    #11;
    repeat(WIDE)
    begin
      spi_mosi = send_data[WIDE - 1 - i];
      #11;
      spi_clk = 1;
      #11;
      spi_clk = 0;
      #11;
      i = i + 1;
    end


    spi_cs = 0;
    #1000;
    i = 0;
    send_data = 16'ha5a5;
    #11;
    repeat(WIDE)
    begin
      spi_mosi = send_data[WIDE - 1 - i];
      #11;
      spi_clk = 1;
      #11;
      spi_clk = 0;
      #11;
      i = i + 1;
    end

    spi_cs = 0;

    $stop;
  end


endmodule




