#ifndef _BIT_MATH_H_
#define  _BIT_MATH_H_
#define GET_BIT(reg,bit) ((reg>>(bit))&1)
#define SET_BIT(reg,bit) (reg=(reg|(1<<bit)))
#define CLR_BIT(reg,bit) (reg=(reg&(~(1<<bit))))
#define TOG_BIT(reg,bit) (reg=reg^(1<<bit))
#endif
