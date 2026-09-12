#include"typedef.h"

void WriteLCD(u8 data);

void CmdLCD(u8 cmd);

void CharLCD(u8 ascii);

void InitLCD(void);

void StrLCD(s8* p);

void U32LCD(u32 n);

void F32LCD(f32 data,u32 nd);

void BuildCGRAM(u8* p, u8 nb);

void BinLCD(u8 data,u8 nb);

void HEXLCD(u32 n);
