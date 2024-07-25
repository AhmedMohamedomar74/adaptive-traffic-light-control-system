#include "ADC.h"
void INIT_ADC(ADC_Init_t *PTR)
{
    ADMUX |= (PTR->channel_selcted) | (PTR->Data_Adj) | (PTR->V_ref_select);
    ADCSRA |= (PTR->Division_factor_selcted);
    ADCSRA = ADCSRA | (1 << ADEN);
}

u16 ADC_Read_test()
{
    u16 Ain;
    u8 AinLow;
    ADCSRA = ADCSRA | (1 << ADSC);
    /* Polling on the flag */
    while (((ADCSRA >> ADIF) & 1) == 0)
        ;
    AinLow = ADCL;
    Ain = (int)ADCH * 256;
    Ain = Ain + AinLow;
    return (Ain);
}
