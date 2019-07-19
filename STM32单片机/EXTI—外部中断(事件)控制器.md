# EXTI—外部中断/事件控制器
EXTI（External interrupt/event controller）—外部中断/事件控制器，管理了控制器的20个中断/事件线。每个中断/事件线都对应有一个边沿检测器，可以实现输入信号的上升沿检测和下降沿的检测。EXTI可以实现对每个中断/事件线进行单独配置，可以单独配置为中断或者事件，以及触发事件的属性。   
EXTI可分为两大部分功能，一个是==产生中断==，另一个是==产生事件==。 
![EXTI功能框图](http://note.youdao.com/yws/public/resource/3bd5b0854dfbb54fdd612cf89dfacb2c/xmlnote/186C5590E4EB4C77BCF710920B4E403C/1984)
 红色线路是一个==产生中断==的线路，最终信号流到NVIC控制器内。         
 1. 输入线： 可通过寄存器设置为**任意一个GPIO**，也可以是一些**外设事件**。 
 2. 边缘检测电路：根据上升沿触发选择 **寄存器(EXTI_RTSR)和下降沿触发选择寄存器(EXTI_FTSR)** 对应位的设置来控制信号触发。检测电路以输入线作为信号输入端，如果检测到有边沿跳变就输出有效信号1给编号3电路，否则输出无效信号0.可以是只有上升沿触发、只有下降沿触发或者上升沿和下降沿都触发.
 3. 实际就是一个或门电路，一个输入来自编号2电路，另外一个输入来自软件**中断事件寄存器(EXTI_SWIER)**。EXTI_SWIER允许我们通过程序控制就可以启动中断/事件线.
 4. 一个与门电路，它一个输入是编号3电路，另外一个输入来自**中断屏蔽寄存器(EXTI_IMR)**.简单的控制EXTI_IMR来实现是否产生中断的目的。编号4电路输出的信号会被保存到挂起**寄存器(EXTI_PR)** 内，如果确定编号4电路输出为1就会把EXTI_PR对应位置1。
 5. 将EXTI_PR寄存器内容输出到NVIC内，从而实现系统中断事件控制.

---
虚线指示的电路流程。它是一个产生事件的线路，最终输出一个==脉冲信号==。    
 6. 6电路是一个与门，它一个输入来自编号3电路，另外一个输入来自**事件屏蔽寄存器(EXTI_EMR)**。简单的控制EXTI_EMR来实现是否产生事件的目的。
 7. 一个脉冲发生器电路，当它的输入端，即编号6电路的输出端，是一个有效信号1时就会产生一个脉冲；如果输入端是无效信号就不会输出脉冲。
 8. 个脉冲信号，就是产生事件的线路最终的产物，这个脉冲信号可以给其他外设电路使用，比如定时器TIM、模拟数字转换器ADC等等，这样的脉冲信号一般用来触发TIM或者ADC开始转换。

- 产生中断线路目的是把输入信号输入到NVIC，进一步会运行中断服务函数，实现功能，这样是==软件级==的。而产生事件线路目的就是传输一个脉冲信号给其他外设使用，并且是电路级别的信号传输，属于==硬件级==的。
- EXTI是在APB2总线上的。

## 中断|事件线
![中断|事件](http://note.youdao.com/yws/public/resource/3bd5b0854dfbb54fdd612cf89dfacb2c/xmlnote/EDE8F068383144EBAFC380A2EA845240/2035)  
XTI0至EXTI15用于GPIO，通过编程控制可以实现任意一个GPIO作为EXTI的输入源。由表18-1可知，EXTI0可以通过AFIO的外部中断配置寄存器1(AFIO_EXTICR1)的EXTI0[3:0]位选择配置为PA0、PB0、PC0、PD0、PE0、PF0、PG0、PH0或者PI0.
## EXTI初始化结构体详解
```
typedefstruct 
{
uint32_tEXTI_Line;                   // 中断/事件线 
EXTIMode_TypeDef EXTI_Mode;         // EXTI模式  
EXTITrigger_TypeDef EXTI_Trigger;   // 触发类型 
FunctionalState EXTI_LineCmd;       // EXTI使能  
} EXTI_InitTypeDef;
```
1) EXTI_Line：EXTI中断/事件线选择，可选EXTI0至EXTI19。 
2) EXTI_Mode：EXTI模式选择，可选为产生中断(EXTI_Mode_Interrupt)或者产生事件(EXTI_Mode_Event)。
3) EXTI_Trigger：EXTI边沿触发事件，可选上升沿触发(EXTI_Trigger_Rising)、下降沿触发(EXTI_Trigger_Falling)或 者 上 升 沿 和 下 降 沿 都 触 发(EXTI_Trigger_Rising_Falling) 。
4) EXTI_LineCmd：控制是否使能EXTI线，可选使能EXTI线(ENABLE)或禁用(DISABLE)。


