#include "adc3.h" // 包含ADC3相关的头文件

/**
 * @brief  初始化ADC3.
 *         配置ADC3时钟, GPIO引脚, ADC参数及采样序列.
 * @param  None
 * @retval None
 */
void ADC3_Init(void)
{
    // --- 外设时钟使能 ---
    RCC->APB2ENR |= RCC_APB2ENR_ADC3EN; // 使能ADC3外设时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN; // 使能GPIOF外设时钟

    // --- ADC时钟配置 ---
    RCC->CFGR &= ~RCC_CFGR_ADCPRE;  // 清除ADC预分频器原有配置
    RCC->CFGR |= RCC_CFGR_ADCPRE_1; // 设置ADC预分频器为6分频 (APB2时钟/6)

    // --- GPIO引脚配置 (PF8, PF9为模拟输入) ---
    GPIOF->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8); // 清除PF8引脚的原有配置 (配置为模拟输入)
    GPIOF->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9); // 清除PF9引脚的原有配置 (配置为模拟输入)

    // --- ADC参数配置 ---
    ADC3->CR1 |= ADC_CR1_SCAN; // 开启扫描模式

    ADC3->CR2 |= ADC_CR2_CONT; // 使能连续转换模式

    ADC3->CR2 &= ~ADC_CR2_ALIGN; // 设置数据右对齐

    // --- ADC采样时间配置 (通道6和通道7) ---
    ADC3->SMPR2 &= ~ADC_SMPR2_SMP6;  // 清除通道6的采样时间配置
    ADC3->SMPR2 |= ADC_SMPR2_SMP6_0; // 设置通道6的采样时间为7.5个周期 (1.5 + 6)
    ADC3->SMPR2 &= ~ADC_SMPR2_SMP7;  // 清除通道7的采样时间配置
    ADC3->SMPR2 |= ADC_SMPR2_SMP7_0; // 设置通道7的采样时间为7.5个周期 (1.5 + 6)

    // --- ADC规则序列配置 (转换通道6和通道7) ---
    ADC3->SQR1 &= ~ADC_SQR1_L;  // 清除规则序列长度原有配置
    ADC3->SQR1 |= ADC_SQR1_L_0; // 设置规则序列长度为2

    ADC3->SQR3 &= ~ADC_SQR3_SQ1; // 清除规则序列中第一个转换的通道选择
    ADC3->SQR3 |= 6 << 0;        // 设置规则序列中第一个转换的通道为通道6
    ADC3->SQR3 &= ~ADC_SQR3_SQ2; // 清除规则序列中第二个转换的通道选择
    ADC3->SQR3 |= 7 << 5;        // 设置规则序列中第二个转换的通道为通道7

    // ADC3->CR2 |= ADC_CR2_EXTTRIG; // 使能外部触发转换
    // ADC3->CR2 |= ADC_CR2_EXTSEL;  // 选择SWSTART作为外部触发源 (所有位为1)
}

/**
 * @brief  初始化ADC3的DMA通道.
 *         配置DMA2通道5用于ADC3的数据传输.
 * @param  None
 * @retval None
 */
void ADC3_DMA_Init(void)
{
    // --- DMA时钟使能 ---
    RCC->AHBENR |= RCC_AHBENR_DMA2EN; // 使能DMA2外设时钟

    // --- DMA通道5配置 (用于ADC3) ---
    DMA2_Channel5->CCR &= ~DMA_CCR5_DIR; // 设置数据传输方向为从外设到存储器

    // --- 数据宽度配置 ---
    DMA2_Channel5->CCR &= ~DMA_CCR5_MSIZE;  // 清除存储器数据宽度原有配置
    DMA2_Channel5->CCR |= DMA_CCR5_MSIZE_0; // 设置存储器数据宽度为16位
    DMA2_Channel5->CCR &= ~DMA_CCR5_PSIZE;  // 清除外设数据宽度原有配置
    DMA2_Channel5->CCR |= DMA_CCR5_PSIZE_0; // 设置外设数据宽度为16位

    // --- 地址增量配置 ---
    DMA2_Channel5->CCR |= DMA_CCR5_MINC;  // 使能存储器地址增量
    DMA2_Channel5->CCR &= ~DMA_CCR5_PINC; // 禁止外设地址增量

    // --- 循环模式配置 ---
    DMA2_Channel5->CCR |= DMA_CCR5_CIRC; // 使能循环模式

    // --- ADC DMA使能 ---
    ADC3->CR2 |= ADC_CR2_DMA; // 使能ADC3的DMA请求
}

/**
 * @brief  启动ADC3的DMA转换.
 *         设置DMA目标地址和传输长度, 然后启动ADC转换.
 * @param  dsetAddr 目标存储器地址 (uint32_t)
 * @param  len      传输的数据长度 (uint8_t)
 * @retval None
 */
void ADC3_DMA_StartConvert(uint32_t dsetAddr, uint8_t len)
{
    // --- DMA传输参数配置 ---
    DMA2_Channel5->CPAR = (uint32_t)&(ADC3->DR); // 设置DMA外设地址为ADC3数据寄存器
    DMA2_Channel5->CMAR = dsetAddr;              // 设置DMA存储器地址
    DMA2_Channel5->CNDTR = len;                  // 设置DMA传输数据量

    // --- DMA通道使能 ---
    DMA2_Channel5->CCR |= DMA_CCR5_EN; // 使能DMA2通道5

    // --- ADC电源和校准 ---
    ADC3->CR2 |= ADC_CR2_ADON; // 开启ADC3电源

    ADC3->CR2 |= ADC_CR2_CAL;         // 启动ADC3校准
    while ((ADC3->CR2 & ADC_CR2_CAL)) // 等待ADC3校准完成
        ;                             // 空循环等待
    // ADC3->CR2 |= ADC_CR2_SWSTART;     // 启动软件触发转换
    ADC3->CR2 |= ADC_CR2_ADON; // 再次置位ADON以启动转换

    while ((ADC3->SR & ADC_SR_EOC) == 0) // 等待转换完成 (EOC位为1表示转换完成)
        ;                                // 空循环等待 
}