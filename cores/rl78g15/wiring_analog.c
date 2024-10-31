#include "wiring_private.h"
#include "wiring_variant.h"
#include "pins_variant.h"
#include "pintable.h"
#include "r_smc_entry.h"

#include "main.h"  // 使用する関数を定義

extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];
extern uint8_t g_adc_int_flg;
static uint8_t g_u8AnalogReference = DEFAULT;
boolean g_bAdcInterruptFlag = false;
uint16_t g_u16ADUL;
uint16_t g_u16ADLL;
extern uint32_t R_BSP_GetFclkFreqHz(void);

/* ★pow関数の代わり★ */
uint16_t pow2n(uint8_t fact);
const uint16_t  ans[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

/* Match to the value of PWM_PIN */
extern volatile unsigned short *g_timer_period_reg[PWM_CH_NUM];
extern volatile unsigned short *g_timer_duty_reg[PWM_CH_NUM];
extern volatile unsigned short *g_timer_analog_mode_reg[PWM_CH_NUM];
extern volatile unsigned short *g_timer_analog_clock_select_reg;
extern const uint8_t  pwm_channel_table[PWM_CH_NUM];
extern Pwm_func pwm_ch[PWM_CH_NUM];
extern const uint8_t g_au8AnalogPinTable[NUM_ANALOG_INPUTS];
extern const uint8_t g_analog_pin_input[NUM_ANALOG_INPUTS];

static void _analogPinRead(uint8_t pin);
static int _analogRead(uint8_t u8ADS);
static uint16_t _analogDuty(int val, uint16_t frequency);
static uint16_t _analogFrequency (uint8_t pin, uint32_t u32Hz);

bool g_u8AnalogReadAvailableTable[NUM_ANALOG_INPUTS] = { 0 };
bool g_u8AnalogWriteAvailableTable[NUM_DIGITAL_PINS] = {};

int8_t get_pwm_channel(uint8_t pwm_num)
{
    int8_t pwm_cnt;
    for(pwm_cnt=0;pwm_cnt<PWM_CH_NUM;pwm_cnt++)
    {
        if (pwm_num == pwm_channel_table[pwm_cnt])
        {
            return pwm_cnt;
        }
    }
    return -1;
}

/***********************************************************************************************************************
* Function Name: analogReference
* Description  : The reference voltage used for analog input.
* Arguments    : mode -
*                    DEFAULT: use VDD as VREF(+)
*                    INTERNAL: use internal voltage as VREF(+)
*                    EXTERNAL: use AVREFP as VREF(+)
* Return Value : None
***********************************************************************************************************************/
void analogReference(uint8_t mode) 
{
    g_u8AnalogReference = mode;
}


int8_t get_analog_channel(uint8_t analog_num)
{
    int8_t analog_cnt;

    for(analog_cnt=0;analog_cnt<NUM_ANALOG_INPUTS;analog_cnt++)
    {
        if (analog_num == g_analog_pin_input[analog_cnt])
        {
            return analog_cnt;
        }
    }
    return -1;
}


/***********************************************************************************************************************
* Function Name: analogRead
* Description  : Reads the value from the specified analog pin.
* Arguments    : analog_pin - the name of the analog input pin to read from A0 (=14) to A2 (=16)
* Return Value : The analog reading on the pin.
*                Although it is limited to the resolution of the analog to digital converter
*                (0-255 for 8 bits or 0-1023 for 10 bits).
***********************************************************************************************************************/
int analogRead(uint8_t analog_pin) {
    int s16Result = 0;
    uint8_t analog_read_flg = 0;
    uint8_t cnt;

    //アナログ入力端子の設定
    _analogPinRead(analog_pin);

    //アナログ入力端子ではない場合、何もしない終了する
    for(cnt = 0; cnt < NUM_ANALOG_INPUTS; cnt ++)
    {
        if(analog_pin == g_analog_pin_input[cnt])
        {
            analog_read_flg = 1;
            cnt = NUM_ANALOG_INPUTS;
        }
        else
        {
        analog_read_flg = 0;
        }
    }

    if(analog_read_flg == 1)
    {
        // アナログ値の読み込み
        s16Result = _analogRead(g_au8AnalogPinTable[get_analog_channel(analog_pin)]);
    }
    return s16Result;
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
/***********************************************************************************************************************
* Function Name: analogWrite
* Description  : Writes an analog value (PWM wave) to a pin.
* Arguments    : pin - the name of output pin (5,6,10,32)
*                value - Output PWM duty 0 ~ 255
* Return Value : None
***********************************************************************************************************************/
void analogWrite(uint8_t pin, int value) {
    if (pin < NUM_DIGITAL_PINS)
    {
        value = min(max(value, PWM_MIN), PWM_MAX);
        uint8_t cnt;
        uint8_t analog_write_flg = 0;
        int8_t pwm_channel = get_pwm_channel(pin);
        if (-1 ==(*(int8_t*)get_pwm_channel))
        {
            NOP();
        }
        /* If it is not a PWM output terminal, do nothing and exit */
        for(cnt = 0; cnt < PWM_CH_NUM; cnt ++)
        {
            if(pin == pwm_channel_table[cnt])
            {
                analog_write_flg = 1;
                cnt = PWM_CH_NUM;
            }
            else
            {
                analog_write_flg = 0;
            }
        }
        if(analog_write_flg == 1)
        {
            pwm_ch[pwm_channel].open();
            /* Frequency Set */
            if(pwm_ch[pwm_channel].cycle == CYCLE_VALUE)
            {
                pwm_ch[pwm_channel].cycle = _analogFrequency(pin,FREQUENCY_MIN_VAL);
            }
            else
            {
                *((uint32_t*)g_timer_period_reg[pwm_channel]) = pwm_ch[pwm_channel].cycle;
            }
            /* Duty set */
            *((uint32_t*)g_timer_duty_reg[pwm_channel])   = _analogDuty(value, pwm_ch[pwm_channel].cycle);
            pwm_ch[pwm_channel].start();
        }
    }
}

/***********************************************************************************************************************
* Function Name: analogWriteFrequency
* Description  : Sets the cycle. The default is 490Hz.
* Arguments    : Hz: cycle
* Return Value : None
***********************************************************************************************************************/
void analogWriteFrequency(uint32_t Hz) {
    /* PWM output pulse cycle setting
    Pulse period = (TDR00 setting value + 1) x count clock period
    Example) When the pulse period is 2 [ms]
    2 [ms] = 1/32 [MHz] x (TDR00 setting + 1)
    TDR00 setting value = 63999 */

    pwm_ch[0].cycle = _analogFrequency(PWM_PIN_3,Hz);

}

/***********************************************************************************************************************
* Function Name: analogWritePinFrequency
* Description  : Sets the cycle. The default is 490Hz.
* Arguments    : pin - the name of analog value (PWM wave) output pin (5,6,10,32)
*                Hz - cycle
* Return Value : None
***********************************************************************************************************************/

void analogWritePinFrequency(uint8_t pin, uint32_t Hz) {
#if 0
    /* PWM output pulse cycle setting
    Pulse period = (TDR00 setting value + 1) x count clock period
    Example) When the pulse period is 2 [ms]
    2 [ms] = 1/32 [MHz] x (TDR00 setting + 1)
    TDR00 setting value = 63999 */
    int8_t pwm_channel = get_pwm_channel(pin);
    pwm_ch[pwm_channel].cycle = _analogFrequency(pin, Hz);
#endif
}

static uint16_t _analogFrequency (uint8_t pin, uint32_t u32Hz)
{
    uint16_t Result;
    uint32_t fclk_frequency = 0;
    uint32_t timer_frequency = 0;
    uint32_t timer_clock_mode = 0;
    uint32_t operating_clock_select = 0;
    int8_t pwm_channel = get_pwm_channel(pin);

    fclk_frequency = R_BSP_GetFclkFreqHz();

  /* Get timer frequency */
    timer_clock_mode = *((uint32_t*)g_timer_analog_mode_reg[pwm_channel]) & TAU_OPERATION_CLOCK;

    if (timer_clock_mode == _4000_TAU_CLOCK_SELECT_CKM2) /* CK02 Clock Selected */
    {
        operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK02_OPERATION;
        if(operating_clock_select == _0000_TAU_CKM2_FCLK_1)
        {
            timer_frequency = fclk_frequency/2;    /*  fclk/2 */
        }
        else
        {
            operating_clock_select = operating_clock_select >> 8;
            //timer_frequency = fclk_frequency/( pow(2, 2 * operating_clock_select));    /*  fclk/2^2 ~ 2^6 */
            timer_frequency = fclk_frequency/( pow2n(2 * operating_clock_select));    /* ★ */
        }
    }
    else if  (timer_clock_mode == _C000_TAU_CLOCK_SELECT_CKM3) /* CK03 Clock Selected */
    {
        operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK03_OPERATION;
        operating_clock_select = operating_clock_select >> 12;
        //timer_frequency = fclk_frequency/( pow(2,(2 * operating_clock_select +8)));    /* fclk/2^8 ~ 2^14 */
        timer_frequency = fclk_frequency/( pow2n(2 * operating_clock_select +8));    /* ★ */
    }
    else /* CK00, CK01 Clock Selected */
    {
        operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK00_CK01_OPERATION;
        //timer_frequency = fclk_frequency/( pow(2,operating_clock_select));    /* ckm00, ckm01 - fclk/2^0 ~ 2^15 */
        timer_frequency = fclk_frequency/( pow2n(operating_clock_select));    /* ★ */
    }

    /* 490 Hz <= frequency <= 8MHz */
    u32Hz = min(max(u32Hz, FREQUENCY_MIN_VAL), FREQUENCY_MAX_VAL);

    /* Pulse period = {Set value of TDRmn (master) + 1} × Count clock period
    Set value of TDRmn (master) = (Pulse period / Count clock period) - 1 */
    Result = (timer_frequency / u32Hz) - 1;

    return Result;
}

static uint16_t _analogDuty(int val, uint16_t frequency)
{
/*    Duty factor [0 ~ 255] = {Set value of TDRmp (slave)}/{Set value of TDRmn (master) + 1} × 255
    {Set value of TDRmp (slave)} = Duty factor * {Set value of TDRmn (master) + 1} / 255 */
    uint16_t u16Duty = 0;
    /* Duty set */
    if(val >= PWM_MAX)
    {
        u16Duty = frequency + 1;

    }
    else if(val == PWM_MIN)
    {
        u16Duty = 0;
    }
    else
    {
        u16Duty = (uint16_t) (((unsigned long) val  * (frequency + 1)) / PWM_MAX);
    }
    return u16Duty;
}

static void _analogPinRead (uint8_t pin)
{
    int8_t pin_index;
    pin_index = (int8_t)pin - ANALOG_PIN_START_NUMBER;
    // if pin_index is not within the accessable range do nothing
    if((pin_index < 0) || (pin_index >= NUM_ANALOG_INPUTS))
    {
        return;
    }
    if (g_u8AnalogReadAvailableTable[pin_index] == false)
    {
        const PinTableType ** pp;
        PinTableType * p;
        pp = &pinTablelist[pin];
        p = (PinTableType *)*pp;
        if (0!=p->pmc)
        {
            pinMode(pin, INPUT);
            /* アナログピンの場合PMCをセットする */
            *p->portModeControlRegisterAddr |= (unsigned long)(p->pmc);
            g_u8AnalogReadAvailableTable[pin_index] = true;
        }
    }
}

static int _analogRead(uint8_t u8ADS) {
    int s16Result = 0;
    uint8_t adc_end_flg = 0;
    R_Config_ADC_Set_ADChannel(u8ADS);
    while(0 == adc_end_flg)
    {
        g_adc_int_flg=0;
        R_Config_ADC_Set_OperationOn();  //ADCE=1 & wait
        delay(100);
        R_Config_ADC_Start();            //ADCS=1 & enable interrupt
        // 7. After STOP mode until AD interrupt occurs (loop processing)
        while (0 == g_adc_int_flg)
        {
            NOP();
        }
        delay(100);
        // 8. Snooze mode Off (interrupt stop)
        R_Config_ADC_Stop();
        // 9. Get AD conversion result
        R_Config_ADC_Get_Result_10bit ((uint16_t*) &s16Result);
        adc_end_flg = 1;
    }
    // 10.AD Comparator Off
    R_Config_ADC_Set_OperationOff();

    // 11. Return the result
    return s16Result;
}


/* ★ */
uint16_t pow2n(uint8_t fact)
{
    return ans[fact];
}

