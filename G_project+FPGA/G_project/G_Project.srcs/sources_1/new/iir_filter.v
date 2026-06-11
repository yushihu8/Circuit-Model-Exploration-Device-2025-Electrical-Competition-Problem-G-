module iir_filter(
    clk,
    rstn,
    data_in,
    data_out,
    coef_a1,
    coef_a2,  
    coef_b0,
    coef_b1,
    coef_b2,
    data_in_val,
    coef_lode
  );

  input  clk;
  input  rstn;
  input  [13:0] data_in;        // 无符号ADC输入
  output reg [13:0] data_out;       // 无符号DAC输出
  input  coef_lode;

  input [47:0]coef_a1;
  input [47:0]coef_a2;
  input [47:0]coef_b0;
  input [47:0]coef_b1;
  input [47:0]coef_b2;
  input data_in_val;

  reg [5:0]filter_step;
  reg [5:0]filter_nest_step;

  reg signed[47:0]coef_b0_reg;
  reg signed[47:0]coef_b1_reg;
  reg signed[47:0]coef_b2_reg;
  reg signed[47:0]coef_a1_reg;
  reg signed[47:0]coef_a2_reg;

  wire signed[61:0] result_0;
  wire signed[61:0] result_1;
  wire signed[61:0] result_2;
  wire signed[61:0] result_3;
  wire signed[61:0] result_4;

  reg signed[62:0] resultSum;      // 加法结果需要63位
  wire signed[13:0] filter_in;

  wire signed[13:0] resultSumDiv;

  reg signed[13:0] data_x0 = 0;
  reg signed[13:0] data_x1 = 0;
  reg signed[13:0] data_x2 = 0;
  reg signed[13:0] data_y0 = 0;
  reg signed[13:0] data_y1 = 0;
  reg signed[13:0] data_y2 = 0;

  iir_mult iir_mult0 (
             .A(data_x0),  // input wire [13 : 0] A
             .B(coef_b0_reg),  // input wire [47 : 0] B
             .P(result_0)  // output wire [61 : 0] P
           );

  iir_mult iir_mult1 (
             .A(data_x1),  // input wire [13 : 0] A
             .B(coef_b1_reg),  // input wire [47 : 0] B
             .P(result_1)  // output wire [61 : 0] P
           );

  iir_mult iir_mult2 (
             .A(data_x2),  // input wire [13 : 0] A
             .B(coef_b2_reg),  // input wire [47 : 0] B
             .P(result_2)  // output wire [61 : 0] P
           );

  iir_mult iir_mult3 (
             .A(data_y1),  // input wire [13 : 0] A
             .B(coef_a1_reg),  // input wire [47 : 0] B
             .P(result_3)  // output wire [61 : 0] P
           );

  iir_mult iir_mult4 (
             .A(data_y2),  // input wire [13 : 0] A
             .B(coef_a2_reg),  // input wire [47 : 0] B
             .P(result_4)  // output wire [61 : 0] P
           );

  assign filter_in = $signed(data_in) - 14'sd8192;   // 转换为有符号

  // 右移45位并四舍五入
  // resultSum是63位En45, 需要右移45位得到14位整数
  // 四舍五入: 加2^44后右移45位
  wire signed[62:0] resultSum_rounded;
  assign resultSum_rounded = resultSum + 63'sd17592186044416;  // 加2^44
  assign resultSumDiv = resultSum_rounded[58:45];  // 右移45位, 取14位

  localparam
    step_dul = 0,
    step_1 = 1,
    step_2 = 2,
    step_3 = 3;

  always @(posedge clk or negedge rstn)
  begin
    if(~rstn)
      data_out <= 14'd0;
    else
      data_out = $unsigned(data_y0 + 14'sd8192);
  end

  always @(posedge clk or negedge rstn)
  begin
    if(!rstn)
    begin
      coef_a1_reg<= 'sd0;
      coef_a2_reg<= 'sd0;
      coef_b0_reg<= 'sd0;
      coef_b1_reg<= 'sd0;
      coef_b2_reg <= 'sd0;
    end
    else
    begin
      if(coef_lode)
      begin
        coef_a1_reg <= coef_a1;
        coef_a2_reg <= coef_a2;
        coef_b0_reg <= coef_b0;
        coef_b1_reg <= coef_b1;
        coef_b2_reg <= coef_b2;
      end
    end
  end

  always @(posedge clk or negedge rstn)
  begin
    if(!rstn)
      filter_step<=step_dul;
    else
      filter_step<=filter_nest_step;
  end

  always @(*)
  begin
    case(filter_step)
      step_dul:
      begin
        if(data_in_val)
          filter_nest_step=step_1;
        else
          filter_nest_step =  step_dul;
      end
      step_1:
        filter_nest_step=step_2;
      step_2:
        filter_nest_step=step_3;
      step_3:
        filter_nest_step=step_dul;
      default:
        filter_nest_step=step_dul;
    endcase
  end

  always @(posedge clk)
  begin
    begin
      case(filter_step)
        step_1:
          data_y0 <= resultSumDiv;
        step_2:
        begin
          data_x2<=data_x1;
          data_x1<=data_x0;
          data_x0<=filter_in;
          data_y2<=data_y1;
          data_y1<= data_y0;
        end
        step_3:
          resultSum <= result_0 + result_1 + result_2 - result_3 - result_4;
        default:
          data_y0 <= data_y0;
      endcase
    end
  end


endmodule
