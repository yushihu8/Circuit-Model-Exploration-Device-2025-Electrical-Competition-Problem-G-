/**********************************************************
>> 模块名       :SPI从机模块
>> 信息         :全双工SPI从机 CPHA = 0 CPOL = 0
>> 版本         :v0.0
>> 时间         :2025-11-21
>> 作者         :ts
************************************************************/

module spi_slave(
    clk,
    rstn,
    spi_cs,
    spi_clk,
    spi_mosi,
    spi_miso,
    spi_data_in,
    spi_data_out,
    spi_rec_val,
    spi_data_val
  );

  //数据位宽配置
  parameter DATA_WIDTH = 16;

  input clk;
  input rstn;
  input spi_cs;
  input spi_clk;
  input spi_mosi;
  input spi_data_val;
  input [DATA_WIDTH-1:0] spi_data_in;

  output reg spi_miso;
  output reg [DATA_WIDTH-1:0] spi_data_out;
  output reg spi_rec_val;

  reg [4:0] bit_count;
  reg [1:0] spi_clk_reg;
  reg [DATA_WIDTH-1:0] spi_data_in_reg;
  reg [DATA_WIDTH-1:0] spi_data_out_reg;

  wire spi_clk_pos_edge;
  wire spi_clk_neg_edge;

  assign spi_clk_pos_edge = spi_clk_reg[1:0] == 2'b01 && ~spi_cs;
  assign spi_clk_neg_edge = spi_clk_reg[1:0] == 2'b10 && ~spi_cs;

  always @(posedge clk or negedge rstn)
  begin
    if(~rstn)
      spi_clk_reg <= 3'd0;
    else
      spi_clk_reg <= {spi_clk_reg[0], spi_clk};
  end

  always @(posedge clk or negedge rstn)
  begin
    if(~rstn)
    begin
      spi_data_out <= 'd0;
      spi_data_out_reg <= 'd0;
    end
    else if(spi_clk_pos_edge)
    begin
      if(bit_count == DATA_WIDTH - 1)
        spi_data_out <= {spi_data_out_reg[DATA_WIDTH-2:0], spi_mosi};
      else
        spi_data_out_reg <= {spi_data_out_reg[DATA_WIDTH-2:0], spi_mosi};
    end
  end

  always @(posedge clk or negedge rstn)
  begin
    if(~rstn)
      bit_count <= 5'd0;
    else if(~spi_cs)
    begin
      if(spi_clk_pos_edge)
        bit_count <= bit_count + 5'd1;
      else if(bit_count == DATA_WIDTH && spi_clk_neg_edge)
        bit_count <= 5'd0;
    end
    else
      bit_count <= 5'd0;
  end

  always @(posedge clk or negedge rstn)
  begin
    if(~rstn)
      spi_rec_val <= 1'd0;
    else
      spi_rec_val <= (spi_clk_neg_edge && bit_count == DATA_WIDTH);
  end

  always @(posedge clk or negedge rstn)
  begin
    if(~rstn)
      spi_data_in_reg <= 'd0;
    else
    begin
      if(~spi_cs && spi_data_val)
        spi_data_in_reg <= spi_data_in;
      else if(spi_clk_neg_edge)
      begin
        if(bit_count != DATA_WIDTH)
          spi_data_in_reg <= spi_data_in_reg << 1;
      end
    end
  end

  always @(posedge clk or negedge rstn)
  begin
    if(~rstn)
      spi_miso <= 1'd0;
    else if(~spi_cs)
      spi_miso <= spi_data_in_reg[DATA_WIDTH - 1];
    else
      spi_miso <= 1'd0;
  end

endmodule
