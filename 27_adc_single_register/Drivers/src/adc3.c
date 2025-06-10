#include "adc3.h" // 包含ADC3相关的头文件

/**
 * @brief  初始化ADC3.
 *         配置ADC3时钟, GPIO引脚, ADC参数及采样序列.
 * @param  None
 * @retval None
 */
void ADC3_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC3EN; // 使能ADC3外设时钟

    RCC->CFGR &= ~RCC_CFGR_ADCPRE;  // 清除ADC预分频器原有配置
    RCC->CFGR |= RCC_CFGR_ADCPRE_1; // 设置ADC预分频器为6分频 (APB2时钟/6)

    GPIOF->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8); // 清除PF8引脚的原有配置 (配置为模拟输入)

    ADC3->CR1 &= ~ADC_CR1_SCAN; // 禁止扫描模式

    ADC3->CR2 |= ADC_CR2_CONT; // 使能连续转换模式

    ADC3->CR2 &= ~ADC_CR2_ALIGN; // 设置数据右对齐

    ADC3->SMPR2 &= ~ADC_SMPR2_SMP6;  // 清除通道6的采样时间配置
    ADC3->SMPR2 |= ADC_SMPR2_SMP6_0; // 设置通道6的采样时间为7.5个周期 (1.5 + 6)

    ADC3->SQR1 &= ~ADC_SQR1_L;   // 设置规则序列长度为1
    ADC3->SQR3 &= ~ADC_SQR3_SQ1; // 清除规则序列中第一个转换的通道选择
    ADC3->SQR3 |= 6 << 0;        // 设置规则序列中第一个转换的通道为通道6

    ADC3->CR2 |= ADC_CR2_EXTTRIG; // 使能外部触发转换
    ADC3->CR2 |= ADC_CR2_EXTSEL;  // 选择SWSTART作为外部触发源 (所有位为1)
}

/**
 * @brief  启动ADC3转换.
 *         包括开启ADC, 校准ADC, 以及启动软件触发转换.
 * @param  None
 * @retval None
 */
void ADC3_StartConvert(void)
{
    ADC3->CR2 |= ADC_CR2_ADON; // 开启ADC3电源

    ADC3->CR2 |= ADC_CR2_CAL;         // 启动ADC3校准
    while ((ADC3->CR2 & ADC_CR2_CAL)) // 等待ADC3校准完成
        ;                             // 空循环等待
    ADC3->CR2 |= ADC_CR2_SWSTART;     // 启动软件触发转换

    while ((ADC3->SR & ADC_SR_EOC) == 0) // 等待转换完成 (EOC位为1表示转换完成)
        ;                                // 空循环等待
}

/**
 * @brief  读取ADC3转换结果并转换为电压值.
 * @param  None
 * @retval double 转换后的电压值 (单位:伏特).
 */
double ADC3_ReturnVoltage(void)
{
    return ADC3->DR * 3.3 / 4095; // 3.3 * X / (2^12 – 1)
}
